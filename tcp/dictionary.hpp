#include<unordered_map>
#include<string>
#include<iostream>
#include<fstream>
#include<string.h>
#include<map>
#include "Log.hpp"
using namespace std;
string path ="./dictionary_data.txt";
bool spilt(string & data,string * japanese, string * chinese)
{
  //cout<<0<<endl;
    int pos=data.find(":");
    if(pos==string::npos)
    return false;
    int ed=data.size();
    //while(data[ed]==' ')
   // ed--;
    
    *chinese=data.substr(pos+2,ed-pos-2-2);
    *japanese=data.substr(0,pos);
    //cout<<*(japanese)<<endl;
    //cout<<1<<endl;
    return true;
}
class dictionary{
  public:
    void init()
    {
        ifstream in(path);
        if(!in.is_open())
        {
          lg(Fatal,"ifstream open %s error:>%s",path.c_str(),strerror(errno));
          exit(-1);
        }
        string line;
        while(getline(in,line))
        {
          string a,b;
          spilt(line,&a,&b);
          //cout<<b<<endl;
          
         // cout<<a<<b<<endl;
         // cout<<b<<a<<endl;
          dict[b]=a; 
        }
        

    }
    string translation(const string& x)
    {
      //cout<<x<<endl;
      auto it=dict.find(x);
      if(it==dict.end())
      {
        lg(Error,"%s no found",x.c_str());
        return "unknown";
      }
      return it->second;
    }
private:
    map<string,string>dict;
};