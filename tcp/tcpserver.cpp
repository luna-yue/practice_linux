#include"tcpserverd.hpp"
int main(int argv,char * argc[])
{
    if(argv!=2)
    {
        cout<<"need a port"<<endl;
        exit(-1);
    }    
    lg.ch_printmethod(Onefile);
    tcpserver x(stoi(argc[1]));
    x.init_server();
    x.start_server();
}