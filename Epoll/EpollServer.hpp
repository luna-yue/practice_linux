#include "Socket.hpp"
#include "Log.hpp"
#include <memory>
#include <string>
#include "Epoller.hpp"
using namespace std;

#define _sz 1024
#define care_events EPOLLIN

class EpollServer{
    public:
    EpollServer(uint16_t port):_port(port),_Epoller(new Epoller()){
     
    }
    ~EpollServer()
    {
        _listensock.Close();
    }
    void Accepter()
    {
        string ip;
        uint16_t port;
        int n=_listensock.Accept(&ip,&port);
        if(n<0)
        {
            lg(Error,"Accept error:> %s",strerror(errno));
            return;
        }
        _Epoller->Update(EPOLL_CTL_ADD,n,care_events);
    }
    void Recver(int fd,int pos)
    {
        char buf[1024];
        int n=read(fd,buf,sizeof(buf)-1);
        if(n>0)
        {
            buf[n] = 0;
            cout << "get a messge: " << buf << endl;
        }
        else if(n==0)
        {
            lg(Info,"client quit %d",fd);
            close(fd);
           _Epoller->Update(EPOLL_CTL_DEL,_listensock.fd(),0);
        }
        else 
        {
            lg(Warning, "recv error: fd is : %d", fd);
            close(fd);
            _Epoller->Update(EPOLL_CTL_DEL,_listensock.fd(),0);
        }
    }
    void Dispatcher(epoll_event * all ,int sz)
    {
        lg(Info,"DISPATCHER START");
        for(int i=0;i<sz;i++)
        {
             
            if(all[i].events&EPOLLIN)
            {
                if(all[i].data.fd==_listensock.fd())
                {
                    //有新链接
                    lg(Info,"Get new link!");
                    Accepter();
                }
                else
                {
                    //从已有的链接收到数据
                    Recver(all[i].data.fd,i);
                }
            }
        }
    }
    void Start()
    {
        
        _listensock.Socket();
        _listensock.Bind(_port);
        _listensock.Listen();
        
        _Epoller->Update(EPOLL_CTL_ADD,_listensock.fd(),care_events);
        epoll_event _ready_list[_sz];
        
        int timeout=3000; //3000ms;
        while(1)
        {
            int n=_Epoller->Wait(_ready_list,_sz);
            cout<<n<<endl;
            if(n==0)
            {
                lg(Info,"timeout");
            }
            else if(n==-1)
            {
                lg(Error,"epoll error:>%s",strerror(errno));
                break;
            }
            else
            {//有至少一个fd上的事件就绪
               Dispatcher(_ready_list,n);
            }
        }


    }
    
    private:
    uint16_t _port;
    sock _listensock;
    std::shared_ptr<Epoller> _Epoller;
};