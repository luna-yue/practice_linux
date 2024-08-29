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
int size =1024;
int main(int argv, char * argc[])
{
    if(argv!=3)
    {
       lg(Fatal,"enter a valid ip and port") ;
       exit (-1);
    }
    std::string ip=argc[1];
    
    sockaddr_in x;
    bzero(&x,sizeof(x));
     x.sin_family=AF_INET;
     x.sin_port=htons(std::stoi(argc[2]));
     x.sin_addr.s_addr=inet_addr(ip.c_str());
     int socketfd=socket(PF_INET,SOCK_DGRAM,0);
     std::string message;
     char buf[size];
     int sz=sizeof(x);
     while(1)
     {
         std::cout<<"please enter$";
         getline(std::cin,message);
         sendto(socketfd,message.c_str(),message.size(),0,(const sockaddr*)(&x),(socklen_t)sz);
         int n=recvfrom(socketfd,buf,size-1,0,(sockaddr* )(&x),( socklen_t*)&sz);
         if(n>0)
         {
            buf[n]='\0';
            lg(Info,"received from server : %s",buf);
         }
     }
}