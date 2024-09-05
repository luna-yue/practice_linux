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
using namespace std;
int main(int argc , char * argv[])
{
    if(argc!=3)
    {
       lg(Fatal,"enter a valid ip and port");
       exit(-1);
    }
    string ip=argv[1];
    uint16_t port=stoi(argv[2]);
    sockaddr_in x;
    x.sin_addr.s_addr=inet_addr(ip.c_str());
    x.sin_family=AF_INET;
    x.sin_port=htons(port);
   
        int sockfd=socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd<0)
        lg(Error,"socket create error");
        
        char buf[4096];
        string message;
        
 while(1)
    {
      int cnt=5;
      int reconnect=0;
      do{
        sockfd=socket(AF_INET, SOCK_STREAM, 0);
      int n=connect(sockfd,(sockaddr*)&x,(socklen_t)sizeof(x));
        if(n<0)
        {
          lg(Error,"connect  error:>%s try to reconnect",strerror(errno));
          cnt--;
          reconnect=1;
          sleep(2);
        }
        else
        reconnect=0;
      }
      while(cnt>0&&reconnect);
      if(reconnect)
      {
        lg(Fatal,"can not connect server %s",strerror(errno));
        close(sockfd);
        exit(-1);
      }
      cout<<"please enter#";
      cin>>message;
      //cout<<message<<endl;
      int n=write(sockfd,message.c_str(),message.size());
      //cout<<n<<endl;
      if(n<0)
      lg(Fatal,"write error %s",strerror(errno));
      n=read(sockfd,buf,4096-1);
      //cout<<n<<endl;
      if(n<0)
      lg(Fatal,"read error %s",strerror(errno));
      buf[n]='\0';
      cout<<buf<<endl;
      close(sockfd);
    }
   
}