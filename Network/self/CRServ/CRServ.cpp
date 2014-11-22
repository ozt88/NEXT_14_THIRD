// iocpClnt.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define BUF_SIZE 1024
#define PORT "9000"

void CALLBACK CompRoutine(DWORD dwError, DWORD szRecvBytes, LPWSAOVERLAPPED lpOverlapped, DWORD flags)
{
	if(dwError != 0)
	{
		ErrorHandling("CompRoutine error!");
	}
	else
	{
		recvBytes = szRecvBytes;
		printf("Received message: %s \n Received data size: %d\n", buf, recvBytes);
	}
}
void ErrorHandling(char* msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}


int _tmain(int argc, _TCHAR* argv[])
{

	WSADATA wsaData;
	SOCKET hListenSocket, hRecvSocket;

	SOCKADDR_IN listenAddr, recvAddr;
	WSABUF dataBuf;
	WSAEVENT evObj;
	WSAOVERLAPPED overlapped;
	char buf[BUF_SIZE] = {0, };

	DWORD recvBytes = 0, flag = 0, index = 0;
	int recvAddrSize = 0;
	

	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() error!");
	}

	hListenSocket = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	memset(&listenAddr, 0, sizeof(listenAddr));
	listenAddr.sin_family = AF_INET;
	listenAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	listenAddr.sin_port = htons(atoi(PORT));

	if(bind(hListenSocket, (SOCKADDR*) &listenAddr, sizeof(listenAddr)) == SOCKET_ERROR)
	{
		ErrorHandling("bind() error!");
	}

	if(listen(hListenSocket, 5) == SOCKET_ERROR)
	{
		ErrorHandling("listen() error!");
	}

	recvAddrSize = sizeof(recvAddr);
	hRecvSocket = accept(hListenSocket, (SOCKADDR*) &recvAddr, &recvAddrSize);
	if(hRecvSocket == INVALID_SOCKET)
	{
		ErrorHandling("accept() error!");
	}

	evObj = WSACreateEvent(); //Dummy Event Object
	memset(&overlapped, 0, sizeof(overlapped));
	overlapped.hEvent = evObj;
	dataBuf.len = BUF_SIZE;
	dataBuf.buf = buf;

	//WSARecv(hSocket, &dataBuf, 1, &recvBytes, 0, &overlapped, NULL);

	if(WSARecv(hRecvSocket, &dataBuf, 1, &recvBytes, &flag, &overlapped, CompRoutine) == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSA_IO_PENDING)
		{
			puts("Background data receive");
		}


		index = WSAWaitForMultipleEvents(1, &evObj, FALSE, WSA_INFINITE, TRUE);
		if(index == WAIT_IO_COMPLETION)
		{
			puts("overlapped I/O Completed");
		}
		else
		{
			ErrorHandling("WSARecv() error!");
		}
	}

	printf("Received message: %s \n Received data size: %d \n", buf, recvBytes);
	WSACloseEvent(evObj);
	closesocket(hListenSocket);
	closesocket(hRecvSocket);
	WSACleanup();

	getchar();
	return 0;
}

