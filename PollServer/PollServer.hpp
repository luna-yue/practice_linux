#include "Socket.hpp"
#include "Log.hpp"
#include<string>
#include <poll.h>
using namespace std;
static const int fd_max =64;
static const int non_event =0;

class PollServer{
    public:
    PollServer(uint16_t port):_port(port){}
    ~PollServer()
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
        int pos=-1;
        for(int i=0;i<fd_max;i++)
        {
            if(_fd[i].fd==-1)
            {
                pos=i;
                break;
            }
        }
        if(pos!=-1)
        {
           _ip[pos]=ip;
           _fd[pos].fd=n;
           _fd[pos].events=POLLIN;
           _fd[pos].revents = non_event;
        }
        else
        {
            lg(Warning,"Server full");
            close(n);
        }
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
            _fd[pos].fd = -1;
        }
        else 
        {
            lg(Warning, "recv error: fd is : %d", fd);
            close(fd);
            _fd[pos].fd = -1;
        }
    }
    void Dispatcher()
    {
        lg(Info,"DISPATCHER START");
        for(int i=0;i<fd_max;i++)
        {
            if(_fd[i].fd==-1)
            continue;
            if(_fd[i].revents&POLLIN)
            {
                if(_fd[i].fd==_listensock.fd())
                {
                    //有新链接
                    lg(Info,"Get new link!");
                    Accepter();
                }
                else
                {
                    //从已有的链接收到数据
                    Recver(_fd[i].fd,i);
                }
            }
        }
    }
    void Start()
    {
        for(int i=0;i<fd_max;i++)
        {
            _fd[i].fd=-1;
            _fd[i].events = non_event;
            _fd[i].revents = non_event;
        }
        _listensock.Socket();
        _listensock.Bind(_port);
        _listensock.Listen();
        _fd[0].fd=_listensock.fd();
        _fd[0].events=POLLIN;
        //当有新连接到来 存在sock的缓冲区中，同时读事件就绪 
        int timeout=3000; //3000ms;
        while(1)
        {
            int n=poll(_fd,fd_max,timeout);
            //cout<<n<<endl;
            if(n==0)
            {
                lg(Info,"timeout");
            }
            else if(n==-1)
            {
                lg(Error,"poll error:>%s",strerror(errno));
                break;
            }
            else
            {//有至少一个fd上的事件就绪
               Dispatcher();
            }
        }


    }
    
    private:
    uint16_t _port;
    sock _listensock;
    pollfd _fd[fd_max];
    string _ip[fd_max];
    
};