// CountReversePosition.cpp : 역위의 갯수를 파악하는 함수

#include "stdafx.h"

void copy( int* srcStart , int* srcEndPoint , int* dstStart )
{
	while( srcStart != srcEndPoint )
	{
		*( dstStart++ ) = *( srcStart++ );
	}
}

//기본적인 MergeSort에서 Merge부분만 변경하면 역위의 갯수를 판단할 수 있다.
int MergeWithCount( int* arr , int* buffer , int firstStartIdx , int secondStartIdx , int secondLastIdx )
{
	if( arr == NULL )
	{
		return 0;
	}
	copy( arr + firstStartIdx , arr + secondLastIdx + 1 , buffer + firstStartIdx );
	int reverseCount = 0;
	int firstIdx = firstStartIdx;
	int secondIdx = secondStartIdx;
	int swapIdx = 0;
	for( int idx = firstStartIdx; idx < secondLastIdx + 1; ++idx )
	{
		if( firstIdx >= secondStartIdx )
		{
			swapIdx = secondIdx++;
		}
		else if( secondIdx > secondLastIdx )
		{
			swapIdx = firstIdx++;
		}
		else if( buffer[firstIdx] > buffer[secondIdx] )
		{
			//두 배열을 병합할때 firstIdx의 값이 secondIdx보다 작을때 
			//각각은 정렬되어 있으므로 firstIdx부터 첫번째 배열의 끝(secondStartIdx -1)까지 모든 숫자들이 
			//secondIdx번째의 숫자와 역위가 된다. 이것을 전체 카운터에 더해주면 된다.
			reverseCount += secondStartIdx - firstIdx;
			swapIdx = secondIdx++;
		}
		else
		{
			swapIdx = firstIdx++;
		}
		arr[idx] = buffer[swapIdx];
	}

	return reverseCount;
}

//그리고 각 recursion에서 반환된 값을 더해서 리턴해주면 전체 역위의 갯수를 판별할 수 있다.
int CountReversePositionWithMergeSort( int* arr , int* buffer , int beginIdx , int lastIdx )
{
	if( arr == NULL || beginIdx >= lastIdx )
	{
		return 0;
	}
	int reverseCount = 0;
	int centerIdx = beginIdx + ( lastIdx - beginIdx ) / 2;
	reverseCount += CountReversePositionWithMergeSort( arr , buffer , beginIdx , centerIdx );
	reverseCount += CountReversePositionWithMergeSort( arr , buffer , centerIdx + 1 , lastIdx );
	reverseCount += MergeWithCount( arr , buffer , beginIdx , centerIdx + 1 , lastIdx );

	return reverseCount;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int test4[] = { 3, 2, 1, 0};
	int buffer[11];
	printf( "%d" , CountReversePositionWithMergeSort( test4 , buffer , 0 , 3 ) );
	return 0;
}

