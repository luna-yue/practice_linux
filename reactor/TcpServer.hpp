#include "Log.hpp"
#include "Epoller.hpp"
#include "Socket.hpp"
#include "NonBlock.hpp"
#include <functional>
#include <memory>
#include <unordered_map>

class Connection;
class TcpServer;

using namespace std;
using func_t = function<void(weak_ptr<Connection>)>;
#define _sz 1024
#define _bufsz 1024

class Connection
{
public:
    Connection() = default;
    func_t _recv_cb;
    func_t _send_cb;
    func_t _except_cb;
    string _ip;
    uint16_t _port;
    int sockfd()
    {
        return sock;
    }
    void SetSock(int x)
    {
        sock=x;
    }
    void SetFunc(func_t recv_cb,func_t send_cb,func_t except_cb)
    {
        _recv_cb=recv_cb;
        _send_cb=send_cb;
        _except_cb=except_cb;
    }
    void AddInbuffer(const string &append)
    {
        _inbuffer += append;
    }
    void AddOutBuffer(const string &append)
    {
        _outbuffer += append;
    }
    string & GetOutBuffer()
    {
        return _outbuffer;
    }
    string & GetInBuffer()
    {
        return _inbuffer;
    }
private:
    int sock;
    string _inbuffer;
    string _outbuffer;
};
class TcpServer : public enable_shared_from_this<TcpServer>
{

    // bool CheckConnection()
    public: TcpServer(uint16_t port,func_t MessageHandler):_port(port),_listensock(new sock()),_Epoller(new Epoller()),_MessageHandler(MessageHandler){}

