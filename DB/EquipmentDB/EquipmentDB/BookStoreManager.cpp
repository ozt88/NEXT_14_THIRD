#include "stdafx.h"
#include "BookStoreManager.h"
#include "CustomDB.h"

BookStoreManager::BookStoreManager()
{
	m_DB = new CustomDB();

}
BookStoreManager::~BookStoreManager()
{
	delete m_DB;
}

void BookStoreManager::Init()
{
	m_DB->Init();
}

bool BookStoreManager::GetOrderingInfo()
{
	SQLHSTMT hStmt;
	SQLWCHAR* command = L"SELECT c.c_Id, COUNT(*) FROM Customer AS c JOIN _Order AS o ON c.c_Id = o.Customer_c_Id GROUP BY c.c_Id;";
	int customerId = 0;
	int orderingCount = 0;

	m_DB->Connect();
	hStmt = m_DB->Command(command);
	if(!hStmt)
	{
		return false;
	}

	while(m_DB->GetData(hStmt, &customerId, SQL_C_ULONG, &orderingCount, SQL_C_ULONG, nullptr))
	{
		printf("CustomerId : %d, OrderCount : %d\n", customerId, orderingCount);
	}

	m_DB->CommandOver(hStmt);
	m_DB->Disconnect();

	return true;
}
