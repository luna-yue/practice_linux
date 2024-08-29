#pragma once
#include "Log.hpp"
#include <iostream>
#include <string>
#include <strings.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <functional>
Log lg;
#define size 1024
class udpserver{
    public:
    udpserver()
    {    
        lg(Info,"enter  port");
        std::cin>>port;
        lg(Info,"%s",ip.c_str());
        lg(Info,"%d",port);
    }
    void init(){
        lg(Info,"server init start");
    socketfd=socket( PF_INET,SOCK_DGRAM,0);
    if(socketfd<0)
     lg(Fatal,"socket create error, socker fd:%d ",socketfd);
    lg(Info,"%d",socketfd);
    //isrunning=true;
     sockaddr_in x;
     bzero(&x,sizeof(x));
     x.sin_family=AF_INET;
     x.sin_port=htons(port);
     x.sin_addr.s_addr=inet_addr("0.0.0.0");

     int tmp= bind(socketfd,(const sockaddr *) (&x),sizeof(x));
     lg(Info,"%d",tmp);
    if(tmp!=0)
    {
        lg(Fatal,"bind error,errno :%d,reason: %s",errno,strerror(errno));
        exit(-1);
    }
    lg(Info,"server init success");
 }
    void run()
    {lg(Info,"server run start");
        isrunning =1;
        sockaddr_in x;
        int sz=size-1;
        char buf[size-1];
      while (isrunning)
      {
         int n=recvfrom(socketfd,buf,size-1,0,(sockaddr *)&x,(socklen_t*)&sz);
         //lg("Info","%d",n);
         std::cout<<n<<std::endl;
         if(n>0)
         {
              buf[n]='\0';
         lg(Info,"server received: %s",buf);
         
         sendto(socketfd,buf,n,0,(const sockaddr*)&x,(socklen_t)sz);
         }
         
      }
    }
    private:
    uint16_t port;
    std::string ip;
    int socketfd;
    bool isrunning;
};