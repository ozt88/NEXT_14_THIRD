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
	fputc('\n',stderr);
	exit(1);
}

int calculator(SOCKET socket);


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

	calculator(hClntSock);

	closesocket(hClntSock);
	closesocket(hServSock);
	WSACleanup();
	return 0;
}




int calculator(SOCKET socket)
{
	char buffer[BUF_SIZE] = {0, }; 
	int operands[BUF_SIZE] = {0, };
	int operandLen = 0;
	if(recv(socket, buffer, BUF_SIZE, 0) == SOCKET_ERROR)
	{
		ErrorHandling("recv() Error!");
	}
	char* operate = strtok(buffer, ", ");
	char* operand;
	while((operand = strtok(NULL, ", ")) != NULL)
	{
		operands[operandLen++] = atoi(operand);
	}
	int result = 0;
	switch(operate[0])
	{
		case '+':
			for(int i = 0; i < operandLen; ++i)
			{
				result += operands[i];
			}
			break;
		case '-':
			for(int i = 0; i < operandLen; ++i)
			{
				result -= operands[i];
			}
			break;
		case '*':
			for(int i = 0; i < operandLen; ++i)
			{
				result *= operands[i];
			}
			break;
		case '%':
			for(int i = 0; i < operandLen; ++i)
			{
				result %= operands[i];
			}
			break;
	}
	itoa(result, buffer, BUF_SIZE);
	if(send(socket, buffer, BUF_SIZE, 0) == SOCKET_ERROR)
	{
		ErrorHandling("send() Error!");
	}
	return 0;
}