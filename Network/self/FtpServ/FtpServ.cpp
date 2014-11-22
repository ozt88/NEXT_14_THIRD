// self.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define BUF_SIZE 1024

void ErrorHandling(char* msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

int FileSend(SOCKET socket);

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	char message[BUF_SIZE];
	int strLen;
	char* port = "9000";
	SOCKADDR_IN servAddr, clntAddr;
	int servAdrSize = sizeof(servAddr), clntAdrSize = sizeof(clntAddr);

	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() Error!");
	}
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if(hServSock == INVALID_SOCKET)
	{
		ErrorHandling("socket() Error!");
	}

	memset(&servAddr, 0, servAdrSize);
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(port));

	if(bind(hServSock, (sockaddr*) &servAddr, servAdrSize)
	   == SOCKET_ERROR)
	{
		ErrorHandling("bind() Error!");
	}
	if(listen(hServSock, 5) == SOCKET_ERROR)
	{
		ErrorHandling("listen() Error!");
	}

	hClntSock = accept(hServSock, (sockaddr*) &clntAddr, &clntAdrSize);
	if(hClntSock == INVALID_SOCKET)
	{
		ErrorHandling("accept() Error!");
	}

	FileSend(hClntSock);

	closesocket(hClntSock);
	closesocket(hServSock);
	WSACleanup();
	return 0;
}


int FileSend(SOCKET socket)
{
	char fileName[BUF_SIZE] = {0, };
	char buf[BUF_SIZE] = {0, };
	int ret = 0;
	int length = 0;

	ret = recv(socket, fileName, BUF_SIZE, 0);
	if(ret == SOCKET_ERROR)
	{
		ErrorHandling("recv() Error!");
	}


	FILE* fp = fopen(fileName, "rb");
	if(fp == NULL)
	{
		ErrorHandling("fopen() Error!");
	}

	while(length = fread((void*)buf, sizeof(char), BUF_SIZE, fp))
	{
		ret = 0;
		while(length > ret)
		{
			ret = send(socket, (char*)buf, length, 0);
			if(ret == SOCKET_ERROR)
			{
				ErrorHandling("send() Error!");
			}
			length -= ret;
		}
	}

	shutdown(socket, SD_SEND);
	ret = recv(socket, (char*) buf, BUF_SIZE, 0);
	if(ret == SOCKET_ERROR)
	{
		ErrorHandling("recv Error!");
	}
	printf("Msg From Clnt : %s\n", buf);

	if(fp)
	{
		fclose(fp);
	}

	return ret;
}