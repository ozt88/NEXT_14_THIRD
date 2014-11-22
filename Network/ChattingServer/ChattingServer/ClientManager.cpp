#include "stdafx.h"
#include "ClientManager.h"
#include "ClientSession.h"

ClientManager* ClientManager::m_Instance = nullptr;
ClientManager* ClientManager::GetInstance()
{
	if(m_Instance == nullptr)
	{
		m_Instance = new ClientManager();
	}
	return m_Instance;
}

void ClientManager::ReleaseInstance()
{
	if(m_Instance != nullptr)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}

bool ClientManager::AddClient(ClientSession* client)
{
	if(!client)
	{
		return false;
	}
	auto findIter = std::find(m_Clients.begin(), m_Clients.end(), client);
	if(findIter != m_Clients.end())
	{
		//이미 있으면 실패
		return false;
	}
	m_Clients.push_back(client);
	return true;
}

bool ClientManager::RemoveClient(ClientSession* client)
{
	if(!client)
	{
		return false;
	}
	auto findIter = std::find(m_Clients.begin(), m_Clients.end(), client);
	if(findIter == m_Clients.end())
	{
		//없으면 실패
		return false;
	}
	m_Clients.erase(findIter);
	client->Disconnect();
	SafeDelete<ClientSession*>(client);
}

bool ClientManager::SendToAllClient(char* message, DWORD bytesTrans)
{
	bool ret = true;
	for(auto clientIter = m_Clients.begin(); clientIter != m_Clients.end(); clientIter++)
	{
		
		auto client = *clientIter;
		printf("send to %d\n", client);

		ret = client->SendToClient(message, bytesTrans);
		if(!ret)
		{
			ret = false;
			break;
		}
	}
	return ret;
}

ClientManager::ClientManager()
{
	m_Clients.reserve(MAX_THREAD_NUM);
}

ClientManager::~ClientManager()
{
	for(auto clientIter = m_Clients.begin(); clientIter != m_Clients.end(); clientIter++)
	{
		auto client = *clientIter;
		RemoveClient(client);
	}
	m_Clients.clear();
}

