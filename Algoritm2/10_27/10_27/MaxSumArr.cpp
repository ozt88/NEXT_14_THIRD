// 10_27.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

int MaxSumArr( int* arr , size_t length )
{
	if( arr == NULL ) return -1;
	int maxSumIdx = 0;
	int maxSum = arr[0];
	int sum = arr[0];
	for( size_t idx = 1; idx < length; ++idx )
	{
		sum += arr[idx];
		if( sum > maxSum )
		{
			maxSum = sum;
			maxSumIdx = idx;
		}
	}
	return maxSumIdx;
}

int _tmain(int argc, _TCHAR* argv[])
{

	return 0;
}

