// ConsoleApplication1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

int multipleA(int argv)
{
	return argv + (argv << 2);
}

int multipleB(int argv)
{
	return argv + ( argv << 3 );
}

int multipleC(int argv)
{
	return ( argv << 5 ) - ( argv << 2 );
}

int multipleD(int argv)
{
	return ( argv << 3 ) - ( argv << 6 );
}

int _tmain(int argc, _TCHAR* argv[])
{
	int x = 1;
	printf("%d * 5 = %d \n", x, multipleA(x));
	printf("%d * 9 = %d \n", x, multipleB(x));
	printf("%d * 30 = %d \n", x, multipleC(x));
	printf("%d * -56 = %d \n", x, multipleD(x));

	return 0;
}

