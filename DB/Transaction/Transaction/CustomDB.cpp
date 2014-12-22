#include "stdafx.h"
#include "customDB.h"


CustomDB::CustomDB()
{
	memset(m_DBId, 0, sizeof(WCHAR)*BUF_SIZE);
	memset(m_DBName, 0, sizeof(WCHAR)*BUF_SIZE);
	memset(m_DBPwd, 0, sizeof(WCHAR)*BUF_SIZE);

	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_HEnv);
	SQLSetEnvAttr(m_HEnv, SQL_ATTR_ODBC_VERSION,
				  (SQLPOINTER) SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, m_HEnv, &m_HDbc);
}


CustomDB::~CustomDB()
{
	if(m_HDbc) SQLFreeHandle(SQL_HANDLE_DBC, m_HDbc );
	if(m_HEnv) SQLFreeHandle(SQL_HANDLE_ENV, m_HEnv );
}

bool CustomDB::ErrorHandling(SQLRETURN ret, char* msg)
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

void CustomDB::Init()
{
	fflush(stdin);
	printf("Input DB Name:");
	_getws(m_DBName);
	printf("Input DB Name:");
	_getws(m_DBId);
	printf("Input DB Name:");
	_getws(m_DBPwd);
}

SQLRETURN CustomDB::Command(OUT SQLHSTMT* hStmt, SQLWCHAR* command)
{
	SQLRETURN ret;
	ret = SQLAllocHandle(SQL_HANDLE_STMT, m_HDbc, hStmt);
	if(!ErrorHandling(ret, "SQLAllockHandle(): hStmt error!"))
	{
		return ret;
	}
	ret = SQLExecDirect(*hStmt, command, SQL_NTS);
	if(!ErrorHandling(ret, "SQLExecDirect() error!"))
	{
		return ret;
	}

	return ret;
}

void CustomDB::CommandOver(IN SQLHSTMT* hStmt)
{
	SQLFreeHandle(SQL_HANDLE_STMT, *hStmt);
	*hStmt = nullptr;
}

SQLRETURN CustomDB::Connect()
{
	SQLRETURN ret;
	ret = SQLConnect(m_HDbc, (SQLWCHAR*) m_DBName, SQL_NTS, (SQLWCHAR*) m_DBId, SQL_NTS, (SQLWCHAR*) m_DBPwd, SQL_NTS);
	ErrorHandling(ret, "SQLConnect() error!");
	return ret;
}

void CustomDB::Disconnect()
{
	if(m_HDbc)
	{
		SQLDisconnect(m_HDbc);
	}
}

