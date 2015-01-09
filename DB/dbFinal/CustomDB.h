#pragma once
#define BUF_SIZE 256

class CustomDB
{
public:
	CustomDB();
	~CustomDB();
	void		Init();
	SQLRETURN	Connect();
	void		Disconnect();
	SQLHSTMT	Command(SQLWCHAR* command);
	void		CommandOver(HSTMT hStmt);
	bool		GetData(HSTMT hStmt, ...);

private:
	bool		ErrorHandling(SQLRETURN ret, char* msg);

	bool		m_IsConnected = false;
	SQLHENV		m_HEnv = NULL;
	SQLHDBC		m_HDbc = NULL;
	WCHAR		m_DBName[BUF_SIZE];
	WCHAR		m_DBId[BUF_SIZE];
	WCHAR		m_DBPwd[BUF_SIZE];
};

