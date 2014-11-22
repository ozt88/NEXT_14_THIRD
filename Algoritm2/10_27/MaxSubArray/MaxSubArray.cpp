// MaxSubArray.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#define MAX_ARRAY_SIZE 20

struct SubArrInfo
{
	SubArrInfo()
	{
		sum = 0;
		leftIdx = 0;
		rightIdx = 0;
	}
	int sum;
	int leftIdx;
	int rightIdx;
	void out()
	{
		printf( "sum: %d, leftIdx: %d, rightIdx: %d\n", sum, leftIdx, rightIdx );
	}
};

//T(n) = O(n) 연산시간의 Maxium SubArr Problem 
SubArrInfo GetMaxSubArrInfoWithOrderN( int* subArr , size_t length )
{
	SubArrInfo curSubArrInfo;
	SubArrInfo maxSubArrInfo;
	if( subArr != NULL )
	{
		for( size_t idx = 0; idx < length; ++idx )
		{
			curSubArrInfo.sum += subArr[idx];
			if( curSubArrInfo.sum < 0 )
			{
				curSubArrInfo.sum = 0;
				curSubArrInfo.leftIdx = idx + 1;
			}
			else
			{
				curSubArrInfo.rightIdx = idx;
				if( curSubArrInfo.sum > maxSubArrInfo.sum )
				{
					maxSubArrInfo = curSubArrInfo;
				}
			}
		}

	}
	return maxSubArrInfo;
}

//T(n) = O(n*log(n)) 연산시간의 Maxium SubArr Problem 
SubArrInfo MaxWithCenterIdx( int* subArr , int leftIdx , int rightIdx, int centerIdx )
{
	SubArrInfo maxInfo;
	int sum = 0;
	int leftMaxSum = 0;
	int rightMaxSum = 0;
	for( int idx = centerIdx; idx >= leftIdx; --idx )
	{
		sum += subArr[idx];
		if( leftMaxSum < sum )
		{
			leftMaxSum = sum;
			maxInfo.leftIdx = idx;
		}
	}

	sum = 0;
	for( int idx = centerIdx + 1; idx <= rightIdx; ++idx )
	{
		sum += subArr[idx];
		if( rightMaxSum < sum )
		{
			rightMaxSum = sum;
			maxInfo.rightIdx = idx;
		}
	}

	maxInfo.sum = leftMaxSum + rightMaxSum;
	return maxInfo;
}

SubArrInfo MaxSubArrIter( int* subArr , int leftIdx , int rightIdx )
{
	SubArrInfo maxInfo;
	if( rightIdx > leftIdx )
	{
		int centerIdx = leftIdx + ( rightIdx - leftIdx ) / 2;
		SubArrInfo leftInfo = MaxSubArrIter( subArr , leftIdx , centerIdx );
		SubArrInfo rightInfo = MaxSubArrIter( subArr , centerIdx + 1 , rightIdx );
		SubArrInfo centerInfo = MaxWithCenterIdx( subArr , leftIdx , rightIdx , centerIdx );
		maxInfo = leftInfo.sum > rightInfo.sum ? leftInfo : rightInfo;
		if( maxInfo.sum < centerInfo.sum )
			maxInfo = centerInfo;
	}
	if( rightIdx == leftIdx )
	{
		maxInfo.sum = subArr[leftIdx];
		maxInfo.leftIdx = leftIdx;
		maxInfo.rightIdx = rightIdx;
	}
	return maxInfo;
}

SubArrInfo GetMaxSubArrInfoWithDivide( int* subArr , size_t length )
{
	return MaxSubArrIter(subArr , 0 , length - 1);
}

//T(n) = O(n^2) 연산시간의 Maxium SubArr Problem 
SubArrInfo GetMaxSubArrInfoWithOrderNSquare( int* subArr , size_t length )
{
	SubArrInfo maxSubArrInfo;
	SubArrInfo curSubArrInfo;

	for( size_t idx = 0; idx < length; ++idx )
	{
		int sum = 0;
		curSubArrInfo.sum = subArr[idx];
		curSubArrInfo.leftIdx = idx;
		curSubArrInfo.rightIdx = idx;

		for( size_t subIdx = idx; subIdx < length; ++subIdx )
		{
			sum += subArr[subIdx];
			if( curSubArrInfo.sum < sum)
			{
				curSubArrInfo.sum = sum;
				curSubArrInfo.rightIdx = subIdx;
			}
		}
		if( maxSubArrInfo.sum < curSubArrInfo.sum )
		{
			maxSubArrInfo = curSubArrInfo;
		}
	}

	return maxSubArrInfo;
}


int _tmain(int argc, _TCHAR* argv[])
{
	//랜덤 데이터 생성
	srand( time( NULL ) );
	size_t randomSize = rand() % MAX_ARRAY_SIZE;
	int randomArr[MAX_ARRAY_SIZE] = { 0 , };
	for( size_t i = 0; i < randomSize; ++i )
	{
		randomArr[i] = rand() % (MAX_ARRAY_SIZE*2) - MAX_ARRAY_SIZE;
		printf( "%d " , randomArr[i] );
	}
	printf( "\n" );

	//Test
	GetMaxSubArrInfoWithOrderNSquare( randomArr , randomSize ).out();
	GetMaxSubArrInfoWithDivide( randomArr , randomSize ).out();
	GetMaxSubArrInfoWithOrderN( randomArr , randomSize ).out();

	return 0;
}

