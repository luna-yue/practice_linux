#include"HttpServer.hpp"
int main(int argc,char * argv[])
{
   if(argc!=2)
   {
    cout<<"enter port"<<endl;
   }    
   HttpServer x((uint16_t)stoi(argv[1]));
   x.start();
}