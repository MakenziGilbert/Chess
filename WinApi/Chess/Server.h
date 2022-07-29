#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
using namespace std;

class Server
{
private:
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	SOCKET sListen, newConnection;

public:
	Server(char ip[16])
	{
		if (WSAStartup(DLLVersion, &wsaData) != 0)
		{
			std::cout << "Error" << std::endl;
			exit(1);
		}

		addr.sin_addr.s_addr = inet_addr(ip);
		addr.sin_port = htons(1111);
		addr.sin_family = AF_INET;

		sListen = socket(AF_INET, SOCK_STREAM, NULL);
		bind(sListen, (SOCKADDR*)&addr, sizeofaddr);
		listen(sListen, SOMAXCONN);

		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
		if (newConnection == 0)
		{
			std::cout << "Error #2\n";
		}
		else
		{
			MessageBox(NULL, "Подключение прошло успешно!", "Подключено!", MB_OK);

			int sizeMessage = sizeof(cb);
			send(newConnection, (char*)&sizeMessage, sizeof(int), NULL);
			send(newConnection, (char*)&cb, sizeof(cb), NULL);
		}
	}
};