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

int calculator(SOCKET sock);

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	SOCKET hSocket;
	char message[BUF_SIZE];
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

	calculator(hSocket);

	closesocket(hSocket);
	WSACleanup();
	return 0;
}

int getCalculateInput(char* result, int* length)
{
	char buffer[BUF_SIZE] = {0, }; 
	int operandCnt = 0;
	fputs("operand cont: ", stdout);
	scanf("%d", &operandCnt);
	int* operands = (int*) malloc(sizeof(int)*operandCnt);
	memset(operands, 0, sizeof(int)*operandCnt);
	sprintf_s(buffer, "%c", ' ');
	for(int i = 0; i < operandCnt; ++i)
	{
		printf("Operand %d : ", i + 1);
		scanf("%d", operands + i);
		sprintf_s(buffer, "%s,%d", buffer, operands[i]);
	}
	fflush(stdin);
	printf("Operator : ");
	scanf("%c", buffer);
	*length = sprintf_s(buffer, "%s#", buffer);

	strcpy(result, buffer);

	return 0;
}

int calculator(SOCKET sock)
{
	char buffer[BUF_SIZE];
	int inputLen = 0;
	int sendLen = 0;
	int ret = 0;
	getCalculateInput(buffer, &inputLen);
	while(sendLen < inputLen)
	{
		ret = send(sock, buffer, inputLen, 0);
		if(ret == SOCKET_ERROR)
		{
			ErrorHandling("send() Error!");
		}
		else
		{
			sendLen += ret;
		}
	}
	
	do
	{
		if(ret = recv(sock, buffer, BUF_SIZE, 0) == SOCKET_ERROR)
		{
			ErrorHandling("recv() Error!");
		}

	}while(ret > 0);

	printf("Result : %s\n", buffer);
	return 0;
}

