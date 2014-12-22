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
	SQLRETURN	Command(OUT SQLHSTMT* hStmt, SQLWCHAR* command);
	void		CommandOver(IN SQLHSTMT* hStmt);


private:
	bool		ErrorHandling(SQLRETURN ret, char* msg);

	SQLHENV		m_HEnv = NULL;
	SQLHDBC		m_HDbc = NULL;
	WCHAR		m_DBName[BUF_SIZE];
	WCHAR		m_DBId[BUF_SIZE];
	WCHAR		m_DBPwd[BUF_SIZE];
};

