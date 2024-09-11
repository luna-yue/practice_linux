#include <iostream>
#include <string>
#include <ctime>
#include <cassert>
#include <unistd.h>
#include<string.h>
#include<errno.h>
#include "Socket.hpp"
#include "Protocol.hpp"
using namespace std;
bool check(const string& s)
{
    if(s.find("\n")!=string::npos)
    {
        //cout<<"enter"<<endl;
        int pos1=s.find("\n");
        int pos2=s.rfind("\n");
       //根据len\ncontent\n的协议 完整报文至少有两个\n
        if(pos1!=pos2)
        return true;
       
    }
    return false;
}
int main(int argc,char * argv[])
{
    //cout<<1<<endl;
   if(argc!=3)
   {
    lg(Fatal,"enter ip & port");
    exit(-1);
   }
   sock socket_;
   string ip=argv[1];
   uint16_t port=stoi(argv[2]);
   socket_.Socket();
   bool r=socket_.Connect(ip.c_str(),port);
   //cout<<1<<endl;
   if(!r)
   {
    lg(Fatal,"connect error:%s",strerror(errno));
   }
   const string opers = "+-*/";
   //cout<<1<<endl;
   srand(time(nullptr) ^ getpid());
   string stream;
   for(int i=1;1;i++)
   {
       /*std::cout << "===============第" << i<< "次测试....., " << "===============" << std::endl;
        int x = rand() % 100 + 1;
        usleep(1234);
        int y = rand() % 100;
        usleep(4321);
        char oper = opers[rand()%opers.size()];*/
        int x,y;
        char oper;
        cout<<"输入 x +-*/ y"<<endl;
        cin>>x>>oper>>y; 
        cout<<x<<" "<<oper<<" "<<y<<"=?"<<endl;
        assert(oper=='+'||oper=='-'||oper=='*'||oper=='/');
        request req(x,y,oper);
        string package;
        req.Serialize(&package);
        package=encode(package);
        //cout<<package<<endl;
        //发送x+y 报文
        int result=write(socket_.sockfd,package.c_str(),package.size());
        if(result<0)
        lg(Fatal,"write error :%s",strerror(errno));
        //cout<<1<<endl;
        
        char buf[1024];
        memset(buf,0,sizeof(buf));
        //读结果报文
        int flag=1;
        int cnt=0;
        while(1){
        int n=read(socket_.sockfd,buf,1024);
        
        if(n>0)
        {
           buf[n]='\0';
           //cout<<buf<<endl;
            stream+=buf;
            //报文完整性检查
            if(!check(stream))
            {
               continue;
            }
            string content;
            bool r=decode(stream,&content);
            if(!r)
            assert(r);
            
            flag=0;
            assert(r);
            response res;
            r=res.Deserialize(content);
            assert(r);
            cout<<"result::>"<<res.result<<" result code(0表示可信)"<<res.code<<endl;
            break;
        }
        else {break;}
        }
   }
   socket_.Close();
}