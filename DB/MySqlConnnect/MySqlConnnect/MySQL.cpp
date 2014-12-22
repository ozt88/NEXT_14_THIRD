#include <windows.h>
#include <stdio.h>
#include <sql.h>
#include <sqlext.h>
#include <tchar.h>
#include <locale.h>

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

int main()
{
	setlocale(LC_ALL, "Korean");

	SQLHENV hEnv;
	SQLHDBC hDbc;
	SQLHSTMT hStmt;
	SQLRETURN ret;

	ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	if(!errorHandling(ret, "SQLAllocHandle():Env error!"))
		return 1;
	ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, 
						(SQLPOINTER) SQL_OV_ODBC3, SQL_IS_INTEGER);
	if(!errorHandling(ret, "SetEnvAttr error!"))
		return 1;
	ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
	if(!errorHandling(ret, "SQLAllocHandle():Dbc error!"))
		return 1;

	ret = SQLConnect(hDbc, (SQLWCHAR*) L"dbdbdip", SQL_NTS,
					 (SQLWCHAR*) L"nextuser", SQL_NTS,
					 (SQLWCHAR*) L"dbgood", SQL_NTS);
	if(!errorHandling(ret, "SQLConnect() error!"))
		return 1;

	ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
	if(!errorHandling(ret, "SQLAllockHandle(): hStmt error!"))
		return 1;	
	
	ret = SQLExecDirect(hStmt, (SQLWCHAR*) L"SELECT author, title, price FROM book", SQL_NTS);
	if(!errorHandling(ret, "SQLExecDirect() error!"))
		return 1;

	int count = 0;
	SQLLEN iAuthorLen, iTitleLen, iPriceLen, iPrice;
	char strAuthor[BUF_SIZE], strTitle[BUF_SIZE];

	while(1)
	{
		ret = SQLFetch(hStmt);
		if(!errorHandling(ret, "SQLFetch() error!"))
		   break;

		ret = SQLGetData(hStmt, 1, SQL_C_WCHAR, strAuthor, BUF_SIZE, &iAuthorLen);
		if(!errorHandling(ret, "SQLGetData():Author error!"))
			break;
		ret = SQLGetData(hStmt, 2, SQL_C_WCHAR, strTitle, BUF_SIZE, &iTitleLen);
		if(!errorHandling(ret, "SQLGetData():Title error!"))
			break;
		ret = SQLGetData(hStmt, 3, SQL_C_ULONG, &iPrice, 0, &iPriceLen);
		if(!errorHandling(ret, "SQLGetData():Price error!"))
			break;

		_tprintf(_T("Row %d: "), count++);
		_tprintf(_T("%ls %ls %d \n"), strAuthor, strTitle, iPrice);
	}

	if(hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	if(hDbc) SQLDisconnect(hDbc);
	if(hDbc) SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	if(hEnv) SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

	return 0;
}