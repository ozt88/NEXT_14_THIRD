// Test1.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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

