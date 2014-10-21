// 10_16.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

//리커시브가 가능한 갯수 찾기 함수 (덧셈연산 활용)
int findSameNumIter( int* arr , int leftIdx, int rightIdx ,int key )
{
	if( leftIdx > rightIdx )
	{
		return 0;
	}
	int centerIdx = leftIdx + ( rightIdx - leftIdx ) / 2;
	int curValue = arr[centerIdx];
	int resultNum = 0;

	if( arr[leftIdx] == key && arr[rightIdx] == key )
	{
		return rightIdx - leftIdx + 1;
	}
	if( key > curValue )
	{
		return findSameNumIter( arr , centerIdx + 1 , rightIdx , key );
	}
	else if( key < curValue )
	{
		return findSameNumIter( arr , leftIdx , centerIdx - 1 , key );
	}
	else
	{
		return	findSameNumIter( arr , centerIdx + 1 , rightIdx , key ) +
				findSameNumIter( arr , leftIdx , centerIdx - 1 , key ) + 1;
	}
}

//정렬된 배열에서 key와 같은 값을 가진 원소의 갯수를 리턴 (덧셈 활용)
int findSameNumBySum( int* arr , size_t length , int key )
{
	if( arr == NULL )
	{
		return 0;
	}
	return findSameNumIter(arr, 0, length-1, key);
}


//왼쪽 끝과 오른쪽 끝을 구해서 끝의 idx값의 차로 총 갯수를 리턴
int findSameNumByEndPoint( int* arr , size_t length , int key )
{
	if( arr == NULL )
	{
		return 0;
	}
	int leftEndIdx = 0, rightEndIdx = 0;
	int leftIdx = 0, rightIdx = length-1;
	int centerIdx = 0;
	
	while( leftIdx <= rightIdx )
	{
		centerIdx = leftIdx + ( rightIdx - leftIdx ) / 2;
		if( arr[centerIdx] < key )
		{
			leftIdx = centerIdx + 1;
		}
		else
		{
			rightIdx = centerIdx - 1;
		}
	}
	leftEndIdx = leftIdx;

	leftIdx = 0;
	rightIdx = length - 1;
	while( leftIdx <= rightIdx )
	{
		centerIdx = leftIdx + ( rightIdx - leftIdx ) / 2;
		if( arr[centerIdx] > key )
		{
			rightIdx = centerIdx - 1;
		}
		else
		{
			leftIdx = centerIdx + 1;
		}
	}
	rightEndIdx = rightIdx;

	return rightEndIdx - leftEndIdx + 1;
}


int _tmain( int argc , _TCHAR* argv[] )
{
	int arr[] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 };
	printf( "Sumation: %d\n" , findSameNumBySum( arr , 11 , 0 ) );
	printf( "EndPoint: %d\n" , findSameNumByEndPoint( arr , 11 , 0 ) );

	return 0;
}

