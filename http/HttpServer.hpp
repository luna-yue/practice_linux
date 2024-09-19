#pragma once
#include<iostream>
#include<fstream>
#include"Socket.hpp"
#include"Log.hpp"
#include<pthread.h>
#include<unordered_map>
#include<sys/socket.h>
#include<vector>
#include<sstream>
using namespace std;
const string sep="\r\n";
const string wwwroot="./wwwroot";
const string home_page="index.html";
class HttpServer;
class ClientData{
    public:
    string ip;
    uint16_t port;
    int fd;
    HttpServer * p;
};
class HttpRequest{
   public:
    
    void Deserialize(string req)
    {
        while(1)
        {
           size_t pos=req.find(sep);
           if(pos==string::npos)
           break;//报头以空行结尾 以\r\n换行
           header.push_back(req.substr(0,pos));
           req.erase(0,pos+sep.size());
        }
        text=req;//余下正文；

    }
    void Parse()
    {
        std::stringstream ss(header[0]);
        ss>>method>>url>>http_version;
        file_path=wwwroot;
        if(url=="/"||url=="/index.html")
        {
            file_path+= "/";
            file_path+=home_page;
        }
        else file_path+=url;
        int pos=file_path.rfind(".");
        if(pos==string::npos)suffix=".html";
        else suffix=file_path.substr(pos);
    }
    void DebugPrint()
    {
        for(auto &e:header)
        {
            cout<<"--------------------------------------------"<<endl;
            cout<<e<<endl;
        }
        cout << "method: " << method << endl;
        cout << "url: " << url << endl;
        cout << "http_version: " << http_version << endl;
        cout << "file_path: " << file_path << endl;
        cout<<"suffix: "<<suffix<<endl;
        cout << text << endl;
    }
   vector<string>header;
   string text;
   string method;
   string url;
   string http_version;
   string file_path;
   string suffix;
};
class HttpServer{
    public:
    HttpServer(uint16_t _port):port(_port){}
    void start()
    {
        content_type[".html"]="text/html";
        content_type[".jpg"]="image/jpeg";
        listensocket.Socket();
        listensocket.Bind(port);
        listensocket.Listen();
        while(1)
        {
           ClientData* tmp=new ClientData();
           tmp->fd=listensocket.Accept(&tmp->ip,&tmp->port);
           tmp->p=this;
           pthread_t pid;
           pthread_create(&pid,nullptr,handler,tmp);
        }
    }
    string GetContentType( string&suffix)
    {
        if(!content_type.count(suffix))
        return content_type[".html"];
    else
     return content_type[suffix];
    }
    string ReadContent(const string& path)
    {
        ifstream in(path, ios::binary);
        if(!in.is_open()) return "";

        in.seekg(0, ios_base::end);
        auto len = in.tellg();
        in.seekg(0, ios_base::beg);

        string content;
        content.resize(len);

        in.read((char*)content.c_str(), content.size());
        in.close();
        return content;
    }
    static void * handler(void * args)
    {
        pthread_detach(pthread_self());
        ClientData *pt =static_cast<ClientData*>(args);
        char buf[10240];
        int n=recv(pt->fd,buf,sizeof(buf)-1,0);
        if(n>0)
        {
            buf[n]=0;
            cout<<buf<<endl;
            HttpRequest req;
            req.Deserialize(buf);
            req.Parse();
            req.DebugPrint();
            cout<<pt->ip<<" "<<pt->port<<endl;
            //回应
            string text;
            string response_header;
            text=pt->p->ReadContent(req.file_path);
            if(text.empty())
            response_header="HTTP/1.0 404 NOT FOUND\r\n";
            else
            response_header="HTTP/1.0 200 OK\r\n";
            response_header+="Content-Length: ";
            response_header+=to_string(text.size());
            response_header+="\r\n";
            response_header+="Content-Type: ";
            response_header+=pt->p->GetContentType(req.suffix);
            response_header+="\r\n";
            response_header += "Set-Cookie: name=luna;passwd=asahi";
            response_header += "\r\n";
            string response= response_header;
            response+="\r\n";//报头结束标识
            response+=text;
            send(pt->fd,response.c_str(),response.size(),0);
        }
        delete pt;
        return nullptr;
    }
    private:
    sock listensocket;
    uint16_t port;
    unordered_map<string,string>content_type;
};