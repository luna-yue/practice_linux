#include "EpollServer.hpp"
int main()
{
    std::shared_ptr<EpollServer> tmp(new EpollServer(9000)  );
    tmp->Start();
}