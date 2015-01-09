// EquipmentDB.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "CustomDB.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CustomDB db;
	SQLHSTMT hStmt;
	SQLWCHAR* command = L"SELECT c.c_Id, COUNT(*) FROM Customer AS c JOIN _Order AS o ON c.c_Id = o.Customer_c_Id GROUP BY c.c_Id;";
	int customerId = 0;
	int orderingCount = 0;

	db.Init();
	db.Connect();
	hStmt = db.Command(command);
	if(!hStmt)
	{
		return false;
	}

	while(db.GetData(hStmt, &customerId, SQL_C_ULONG, &orderingCount, SQL_C_ULONG, nullptr))
	{
		printf("CustomerId : %d, OrderCount : %d\n", customerId, orderingCount);
	}

	db.CommandOver(hStmt);
	db.Disconnect();

	getchar();
	return 0;
}

