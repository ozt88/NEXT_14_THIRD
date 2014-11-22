// 11_03.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len)
{
	for(int i = 0; i < len; ++i)
	{
		printf("address: %p \t value: 0x%x\n", start + i, start[i]);
	}
	printf("\n");
}


void testShowByte()
{
	printf("//Show Byte Test\n");
	int value = 0xABCD1234;
	show_bytes((byte_pointer) &value, sizeof(int));
}


void testByteOrdering()
{
	printf("//Byte Ordering Test\n");
	int value = 0x87654321;
	byte_pointer ptr = (byte_pointer) &value;
	show_bytes(ptr, 1);
	show_bytes(ptr, 2);
	show_bytes(ptr, 3); 

}

int _tmain(int argc, _TCHAR* argv[])
{
	testShowByte();
	testByteOrdering();
	return 0;
}

