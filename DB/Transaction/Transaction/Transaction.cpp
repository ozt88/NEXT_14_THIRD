#include "stdafx.h"
#include "customDB.h"

#define BUF_SIZE 256


bool errorHandling(SQLRETURN ret, char* msg)
{
	char error[BUF_SIZE] = {0, };
	if(ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
	{
		return true;
	}
	else
	{
		sprintf_s(error, "%s error No: %d\n", msg, GetLastError());
		fputs(error, stderr);
		return false;
	}
}


SQLRETURN bookSales(CustomDB* db)
{
	WCHAR customerName[256] = {0, };
	SQLWCHAR cmd[256] = {0, };
	SQLHSTMT hStmt;
	SQLRETURN ret;
	
	wsprintf(cmd, L"SELECT c.c_Id, COUNT(*) FROM Customer AS c JOIN _Order AS o ON c.c_Id = o.Customer_c_Id GROUP BY c.c_Id;");

	ret = db->Command(&hStmt, cmd);
	if(!errorHandling(ret, "Command() Error!"))
		return ret;

	int count = 0;
	SQLLEN customerId, orderingCount, idLen, countLen;

	ret = SQLFetch(hStmt);

	ret = SQLGetData(hStmt, 1, SQL_C_ULONG, &customerId, 0, &idLen);
	if(!errorHandling(ret, "SQLGetData():customerId error!"))
		return ret;	
	ret = SQLGetData(hStmt, 2, SQL_C_ULONG, &orderingCount, 0, &countLen);
	if(!errorHandling(ret, "SQLGetData():orderingCount error!"))
		return ret;
	printf("id :%d, count: %d\n", customerId, orderingCount);


	db->CommandOver(&hStmt);

	return ret;
}



int main()
{
	setlocale(LC_ALL, "Korean");
	CustomDB db;
	db.Init();
	db.Connect();
	bookSales(&db);
	db.Disconnect();

	return 0;
}