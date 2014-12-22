#include "stdafx.h"
#include "EquipmentManager.h"
#include "CustomDB.h"

EquipmentManager::EquipmentManager()
{
	m_DB = new CustomDB();
}


EquipmentManager::~EquipmentManager()
{
	delete m_DB;
}

void EquipmentManager::Init()
{
	m_DB->Init();
}

bool EquipmentManager::GetResources()
{
	SQLHSTMT hStmt;
	SQLWCHAR* command = L"SELECT g_Id, g_FrontSprite, g_IconSprite, g_PartsType FROM GraphicResource;";
	GraphicResource resource;

	m_DB->Connect();
	hStmt = m_DB->Command(command);
	if(!hStmt)
	{
		return false;
	}
	while(m_DB->GetData(hStmt, &resource.m_ResourceId, SQL_C_ULONG,
		&resource.m_IconResource, SQL_C_ULONG,
		&resource.m_FrontResource, SQL_C_ULONG,
		&resource.m_PartsType, SQL_C_ULONG, nullptr))
	{
		m_Resources.push_back(resource);
	}

	m_DB->CommandOver(hStmt);
	command = L"SELECT r_ResourceId, r_FsmNum, r_StateNum, r_AnimationSprite FROM IngameRender;";
	hStmt = m_DB->Command(command);
	if(!hStmt)
	{
		return false;
	}

	int graphicId = 0;
	IngameRender render;
	int fsmNum = 0;
	int stateNum = 0;
	int animationResource = 0;

	while(m_DB->GetData(hStmt, &graphicId, SQL_C_ULONG, 
		&render.m_FsmNum, SQL_C_ULONG, &render.m_StateNum, SQL_C_ULONG,
		&render.m_AnimaitionSprite, SQL_C_ULONG, nullptr))
	{
		if(graphicId < m_Resources.size())
		{
			m_Resources[graphicId].m_AnimationResource.push_back(render);
		}
	}

	m_DB->CommandOver(hStmt);
	m_DB->Disconnect();

	return true;
}