    void AddConnection(int fd,uint32_t event,func_t recv_cb,func_t send_cb,func_t except_cb,const string& ip="0.0.0.0",uint16_t port=0)
    {
        if(_connections.count(fd))
        return;
        shared_ptr <Connection> NewConnection = make_shared<Connection>();
        NewConnection->SetFunc(recv_cb,send_cb,except_cb);
        NewConnection->_ip=ip;
        NewConnection->_port=port;  
        NewConnection->SetSock(fd);
        _connections[fd]=NewConnection;
        _Epoller->Update(EPOLL_CTL_ADD,fd,event);
        EnableEvents(fd,1,0);//设为ET
        SetNonBlock(fd);
        lg(Info,"get new connection%d   %s   %d  connection sz now:> %d",fd,ip.c_str(),port,_connections.size());
    }
    public: void Init()
    {
        _listensock->Socket();
        SetNonBlock(_listensock->fd());
        _listensock->Bind(_port);
        _listensock->Listen();
        lg(Info, "create listen socket success: %d", _listensock->fd());
        AddConnection(_listensock->fd(),EPOLLIN|EPOLLET,bind(&TcpServer::Accepter,this,placeholders::_1),nullptr,nullptr);
    }
    //当监听套接字上有EPOLLIN就绪，回调Accepter
    void Accepter(std::weak_ptr<Connection> conn)
    {
        auto connection = conn.lock();
        while (true)
        {
            string ip;
          uint16_t port;
          int newfd=_listensock->Accept(&ip,&port);
          if(newfd>0)
          {
            AddConnection(newfd,EPOLLIN,bind(&TcpServer::Recver,this,placeholders::_1),
            bind(&TcpServer::Sender,this,placeholders::_1),
            bind(&TcpServer::Excepter,this,placeholders::_1),ip,port);
          }
            else
            {
                 if(errno==EWOULDBLOCK)//非阻塞，无新连接 errno会被设置为其中一个
               break;
               else if(errno==EINTR)
               continue;
               else
               {
                lg(Error,"???Accepter error :> %s",strerror(errno));
                break;
               }

            }
        }
    }
    //ET模式 一次读完写完 
    void Recver(weak_ptr<Connection> tmp)
    {
        if (tmp.expired())
            return;
        auto now = tmp.lock();
        char buf[_bufsz];
        int fd = now->sockfd();
        while (1)
        {
            int n = recv(now->sockfd(), buf, _bufsz - 1, MSG_DONTWAIT); // 非阻塞读取
            if (n > 0)
            {
                now->AddInbuffer(buf);
            }
            else if (n == 0)
            {
                lg(Info, "sockfd: %d, client info %s:%d quit...", fd, now->_ip.c_str(), now->_port);
                now->_except_cb(now);
                return;
            }
            else
            {
                if (errno == EWOULDBLOCK)
                    break;
                else if (errno == EINTR)
                    continue;
                else
                {
                    lg(Warning, "sockfd: %d, client info %s:%d recv error...", fd, now->_ip.c_str(), now->_port);
                    now->_except_cb(now);
                    return;
                }
            }
        }
        //对于数据的完整性验证 数据的处理，由上层处理，Server只读取数据到buffer
        _MessageHandler(tmp);
    }
    void Sender(weak_ptr<Connection> tmp)
    {
        if (tmp.expired())
            return;
        auto now = tmp.lock();
        
        int fd = now->sockfd();
        string & outbuffer=now->GetOutBuffer();
        while (1)
        {
            int n = send(now->sockfd(), outbuffer.c_str(), outbuffer.size(), MSG_DONTWAIT); // 非阻塞读取
            if (n > 0)
            {
                outbuffer.erase(0,n);
                if(outbuffer.empty())
                break;
            }
            else if (n == 0)//?
            {
                lg(Info, "sockfd: %d, client info %s:%d quit...", fd, now->_ip.c_str(), now->_port);
                now->_except_cb(now);
                return;
            }
            else
            {
                if (errno == EWOULDBLOCK)//用于非阻塞模式，不需要重新读或者写
                    break;
                else if (errno == EINTR)//指操作被中断唤醒，需要重新读/写
                    continue;
                else
                {
                    lg(Warning, "sockfd: %d, client info %s:%d recv error...", fd, now->_ip.c_str(), now->_port);
                    now->_except_cb(now);
                    return;
                }
            }
        }
        if(!outbuffer.empty())
        {
              EnableEvents(fd,1,1);
        }
        else
        {
              EnableEvents(fd,1,0);
        }
    }
    void Excepter(weak_ptr<Connection> tmp) // 遇到错误关闭连接
    {
        if(tmp.expired())
        return;
        auto now=tmp.lock();
        _Epoller->Update(EPOLL_CTL_DEL,now->sockfd(),0);
        lg(Info,"From Excepter : fd:%d ip:%s port:%d", now->sockfd(),now->_ip.c_str(),now->_port);
        close(now->sockfd());
        auto it=_connections.find(now->sockfd());
        if(it!=_connections.end())
        _connections.erase(it);
    }
    void Dispatcher(int timeout = 3000)
    {
        int n = _Epoller->Wait(_ready_list, _sz, timeout);

        for (int i = 0; i < n; i++)
        {
            int events = _ready_list[i].events;
            int fd = _ready_list[i].data.fd;
            if (events & EPOLLHUP || events & EPOLLERR)
            {
                _connections[fd]->_except_cb(_connections[fd]);
                continue;
            }
            if (events & EPOLLIN)
                _connections[fd]->_recv_cb(_connections[fd]);
            if (events & EPOLLOUT)
                _connections[fd]->_send_cb(_connections[fd]);
        }
    }
    void EnableEvents(int fd,int readable,int writeable)
    {
        uint32_t event=0;
        event|=EPOLLET;
        if(readable)event|=EPOLLIN;
        if(writeable)event|=EPOLLOUT;
        //MOD时是覆盖式
        _Epoller->Update(EPOLL_CTL_MOD,fd,event);
    }
    void ShowConnections()
    {
        cout<<"Connections now:> "<<_connections.size()<<endl;
        for(auto &e:_connections)
        {
           cout<<e.second->sockfd()<<" "<<e.second->GetInBuffer().size()<<" "<<e.second->GetInBuffer()<<endl;
        }
    }
   public: void loop()
    {
        while(1)
        {
           Dispatcher();
           ShowConnections();
        }
    }
    
private:
    unordered_map<int, shared_ptr<Connection>> _connections;
    epoll_event _ready_list[_sz];
    uint16_t _port;
    shared_ptr<sock> _listensock;
    shared_ptr<Epoller> _Epoller;
    func_t _MessageHandler;
};
