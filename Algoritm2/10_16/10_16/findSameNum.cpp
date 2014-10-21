// 10_16.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

//��Ŀ�ú갡 ������ ���� ã�� �Լ� (�������� Ȱ��)
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

//���ĵ� �迭���� key�� ���� ���� ���� ������ ������ ���� (���� Ȱ��)
int findSameNumBySum( int* arr , size_t length , int key )
{
	if( arr == NULL )
	{
		return 0;
	}
	return findSameNumIter(arr, 0, length-1, key);
}


//���� ���� ������ ���� ���ؼ� ���� idx���� ���� �� ������ ����
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

