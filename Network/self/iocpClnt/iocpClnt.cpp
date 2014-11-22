// iocpClnt.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define BUF_SIZE 1024
#define IP "127.0.0.1"
#define PORT "9000"

void ErrorHandling(char* msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}


int _tmain(int argc, _TCHAR* argv[])
{

	WSADATA wsaData;
	SOCKET hSocket;
	
	SOCKADDR_IN servAddr;
	DWORD sendBytes = 0, readBytes = 0;

	WSABUF dataBuf;
	char msg[BUF_SIZE] = {0, };
	

	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() error!");
	}

	hSocket = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if(hSocket == INVALID_SOCKET)
	{
		ErrorHandling("WSASocket() error!");
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(IP);
	servAddr.sin_port = htons(atoi(PORT));
	
	if(connect(hSocket, (SOCKADDR*) &servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		ErrorHandling("connect() error!");
	}
	else
	{
		puts("Connected......");
	}

	while(1)
	{
		fputs("Input message(Q to quit): ", stdout);
		fgets(msg, BUF_SIZE, stdin);
		if(!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
		{
			break;
		}

		sendBytes = strlen(msg);
		send(hSocket, msg, sendBytes, 0);
		readBytes = 0;
		while(readBytes < sendBytes)
		{
			readBytes += recv(hSocket, &msg[readBytes], BUF_SIZE - 1, 0);
		}
		msg[readBytes] = 0;
		printf("Message from server: %s", msg);
	}

	closesocket(hSocket);
	WSACleanup();
	return 0;

	/*
	WSAEVENT evObj;
	WSAOVERLAPPED overlapped;
	evObj = WSACreateEvent();
	memset(&overlapped, 0, sizeof(overlapped));
	overlapped.hEvent = evObj;
	dataBuf.len = strlen(msg) + 1;
	dataBuf.buf = msg;

	//WSARecv(hSocket, &dataBuf, 1, &recvBytes, 0, &overlapped, NULL);

	if(WSASend(hSocket, &dataBuf, 1, &sendBytes, 0, &overlapped, NULL) == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSA_IO_PENDING)
		{
			puts("Background data send");
			WSAWaitForMultipleEvents(1, &evObj, TRUE, WSA_INFINITE, FALSE);
			WSAGetOverlappedResult(hSocket, &overlapped, &sendBytes, TRUE, NULL);
		}
		else
		{
			ErrorHandling("WSASend() error!");
		}
	}
	
	printf("Send data size: %d \n", sendBytes);
	WSACloseEvent(evObj);
	closesocket(hSocket);
	WSACleanup();

	getchar();
	return 0;
	*/
}

