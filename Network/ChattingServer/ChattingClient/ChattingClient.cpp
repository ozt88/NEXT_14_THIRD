// ChattingClient.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//
#include "stdafx.h"
#include "Util.h"

unsigned int WINAPI SendThreadProc(LPVOID argv);
unsigned int WINAPI RecvThreadProc(LPVOID argv);
int		SendMessage(SOCKET socket, char* message, int length);
int		RecvMessage(SOCKET socket, char* buffer, int length);
void	ErrorHandling(char* message, DWORD error);
void	AddMessage(char* message);
void	PrintRecvMessages();

std::deque<char*> messages;

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	HANDLE hSendThread, hRecvThread;
	DWORD dwSendThreadId, dwRecvThreadId;
	SOCKET hServSock;
	SOCKADDR_IN servAddr;
	int port = 0;
	const char* ip;

	if(argc != 2)
	{
#ifndef _DEBUG
		printf("Usage: %s <IP> <PORT>\n", argv[0]);
		exit(1);
#else
		port = 8000;
		ip = "127.0.0.1";
#endif
	}
	else
	{
		ip = (const char*)argv[1];
		port = atoi((const char*) argv[2]);
	}

	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() error!", GetLastError());
		exit(1);
	}

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if(hServSock == INVALID_SOCKET)
	{
		ErrorHandling("socket() error!", GetLastError());
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(ip);
	servAddr.sin_port = htons(port);

	if(connect(hServSock, (SOCKADDR*) &servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		ErrorHandling("connect() error!", GetLastError());
		exit(1);
	}
	else
	{
		puts("Connected........");
	}


	hSendThread = (HANDLE) _beginthreadex(NULL, 0, SendThreadProc, (LPVOID)hServSock, 0, (unsigned*) &dwSendThreadId);
	if(hSendThread == INVALID_HANDLE_VALUE)
	{
		ErrorHandling("_beginthreadex() : SendThread error!", GetLastError());
		exit(1);
	}

	hRecvThread = (HANDLE) _beginthreadex(NULL, 0, RecvThreadProc, (LPVOID) hServSock, 0, (unsigned*) &dwRecvThreadId);
	if(hRecvThread == INVALID_HANDLE_VALUE)
	{
		ErrorHandling("_beginthreadex() : RecvThread error!", GetLastError());
		exit(1);
	}

	

	WaitForSingleObject(hSendThread, INFINITE);
	WaitForSingleObject(hRecvThread, INFINITE);
	_endthreadex(dwSendThreadId);
	_endthreadex(dwRecvThreadId);
	closesocket(hServSock);
	WSACleanup();
	return 0;
}

int SendMessage(SOCKET socket, char* message, int length)
{
	int ret = 0;
	int sentBytes = 0;
	while(sentBytes < length)
	{
		ret = send(socket, message + sentBytes, length - sentBytes, NULL);
		if(ret == SOCKET_ERROR)
		{
			ErrorHandling("send() error!", GetLastError());
			return ret;
		}
		sentBytes += ret;
	}
	return sentBytes;
}

int RecvMessage(SOCKET socket, char* buffer, int length)
{
	int ret = 0;
	int recvBytes = 0;
	while(true)
	{
		ret = recv(socket, buffer + recvBytes, length - recvBytes, NULL);
		if(ret == SOCKET_ERROR)
		{
			ErrorHandling("recv() error!", GetLastError());
			return ret;
		}
		else if(ret == 0)
		{
			break;
		}
		recvBytes += ret;
	}
	return recvBytes;
}

unsigned int WINAPI SendThreadProc(LPVOID argv)
{
	SOCKET hServSock = (SOCKET) argv;
	char buffer[BUF_SIZE] = {0, };
	char message[BUF_SIZE] = {0, };
	unsigned short messageSize = 0;

	while(true)
	{
		memset(message, 0, sizeof(char) * BUF_SIZE);
		fputs("Input message(Q to quit): ", stdout);
		fgets(buffer, BUF_SIZE, stdin);
		messageSize = strlen(buffer) + 2;
		MakeMessageHeader(buffer, messageSize, PACKET_CHAT, message);
		if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
		{
			break;
		}
		if(SendMessage(hServSock, message, messageSize) == SOCKET_ERROR)
		{
			ErrorHandling("sendMessage() error!", GetLastError());
			break;
		}
	}

	return 0;
}

unsigned int WINAPI RecvThreadProc(LPVOID argv)
{
	SOCKET hServSock = (SOCKET) argv;
	char message[BUF_SIZE] = {0, };
	unsigned short messageSize = 0;

	while(true)
	{
		memset(message, 0, sizeof(char)*BUF_SIZE);
		if(RecvMessage(hServSock, (char*)&messageSize, 1) == SOCKET_ERROR)
		{
			ErrorHandling("RecvMessage(): messageSize error!", GetLastError());
			continue;
		}
		if(RecvMessage(hServSock, message, messageSize - 1) == SOCKET_ERROR)
		{
			ErrorHandling("RecvMessage(): message error!", GetLastError());
			continue;
		}
		messages.push_back(message + 1);
		printf(message+1);
	}
	return 0;
}

void PrintRecvMessages()
{
	system("cls");
	for(auto message : messages)
	{
		printf("%s\n", message);
	}
}

void AddMessage(char* message)
{
	messages.push_back(message);

}

