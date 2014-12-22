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
	if(m_HDbc) SQLFreeHandle(SQL_HANDLE_DBC, m_HDbc);
	if(m_HEnv) SQLFreeHandle(SQL_HANDLE_ENV, m_HEnv);
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
	_getws_s(m_DBName);
	printf("Input DB ID:");
	_getws_s(m_DBId);
	printf("Input DB PASSWARD:");
	_getws_s(m_DBPwd);
}

SQLHSTMT CustomDB::Command(SQLWCHAR* command)
{
	SQLHSTMT hStmt;
	SQLRETURN ret;
	ret = SQLAllocHandle(SQL_HANDLE_STMT, m_HDbc, &hStmt);
	if(!ErrorHandling(ret, "SQLAllockHandle(): hStmt error!"))
	{
		return NULL;
	}
	ret = SQLExecDirect(hStmt, command, SQL_NTS);
	if(!ErrorHandling(ret, "SQLExecDirect() error!"))
	{
		return NULL;
	}

	return hStmt;
}

SQLRETURN CustomDB::Connect()
{
	SQLRETURN ret;
	ret = SQLConnect(m_HDbc, (SQLWCHAR*) m_DBName, SQL_NTS, (SQLWCHAR*) m_DBId, SQL_NTS, (SQLWCHAR*) m_DBPwd, SQL_NTS);
	if(!ErrorHandling(ret, "SQLConnect() error!"))
	{
		return ret;
	}
	m_IsConnected = true;
	return ret;
}

void CustomDB::Disconnect()
{
	m_IsConnected = false;
	if(m_HDbc)
	{
		SQLDisconnect(m_HDbc);
	}
}

bool CustomDB::GetData(HSTMT hStmt, ...)
{
	if(!m_IsConnected)
	{
		return false;
	}

	SQLRETURN ret;
	ret = SQLFetch(hStmt);
	if(ret == SQL_ERROR)
	{
		return false;
	}

	va_list ap;

	va_start(ap, hStmt);
	SQLSMALLINT targetType;
	void* targetValue;
	int idx = 1;
	while(true)
	{
		SQLLEN length = 0;
		targetValue = va_arg(ap, void*);
		targetType = va_arg(ap, SQLSMALLINT);
		if(targetValue == nullptr)
		{
			break;
		}
		ret = SQLGetData(hStmt, idx++, targetType, targetValue, BUF_SIZE, &length);
		if(ret == SQL_ERROR)
		{
			return false;
		}
	}
	va_end(ap);

	return true;
}

void CustomDB::CommandOver(HSTMT hStmt)
{
	if(hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

