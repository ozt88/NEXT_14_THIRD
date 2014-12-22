#pragma once

struct IngameRender
{
	int m_FsmNum = 0;
	int m_StateNum = 0;
	int	m_AnimaitionSprite = 0;
};
struct GraphicResource
{
	int m_ResourceId = 0;
	int m_IconResource = 0;
	int m_FrontResource = 0;
	int	m_PartsType = 0;
	std::vector<IngameRender> m_AnimationResource;
};

class CustomDB;
class EquipmentManager
{
public:
	EquipmentManager();
	~EquipmentManager();

	void	Init();
	bool	GetResources();
	void	MakeItem();
	void	ShowResource(int resourceId);

private:
	CustomDB*						m_DB = nullptr;
	std::vector<GraphicResource>	m_Resources;
};

