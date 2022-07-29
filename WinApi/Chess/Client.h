#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
using namespace std;

class Client
{
private:
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	SOCKET Connection;

public:
	Client(char ip[16])
	{
		if (WSAStartup(DLLVersion, &wsaData) != 0)
		{
			std::cout << "Error" << std::endl;
			exit(1);
		}

		addr.sin_addr.s_addr = inet_addr(ip);
		addr.sin_port = htons(1111);
		addr.sin_family = AF_INET;

		Connection = socket(AF_INET, SOCK_STREAM, NULL);
		if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
		{
			std::cout << "Error connection" << std::endl;
		}

		MessageBox(NULL, "Подключение прошло успешно!", "Подключено!", MB_OK);

		int sizeMessage;

		recv(Connection, (char*)&sizeMessage, sizeof(int), NULL);
		recv(Connection, (char*)&cb, sizeMessage, NULL);
	}
};