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

bool requestFile(SOCKET socket, char* fileName);
int receiveFile(SOCKET hSocket, char* fileName);


int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	SOCKET hSocket;
	char message[BUF_SIZE] = {0, };
	char fileName[BUF_SIZE] = {0, };
	int strLen;
	char* ip = "127.0.0.1";
	char* port = "9000";
	SOCKADDR_IN servAddr;

	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() Error!");
	}
	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if(hSocket == INVALID_SOCKET)
	{
		ErrorHandling("socket() Error!");
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(ip);
	servAddr.sin_port = htons(atoi(port));

	if(connect(hSocket, (sockaddr*) &servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		ErrorHandling("connect() Error!");
	}

	requestFile(hSocket, fileName);
	receiveFile(hSocket, fileName);

	closesocket(hSocket);
	WSACleanup();
	return 0;
}

bool requestFile(SOCKET socket, char* fileName)
{
	int inputLen = -1;
	int sendLen = 0;
	int ret = 0;
	printf("file Name :");
	scanf("%s", fileName);
	while(fileName[inputLen++]);
	while(sendLen < inputLen)
	{
		ret = send(socket, fileName, inputLen, 0);
		if(ret == SOCKET_ERROR)
		{
			ErrorHandling("send() Error!");
		}
		else
		{
			sendLen += ret;
		}
	}
	return ret;
}

int receiveFile(SOCKET hSocket, char* fileName)
{
	char buf[BUF_SIZE] = {0, };
	int ret = 0;
	FILE* fp = fopen(fileName, "wb");
	if(fp == NULL)
	{
		ErrorHandling("fopen Error!");
	}

	while(ret = recv(hSocket, buf, BUF_SIZE, 0))
	{
		if(ret == SOCKET_ERROR)
		{
			ErrorHandling("recv() Error!");
		}
		fwrite((void*) buf, 1, ret, fp);
	}

	ret = send(hSocket, "Thank you", 10, 0);
	if(ret == SOCKET_ERROR)
	{
		ErrorHandling("recv() Error!");
	}

	if(fp)
	{
		fclose(fp);
	}
	return ret;
}