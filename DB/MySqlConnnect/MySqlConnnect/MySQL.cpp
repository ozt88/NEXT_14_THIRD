#include <stdio.h>
#include <mysql.h>

int main()
{
	MYSQL* mySql = new MYSQL();
	mysql_init( mySql );


	return 0;
}