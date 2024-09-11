#include"Servercal.hpp"
#include"Tcpserver.hpp"
#include<unistd.h>
int main(int argc,char * argv[])
{
   if(argc!=2)
   exit(0);
    lg.ch_printmethod(Onefile);
    uint16_t port = std::stoi(argv[1]);
    Servercal cal;
    Tcpserver *tsvp = new Tcpserver(port, std::bind(&Servercal::Cal, &cal, std::placeholders::_1));
    tsvp->init_server();
    
    daemon(0, 0);
    tsvp->start_server();
    
}