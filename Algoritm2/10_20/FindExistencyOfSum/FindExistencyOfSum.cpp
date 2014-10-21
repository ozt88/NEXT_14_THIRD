// FindExistencyOfSum.cpp : 배열 S에서 합이 x가 되는 두 원소가 있는지를 bool로 리턴
//

#include "stdafx.h"

#define MAX_BUFFER_SIZE 1024

void copy( int* srcStart , int* srcEndPoint , int* dstStart )
{
	while( srcStart != srcEndPoint )
	{
		*( dstStart++ ) = *( srcStart++ );
	}
}
void Merge( int* arr , int* buffer , int firstStartIdx , int secondStartIdx , int secondLastIdx )
{
	if( arr == NULL )
	{
		return;
	}
	copy( arr + firstStartIdx , arr + secondLastIdx + 1 , buffer + firstStartIdx );

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

void MergeSortIter( int* arr , int* buffer , int beginIdx , int lastIdx )
{
	if( beginIdx < lastIdx )
	{
		int centerIdx = beginIdx + ( lastIdx - beginIdx ) / 2;
		MergeSortIter( arr , buffer , beginIdx , centerIdx );
		MergeSortIter( arr , buffer , centerIdx + 1 , lastIdx );
		Merge( arr , buffer , beginIdx , centerIdx + 1 , lastIdx );
	}
}

void MergeSort( int* arr , int beginIdx , int lastIdx )
{
	if( arr == NULL )
	{
		return;
	}
	int buffer[MAX_BUFFER_SIZE] = { 0 , };
	MergeSortIter( arr , buffer , beginIdx , lastIdx );
}

bool BinarySearch( int* arr , size_t length, int key )
{
	int leftIdx = 0;
	int rightIdx = length - 1;
	int centerIdx = 0;
	while( leftIdx < rightIdx )
	{
		centerIdx = leftIdx + ( rightIdx - leftIdx ) / 2;
		if( arr[centerIdx] == key )
		{
			return true;
		}
		if( arr[centerIdx] > key )
		{
			rightIdx = centerIdx - 1;
		}
		else
		{
			leftIdx = centerIdx + 1;
		}
	}
	return false;
}

bool FindExistencyOfSum( int* arr , size_t length , int key )
{
	//먼저 배열을 정렬한다.(n*log(n))
	MergeSort( arr , 0 , length - 1 );
	for( int idx = 0; idx < length; ++idx )
	{
		//각 원소마다 순회하면서 key와 원소값의 차가 배열 안에 있는지를 바이너리 서치로 검색한다.(n*log(n))
		if( BinarySearch( arr , length , key - arr[idx] ) )
		{
			return true;
		}
	}
	return false;
	//총 연산시간 c*n*log(n)
}


int _tmain(int argc, _TCHAR* argv[])
{
	int test4[] = { 10 , 9 , 8 , 7 , 6 , 5 , 4 , 3 , 2 , 1 , 0 };
	FindExistencyOfSum( test4 , 11 , 10 ) ? printf( "true\n" ) : printf( "false\n" );
	return 0;
}

