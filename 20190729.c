#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return -1;

    if ((serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
        return -1;
        
    WSACleanup();
}