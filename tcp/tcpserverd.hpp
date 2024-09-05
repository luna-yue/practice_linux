#pragma once
#include<string>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unordered_set>
#include"Log.hpp"
#include"threadpool.h"
#include"dictionary.hpp"
#include"Deamon.hpp"
using namespace std;
string defalut_ip ="0.0.0.0";

int backlog=10;
int bufsz=1024;
dictionary dict;
class client_info
{
  public:
  client_info(){}
  //client_info(uint16_t p,string& _ip,int fd):port(p),ip(_ip),sockfd(fd){}
  uint16_t port;
   in_addr ip;
  int sockfd;
};
void * solve(void * args)
{
   client_info* p=(client_info*)args;
   char buf[bufsz];
   
   int n=read(p->sockfd,buf,bufsz);
   if(n>0)
   {
      buf[n]='\0';
      lg(Info,"received:>%s",buf);
      
      string ans=dict.translation(buf);
      write(p->sockfd,ans.c_str(),ans.size());
   }
   else if(n==0)
   {
       lg(Info,"a client quit, ip: >%s",inet_ntoa(p->ip));
       return 0;
   }
   else
   {
     lg(Warning, "read error, sockfd: %d, client ip: %s, client port: %d", p->sockfd, inet_ntoa(p->ip),p->port);
   }
   
   close(p->sockfd);
   return nullptr;
}
class tcpserver{
  public:
  tcpserver(uint16_t _port,string _ip=defalut_ip):port(_port),ip(_ip){}
  //1.创建socket setsockopt
    //2.bind
    //3.listen
    //4.accept
  void init_server()
  {
    
    //使用ipv4 AF_INET ,tcp 使用流式传输 SOCK_STREAM，
    listen_socket=socket(AF_INET,SOCK_STREAM,0);
    dict.init();
    if(listen_socket<0)
    {lg(Fatal,"socket create error:>%s",strerror(errno));
     exit(-1);
    }    
    lg(Info,"socket create done");
    int opt=1;
    //SO_REUSEADDR只有针对time-wait链接(linux系统time-wait连接持续时间为1min)，确保server重启成功的这一个作用
    //SO_REUSEPORT使用场景：linux kernel 3.9 引入了最新的SO_REUSEPORT选项，使得多进程或者多线程创建多个绑定同一个ip:port的监听socket，提高服务器的接收链接的并发能力,程序的扩展性更好；此时需要设置SO_REUSEPORT（注意所有进程都要设置才生效）。
    if(setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &opt, sizeof(opt)))
    {lg(Fatal,"setsockopt error:>%s",strerror(errno));
     exit(-1);
    } 
    lg(Info,"setsockopt done");
    sockaddr_in x;
    bzero(&x,sizeof(x));
    x.sin_family=AF_INET;
    x.sin_port=htons(port);//把short 转成网络字节顺序
    x.sin_addr.s_addr=inet_addr(ip.c_str());
    if(bind(listen_socket,(const sockaddr*)&x,(socklen_t)sizeof(x)))
    {
     lg(Fatal,"bind error:>%s",strerror(errno));
     exit(-1);
    }
    lg(Info,"bind done");
    //limit the number of outstanding connections in the socket's  listen  queue.
    if(listen(listen_socket,backlog))
    {
        lg(Fatal,"listen error:>%s",strerror(errno));
        exit(-1);
    }
    lg(Info,"listen done");
  }  
  void start_server()
  {
    //使用线程池来
    Deamon();
    threadpool x(10,solve);
    x.start();
    lg(Info,"server start");
    sockaddr_in tmp;
    bzero(&tmp,sizeof(tmp));
    socklen_t len=sizeof(tmp);
    while(1)
    {
      
      int client_fd=accept(listen_socket,(sockaddr*)&tmp,&len);
      if(client_fd<0)
      {
        lg(Fatal,"accept error:>%s",strerror(errno));
        continue;
      }
      
      string userip=inet_ntoa((tmp.sin_addr));
      if(user.find(userip)==user.end())
      {
        user.insert(userip);
      }
      
      client_info mem;
      mem.port=ntohs(tmp.sin_port);
      mem.ip=tmp.sin_addr;
      mem.sockfd=client_fd;
      lg(Info, "get a new link..., sockfd: %d, client ip: %s, client port: %d", mem.sockfd, inet_ntoa(mem.ip), mem.port);
      x.push(&mem);
    }
  }
  private:
  string ip;
  int listen_socket;
  uint16_t port;
  unordered_set<string> user;
};