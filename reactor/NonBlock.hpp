#pragma once

#include <unistd.h>
#include <fcntl.h>

void SetNonBlock(int sock)
{
    int fl = fcntl(sock, F_GETFL);
    if (fl < 0)
        exit(-1);
    fcntl(sock, F_SETFL, fl | O_NONBLOCK);
}