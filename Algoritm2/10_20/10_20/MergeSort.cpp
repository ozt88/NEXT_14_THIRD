// 10_20.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#define MAX_BUFFER_SIZE 1024

void copy( int* srcStart , int* srcEndPoint , int* dstStart)
{
	while( srcStart != srcEndPoint )
	{
		*(dstStart++) = *(srcStart++);
	}
}
void Merge( int* arr , int* buffer , int firstStartIdx , int secondStartIdx , int secondLastIdx )
{
	if( arr == NULL )
	{
		return;
	}
	copy( arr + firstStartIdx , arr + secondLastIdx + 1, buffer + firstStartIdx );

	int firstIdx = firstStartIdx;
	int secondIdx = secondStartIdx;

	for( int idx = firstStartIdx; idx < secondLastIdx + 1; ++idx )
	{
		if( firstIdx >= secondStartIdx )
			arr[idx] = buffer[secondIdx++];
		else if( secondIdx > secondLastIdx )
			arr[idx] = buffer[firstIdx++];
		else if( buffer[firstIdx] > buffer[secondIdx] )
			arr[idx] = buffer[secondIdx++];
		else
			arr[idx] = buffer[firstIdx++];
	}
}

void MergeSort( int* arr ,int* buffer , int beginIdx , int lastIdx )
{
	if( arr == NULL || beginIdx >= lastIdx )
	{
		return;
	}
	int centerIdx = beginIdx + ( lastIdx - beginIdx ) / 2;
	MergeSort( arr , buffer, beginIdx , centerIdx );
	MergeSort( arr , buffer, centerIdx + 1 , lastIdx );
	Merge( arr , buffer , beginIdx , centerIdx + 1 , lastIdx );
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
	int buffer[MAX_BUFFER_SIZE];
	MergeSort( arr , buffer, 0, length-1 );
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

