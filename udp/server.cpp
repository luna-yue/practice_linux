#include "Log.hpp"
#include  "udpserver.hpp"
int main()
{
    udpserver x;
    x.init();
    x.run();
}