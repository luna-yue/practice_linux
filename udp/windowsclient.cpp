//
// Created by JinxBIGBIG on 2022/8/3.
//

#include <iostream>
#include <WS2tcpip.h>

using namespace std;

#pragma comment(lib,"ws2_32.lib")

int main()
{

    WSADATA wdata;

    WORD wVersion;

    wVersion = MAKEWORD(2, 2);

    WSAStartup(wVersion, &wdata);

    if (HIBYTE(wdata.wVersion) != 2 || LOBYTE(wdata.wVersion) != 2)
    {
        return -1;
    }

    sockaddr_in sClient;

    sClient.sin_family = AF_INET;
    sClient.sin_port = htons(50001);

    //inet_pton(AF_INET, "127.0.0.1", &sClient.sin_addr);
    sClient.sin_addr.S_un.S_addr = inet_addr("49.232.249.2");

    SOCKET psock = socket(AF_INET, SOCK_DGRAM, 0);

    int len = sizeof(sClient);

    char sendBuf[128];
    while (1)
    {

        memset(sendBuf, 0, sizeof(sendBuf));

        cout << "Please input:";

        cin.getline(sendBuf, 64);
        sendto(psock, sendBuf, sizeof(sendBuf), 0, (sockaddr*)&sClient, len);

    }
    return 0;
}
