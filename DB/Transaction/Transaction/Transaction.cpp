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


SQLRETURN bookPrint(SQLHDBC& hDbc, SQLHSTMT& hStmt, WCHAR* title)
{
	SQLRETURN ret;
	//START
	SQLSetConnectAttr(hDbc, SQL_ATTR_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF, SQL_IS_INTEGER);
	ret = SQLConnect(hDbc, (SQLWCHAR*) L"ozt88", SQL_NTS,
					 (SQLWCHAR*) L"root", SQL_NTS,
					 (SQLWCHAR*) L"rladusdn1", SQL_NTS);

	if(!errorHandling(ret, "SQLConnect() error!"))
		return 1;

	ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
	if(!errorHandling(ret, "SQLAllockHandle(): hStmt error!"))
		return 1;

	SQLWCHAR cmd[256] = {0,};
	wsprintf(cmd, L"SELECT author, title, price, inventory FROM book WHERE title = '%s'", title);
	ret = SQLExecDirect(hStmt, cmd, SQL_NTS);
	if(!errorHandling(ret, "SQLExecDirect() error!"))
		return 1;

	if(ret == SQL_SUCCESS)
	{
		SQLEndTran(SQL_HANDLE_DBC, hDbc, SQL_COMMIT);
		_tprintf(_T("insert success\n"));
	}
	else
	{
		SQLEndTran(SQL_HANDLE_DBC, hDbc, SQL_ROLLBACK);
		_tprintf(_T("rollback!! \n"));
	}
	//END

	int count = 0;
	SQLLEN iAuthorLen, iTitleLen, iPriceLen, iPrice, iInvenLen , iInven;
	char strAuthor[BUF_SIZE], strTitle[BUF_SIZE];


	ret = SQLFetch(hStmt);
	if(!errorHandling(ret, "SQLFetch() error!"))
		return ret;
	ret = SQLGetData(hStmt, 1, SQL_C_WCHAR, strAuthor, BUF_SIZE, &iAuthorLen);
	if(!errorHandling(ret, "SQLGetData():Author error!"))
		return ret;
	ret = SQLGetData(hStmt, 2, SQL_C_WCHAR, strTitle, BUF_SIZE, &iTitleLen);
	if(!errorHandling(ret, "SQLGetData():Title error!"))
		return ret;
	ret = SQLGetData(hStmt, 3, SQL_C_ULONG, &iPrice, 0, &iPriceLen);
	if(!errorHandling(ret, "SQLGetData():Price error!"))
		return ret;
	ret = SQLGetData(hStmt, 4, SQL_C_ULONG, &iInven, 0, &iInvenLen);
	if(!errorHandling(ret, "SQLGetData():Inven error!"))
		return ret;
	_tprintf(_T("Row %d: "), count++);
	_tprintf(_T("%ls %ls %d \n"), strAuthor, strTitle, iPrice);

	return ret;
}

SQLRETURN bookSales(CustomDB* db)
{
	WCHAR title[256] = {0, };
	SQLWCHAR cmd[256] = {0, };
	SQLHSTMT hStmt;
	SQLRETURN ret;
	printf("어떤 책을 사시겠습니까?\n");
	fflush(stdin);
	_getws(title);
	wsprintf(cmd, L"SELECT author, title, price, inventory FROM book WHERE title = '%s'", title);

	ret = db->Command(&hStmt, cmd);
	if(!errorHandling(ret, "Command() Error!"))
		return ret;

	int count = 0;
	SQLLEN iAuthorLen, iTitleLen, iPriceLen, iPrice, iInvenLen, iInven;
	WCHAR strAuthor[BUF_SIZE], strTitle[BUF_SIZE];


	ret = SQLFetch(hStmt);
	if(!errorHandling(ret, "책이 없습니다."))
		return ret;
	ret = SQLGetData(hStmt, 1, SQL_C_WCHAR, strAuthor, BUF_SIZE, &iAuthorLen);
	if(!errorHandling(ret, "SQLGetData():Author error!"))
		return ret;
	ret = SQLGetData(hStmt, 2, SQL_C_WCHAR, strTitle, BUF_SIZE, &iTitleLen);
	if(!errorHandling(ret, "SQLGetData():Title error!"))
		return ret;
	ret = SQLGetData(hStmt, 3, SQL_C_ULONG, &iPrice, 0, &iPriceLen);
	if(!errorHandling(ret, "SQLGetData():Price error!"))
		return ret;
	ret = SQLGetData(hStmt, 4, SQL_C_ULONG, &iInven, 0, &iInvenLen);
	if(!errorHandling(ret, "SQLGetData():Inven error!"))
		return ret;

	db->CommandOver(&hStmt);

	_tprintf(_T("Book : %ls %ls %d원 %d개 \n"), strAuthor, strTitle, iPrice, iInven);
	if(iInven <= 0)
	{
		printf("재고가 없습니다.\n");
		return ret;
	}

	fflush(stdin);
	printf("책을 사시겠습니까?[Y/N]:");
	char ack = fgetc(stdin);

	if(ack == 'Y')
	{
		wsprintf(cmd, L"UPDATE book SET inventory = inventory-1 WHERE title = '%s'", title);
		ret = db->Command(&hStmt, cmd);
		if(!errorHandling(ret, "Command() Error!"))
			return ret;
		db->CommandOver(&hStmt);
		bookSales(db);
	}
	else if(ack == 'N')
	{
		printf("안녕히 가세요.\n");
		return ret;
	}

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