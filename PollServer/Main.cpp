#include "PollServer.hpp"
#include <memory>
int main()
{
    std::unique_ptr<PollServer> svr(new PollServer(8889));
    svr->Start();
}