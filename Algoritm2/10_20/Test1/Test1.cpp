// Test1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

class CClass
{
public:
	CClass()
	{
	}
	int m_Num;
	int m_Num2;
	int* m_Arr;
};

int _tmain(int argc, _TCHAR* argv[])
{
	CClass classArr = CClass();
	printf( "%d %d %d\n" , classArr.m_Num , classArr.m_Num2, classArr.m_Arr);
	return 0;
}

