#pragma once
#include <functional>
#include <string>
#include <signal.h>
#include "Log.hpp"
#include "Socket.hpp"

using func_t = std::function<std::string(std::string &package)>;
class Tcpserver{
    public:
    Tcpserver(uint16_t port_,func_t callback_)
    :port(port_),callback(callback_){}
    void init_server()
    {
        socket_.Socket();
        socket_.Bind(port);
        socket_.Listen();
         lg(Info, "init server .... done");
        
    }
    void start_server()
    {
        signal(SIGCHLD, SIG_IGN);
        signal(SIGPIPE, SIG_IGN);
        while(1)
        {
            lg(Info,"start server");
            std::string clientip;
            uint16_t clientport;
            int sockfd = socket_.Accept(&clientip, &clientport);
            if (sockfd < 0)
                continue;
            
            lg(Info, "accept a new link, sockfd: %d, clientip: %s, clientport: %d", sockfd, clientip.c_str(), clientport);
            if(fork()==0)
            {
                socket_.Close();
                string stream;
                
                while(1){
                    char buf[1024];
                int n=read(sockfd,buf,sizeof(buf));
               
                
                if(n>0)
                { buf[n]=0;
                //cout<<buf<<endl;
                   stream+=buf;
                   int cnt=1;
                   while(1){
                  string info=callback(stream);
                  
                   if(info.empty())
                   break;
                  int flag=1;
                  //经过检查 我发现write每次只能发送32字节 并不能一次发完 因而采用循环
                  while(flag){
                    flag=0;
                    lg(Debug, "response sz:%d>>>debug, response:\n%s", info.size(),info.c_str());
                    lg(Debug, "debug:\n%s", stream.c_str());
                    
                    int xxx=write(sockfd,info.c_str(),info.size());
                    cout<<"write done:>"<<xxx<<endl;
                    if(xxx<info.size())
                    {info.erase(0,xxx);flag=1;}
                   
                  }
                  cout<<"out"<<endl;
                   }
                   
                }
                else
                break;
                }
            }
        }
    }
    private:
    func_t callback;
    sock socket_;
    uint16_t port;
};