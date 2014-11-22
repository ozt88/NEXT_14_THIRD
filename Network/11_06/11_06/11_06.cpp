#include "stdafx.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment ( lib, "Ws2_32.lib" )
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <windows.h>


int main(int ac, char* av[])
{
	int socket_handle;
	struct sockaddr_in socket_details;//주소 버퍼
	char* input_buffer;//데이터 버퍼
	char httpget[] = "GET / HTTP/1.0\r\n\r\n"; 

	struct addrinfo* result = new addrinfo();
	getaddrinfo("www.naver.com", NULL, NULL, &result);
	struct in_addr ip = ( ( struct sockaddr_in * )( result->ai_addr ) )->sin_addr;

	input_buffer = (char*)malloc(20000);

	socket_handle /* int */
		= socket(AF_INET, SOCK_STREAM, 0);
	/* sockaddr_in */
	socket_details.sin_family = AF_INET;
	socket_details.sin_addr.s_addr
		= inet_addr(inet_ntoa(ip));
	socket_details.sin_port = htons(80);

	connect(socket_handle,
			( struct sockaddr* )&socket_details,
			sizeof(struct sockaddr));

	send(socket_handle, /* int */
		 httpget, /* "GET / ... " */
		 strlen(httpget),
		 0); /* default value */

	recv(socket_handle,
		 input_buffer, /* malloc(20000) */
		 20000,
		 0); /* default value */

	printf("input: %s\n", input_buffer);

	if(input_buffer)
	{
		free(input_buffer);
		input_buffer == NULL;
	}
	return 0;
}
