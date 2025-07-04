#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;
const std::string nullfile = "/dev/null";

void Deamon(const string& cwd="")
{
    signal(SIGCLD, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);
    signal(SIGSTOP, SIG_IGN);
    if(fork()>0)
    exit(0);
    setsid();
    if (!cwd.empty())
        chdir(cwd.c_str());
    int fd = open(nullfile.c_str(), O_RDWR);
    if(fd > 0)
    {
        dup2(fd, 0);
        dup2(fd, 1);
        dup2(fd, 2);
        close(fd);
    }
}