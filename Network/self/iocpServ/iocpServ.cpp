// iocpClnt.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <process.h>

#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define BUF_SIZE 1024
#define PORT "9000"
#define READ 3
#define WRITE 5

typedef struct
{
	SOCKET hClntSock;
	SOCKADDR_IN clntAdr;
}PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

typedef struct
{
	OVERLAPPED overlapped;
	WSABUF wsaBuf;
	char buffer[BUF_SIZE];
	int rwMode;	//READ OR WRITE
}PER_IO_DATA, *LPPER_IO_DATA;

unsigned int WINAPI EchoThreadMain(LPVOID CompletionPortIO);

void ErrorHandling(char* msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}


int _tmain(int argc, _TCHAR* argv[])
{

	WSADATA wsaData;
	HANDLE hComPort;
	SYSTEM_INFO sysInfo;
	LPPER_IO_DATA ioInfo;
	LPPER_HANDLE_DATA handleInfo;

	SOCKET hServSock;
	SOCKADDR_IN servAddr;

	DWORD recvBytes = 0, flag = 0;

	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() error!");
	}

	hComPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	GetSystemInfo(&sysInfo);
	for(int i = 0; i < sysInfo.dwNumberOfProcessors; ++i)
	{
		_beginthreadex(NULL, 0, EchoThreadMain, (LPVOID) hComPort, 0, NULL);
	}

	hServSock = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(PORT));

	if(bind(hServSock, (SOCKADDR*) &servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		ErrorHandling("bind() error!");
	}

	if(listen( hServSock, 5 ) == SOCKET_ERROR)
	{
		ErrorHandling("listen() error!");
	}
	
	while(1)
	{
		SOCKET hClntSock;
		SOCKADDR_IN clntAddr;
		int addrLen = sizeof(clntAddr);
		hClntSock = accept(hServSock, (SOCKADDR*) &clntAddr, &addrLen);
		if(hClntSock == INVALID_SOCKET)
		{
			ErrorHandling("accept() error!");
		}
		handleInfo = (LPPER_HANDLE_DATA) malloc(sizeof(PER_HANDLE_DATA));
		handleInfo->hClntSock = hClntSock;
		memcpy(&( handleInfo->clntAdr ), &clntAddr, addrLen);

		CreateIoCompletionPort((HANDLE) hClntSock, hComPort, (DWORD) handleInfo, 0);

		ioInfo = (LPPER_IO_DATA) malloc(sizeof(PER_IO_DATA));
		memset(&( ioInfo->overlapped ), 0, sizeof(OVERLAPPED));
		ioInfo->wsaBuf.len = BUF_SIZE;
		ioInfo->wsaBuf.buf = ioInfo->buffer;
		ioInfo->rwMode = READ;
		if(WSARecv(handleInfo->hClntSock, &( ioInfo->wsaBuf ), 1, &recvBytes, &flag, &( ioInfo->overlapped ), NULL)
		   == SOCKET_ERROR)
		{
			ErrorHandling("WSARecv() error!");
		}
	}
	getchar();
	return 0;
}
