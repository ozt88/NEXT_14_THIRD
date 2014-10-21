// InsertionSort.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

bool InsertionSort( int* arr , size_t length )
{
	if( arr == NULL )
	{
		return false;
	}
	int key = 0;
	int subIdx = 0;
	for( int idx = 1; idx < length; ++idx )
	{
		key = arr[idx];
		subIdx = idx - 1;
		while( subIdx >= 0 && arr[subIdx] > key )
		{
			arr[subIdx + 1] = arr[subIdx];
			--subIdx;
		}
		arr[subIdx + 1] = key;
	}
	return true;
}

bool isSorted( int* arr , size_t length )
{
	if( length < 2 )
	{
		return true;
	}
	int compareValue = arr[0];
	for( int i = 1; i < length; ++i )
	{
		if( arr[i] < compareValue )
		{
			return false;
		}
		compareValue = arr[i];
	}
	return true;
}

void testCase( int* arr , size_t length )
{
	InsertionSort( arr , length );
	for( int i = 0; i < length; ++i )
	{
		printf( "%d " , arr[i] );
	}
	printf( "\n" );
	isSorted( arr , length ) ? printf( "case success!\n" ) : printf( "case failure!\n" );
}
int _tmain(int argc, _TCHAR* argv[])
{
	int* test0 = NULL;
	int test1[] = { 0 };
	int test2[] = { 1 , 2 };
	int test3[] = { 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 };
	int test4[] = { 10 , 9 , 8 , 7 , 6 , 5 , 4 , 3 , 2 , 1 , 0 };
	int test5[] = { 0 , 6 , 4 , 8 , 2 , 7 , 1 , 5 , 3 , 10 , 9 };

	testCase( test0 , 0 );
	testCase( test1 , 1 );
	testCase( test2 , 2 );
	testCase( test3 , 11 );
	testCase( test4 , 11 );
	testCase( test5 , 11 );
	return 0;
}

