// 2.61.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

bool checkBitAll1(int value)
{
	return ~!value;
}

bool checkBitAll0(int value)
{
	return !value;
}

bool checkMSBAll1(int value)
{
	int shift_val = (sizeof(int) - 1) << 3;
	int msb = value >> shift_val;
	return !(msb & 0xFF);
}

bool checkMIBAll0(int value)
{
	return !( value & 0xFF );
}

int _tmain(int argc, _TCHAR* argv[])
{

	return 0;
}

