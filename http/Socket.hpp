#include <iostream>
#include <string>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "Log.hpp"
using namespace std;
enum{
    SocketErr = 2,
    BindErr,
    ListenErr,
};
const int backlog=10;
class sock{
    public:
    sock()
    {
    }
    ~sock(){}
    void Socket(){
       sockfd=socket(AF_INET, SOCK_STREAM, 0);
       if(sockfd<0)
       {
        lg(Fatal, "socket error, %s: %d", strerror(errno), errno);
         exit(SocketErr);
       }

       //setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, buf, sizeof(buf));
    }
    void Bind(uint16_t port){
        struct sockaddr_in local;
        memset(&local, 0, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(port);
        local.sin_addr.s_addr = INADDR_ANY;
        if(bind(sockfd, (struct sockaddr *)&local, sizeof(local)) < 0)
        {
            lg(Fatal, "bind error, %s: %d", strerror(errno), errno);
            exit(BindErr);
        }
    }
    void Listen()
    {
        if(listen(sockfd,backlog)<0)
        {
            lg(Fatal, "listen error, %s: %d", strerror(errno), errno);
            exit(ListenErr);
        }
    }
    int Accept(string * ip,uint16_t *port)
    {//输出型参数
          struct sockaddr_in peer;
        socklen_t len = sizeof(peer);
        int newfd = accept(sockfd, (struct sockaddr*)&peer, &len);
        if(newfd<0)
        {
            lg(Warning, "accept error, %s: %d", strerror(errno), errno);
            sleep(1000);
            return -1;
        }
        char ipstr[64];
        inet_ntop(AF_INET, &peer.sin_addr, ipstr, sizeof(ipstr));
        *ip = ipstr;
        *port = ntohs(peer.sin_port);
        return newfd;
    } 
    bool Connect(const string&ip,uint16_t port)
    {
        struct sockaddr_in peer;
        memset(&peer, 0, sizeof(peer));
        peer.sin_family = AF_INET;
        peer.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &(peer.sin_addr));
        if(connect(sockfd,(struct sockaddr*)&peer,sizeof(peer)))
        return false;
    return true;
    }
    void Close()
    {
        close(sockfd);
    }
    int fd()
    {
        return sockfd;
    }
    //char buf[1024];
    int sockfd;
};