// 2.67.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
//for 32bit
int bad_int_size_is_32()
{
	unsigned int set_msb = 1 << 15 << 16;
	unsigned int beyond_msb = 1 << 16 << 16;

	bool ret =  set_msb && !beyond_msb;
	return ret;
}

//for 16bit
int _bad_int_size_is_32()
{
	unsigned int set_msb = 1 << 7 << 8 << 8 << 8;
	unsigned int beyond_msb = 1 << 8 << 8 << 8 << 8;

	bool ret = set_msb && !beyond_msb;
	return ret;
}

int _tmain(int argc, _TCHAR* argv[])
{
	bad_int_size_is_32();
	_bad_int_size_is_32();
	return 0;
}

