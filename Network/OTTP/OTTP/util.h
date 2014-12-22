//
// util.h
// Network for FSM sample code
//
// Created by Nam SeHyun, 2014.12.1.
// Copyright (c) 2014. Nam SeHyun All rights reserved.
// No License.




#ifndef ProtocolClient_util_h
#define ProtocolClient_util_h
#define MAX_PACKET_SIZE 1024
#define LOGIN_UNIQUE_KEY 0x10204080
#define PORT 9999
#define SERVER_IP "125.209.193.18"
#define LOGIN_MAX_TRY_COUNT 10

typedef unsigned int ChannelNumber;
typedef unsigned int ID;

// success = 0, fail = -1
int Login(ChannelNumber channel, ID id, int lossRate);
int Send(char* buf, size_t length);

// 0 : no recv
// <0 : error
// n(>0) : recv length n
size_t Recv(char* buf, int maxLength);

typedef struct t_LoginPacket
{
	int m_UniqueKey;
	ChannelNumber m_ChannelNumber;
	ID m_ID;
	int m_LossRate;
} LoginPacket;

typedef struct t_NormalPacket
{
	ChannelNumber m_ChannelNumber;
	ID m_ID;
	char m_Data[MAX_PACKET_SIZE - sizeof(ChannelNumber) - sizeof(ID)];
} NormalPacket;

#endif
