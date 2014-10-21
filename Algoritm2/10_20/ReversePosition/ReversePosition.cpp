// CountReversePosition.cpp : ������ ������ �ľ��ϴ� �Լ�

#include "stdafx.h"

void copy( int* srcStart , int* srcEndPoint , int* dstStart )
{
	while( srcStart != srcEndPoint )
	{
		*( dstStart++ ) = *( srcStart++ );
	}
}

//�⺻���� MergeSort���� Merge�κи� �����ϸ� ������ ������ �Ǵ��� �� �ִ�.
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
			//�� �迭�� �����Ҷ� firstIdx�� ���� secondIdx���� ������ 
			//������ ���ĵǾ� �����Ƿ� firstIdx���� ù��° �迭�� ��(secondStartIdx -1)���� ��� ���ڵ��� 
			//secondIdx��°�� ���ڿ� ������ �ȴ�. �̰��� ��ü ī���Ϳ� �����ָ� �ȴ�.
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

//�׸��� �� recursion���� ��ȯ�� ���� ���ؼ� �������ָ� ��ü ������ ������ �Ǻ��� �� �ִ�.
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

