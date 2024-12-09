#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>
#include"Log.hpp"
using namespace std;
//采用 长度\n内容\n 的方式进行编码 验证收到报文的完整性
const string blank_space_sep = " ";
const string protocol_sep = "\n";
string encode(const string& content)
{
    string package=to_string(content.size());
    
    package+=protocol_sep;
    package+=content;
    package+=protocol_sep;
    return package;
}
bool decode(string &package ,string * content )
{
   int pos=package.find(protocol_sep);
   if(pos==string::npos)
   return false;
   //cout<<pos<<endl;
   string tmp=package.substr(0,pos);
   //cout<<"will stoi:>"<<tmp<<" "<<tmp.size()<<endl;
   int sz=stoi(tmp);
   //cout<<"sz"<<sz<<endl;
   int total_len=tmp.size()+sz+2;
   //cout<<package.size()<<" "<<total_len<<endl;
   //return 0;
   if(package.size()<total_len)
   return false;//报文不完整 因为至少为 内容长度+'\n'*2+ tmp的长度
   *content=package.substr(pos+1,pos+sz);
   //cout<<*content<<endl;cout<<"done"<<endl;
   package.erase(0,total_len);
   return true;
}
class request{
    public:
    request(int data1, int data2, char oper):x(data1),y(data2),op(oper) 
    {

    }
    request(){}
    ~request(){

    }
    bool Serialize(string *out)
    {
        Json::Value root;
        root["x"]=x;
        root["y"]=y;
        root["op"]=op;
        Json::StyledWriter w;
        *out=w.write(root);
        return true;
    }
    bool Deserialize(const string&in)
    {
        Json::Value root;
        Json::Reader r;
        r.parse(in,root);//解析字符串
        x=root["x"].asInt();
        y=root["y"].asInt();
        op=root["op"].asInt();
        return true;
    }
    
    int x;
    int y;
    char op;
};
class response{
   public:
   response(int res,int c):result(res),code(c){}
   response(){}
   ~response(){}
   bool Serialize(string * out)
   {
    Json::Value root;
    root["result"]=result;
    root["code"]=code;
    Json::StyledWriter w;
    *out=w.write(root);
    return true;
   }
   bool Deserialize(const string&in)
   {
        Json::Value root;
        Json::Reader r;
        r.parse(in, root);

        result = root["result"].asInt();
        code = root["code"].asInt();
        return true;
   }
    
   int result;
   int code;//0表示可信
};
