#pragma once

class CustomDB;
class BookStoreManager
{
public:
	BookStoreManager();
	~BookStoreManager();
	void	Init();
	bool	GetOrderingInfo();

private:
	CustomDB*	m_DB = nullptr;
};
