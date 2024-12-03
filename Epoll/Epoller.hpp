#include"Log.hpp"
#include<sys/epoll.h>
#include<string.h>
class Epoller{
    public:
    Epoller(){
        _epfd=epoll_create(1024);
    }
    void Update(int op,int fd, uint32_t event){
           if(op==EPOLL_CTL_DEL)
           {
             int n=epoll_ctl(_epfd,op,fd,nullptr);
             if(n!=0)
             {
                lg(Error,"EPOLL_CTL_DEL Error :> %s",strerror(errno));
             }
           }
           else 
           {
              epoll_event tmp;
              tmp.data.fd=fd;
              tmp.events=event;
              int n=epoll_ctl(_epfd,op,fd,&tmp);
              if(n!=0)
             {
                lg(Error,"EPOLL_CTL Error :> %s",strerror(errno));
             }
           }
    }
    size_t Wait(epoll_event * events,int maxsz){
        int n= epoll_wait(_epfd,events,maxsz,timeout);
        if(n==-1)
        {
            lg(Error,"epoll_wait error :>%s",strerror(errno));
            return 0;
        }
        return n;
    }
    ~Epoller(){
         if(_epfd>0)
         close(_epfd);
    }
    private:
    int timeout=3000;
    int _epfd;
};