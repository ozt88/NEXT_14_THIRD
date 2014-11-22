#pragma once
#define BUF_SIZE 1024

enum PacketType
{
	PACKET_NONE,
	PACKET_ENTER,
	PACKET_CHAT,
	PACKET_EXIT,
	PACKET_MAX,
};

void ErrorHandling(char* message, DWORD error);
bool GetMessageHeader(char* buffer, OUT DWORD* messageLength, OUT PacketType* packetType, OUT char** message);
bool MakeMessageHeader(char* buffer, char bufferLength, char packetType, OUT char* message);