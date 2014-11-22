// 11_06.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "include.h"



int quickSort(int* arr, int startIdx, int endIdx)
{
	int pivotIdx = 0;
	if(startIdx < endIdx)
	{
		pivotIdx = partition(arr, startIdx, endIdx);
		quickSort(arr, startIdx, pivotIdx - 1);
		quickSort(arr, pivotIdx + 1, endIdx);
	}
	return pivotIdx;
}

bool quickSort_check(int* arr, size_t size)
{
	int pivot = quickSort(arr, 0, size - 1);
	char* result = isRightPivot(arr, 0, size - 1, pivot) ?
		"PARTITION SUCCESS\n" : "PARTITION FAILED\n";
	printf("%s", result);

	return result;
}

void test_quicksort()
{
	int* arrList[MAX_ARR_NUM] = {0, };
	int successCount = 0;
	printf("\n=====RANDOM TEST=====\n");
	for(successCount = 0; successCount < MAX_ARR_NUM; ++successCount)
	{
		arrList[successCount] = MakeRandomArr(successCount + 1);
		if(quickSort_check(arrList[successCount], successCount + 1))
		{
			if(arrList[successCount])
			{
				delete arrList[successCount];
				arrList[successCount] = NULL;
			}
		}
		else
		{
			break;
		}
	}

	printf("\n=====INCREASING TEST=====\n");
	for(successCount = 0; successCount < MAX_ARR_NUM; ++successCount)
	{
		arrList[successCount] = MakeIncreaseArr(successCount + 1);
		if(quickSort_check(arrList[successCount], successCount + 1))
		{
			if(arrList[successCount])
			{
				delete arrList[successCount];
				arrList[successCount] = NULL;
			}
		}
		else
		{
			break;
		}
	}

	printf("\n=====DECREASING TEST=====\n");
	for(successCount = 0; successCount < MAX_ARR_NUM; ++successCount)
	{
		arrList[successCount] = MakeDecreaseArr(successCount + 1);
		if(quickSort_check(arrList[successCount], successCount + 1))
		{
			if(arrList[successCount])
			{
				delete arrList[successCount];
				arrList[successCount] = NULL;
			}
		}
		else
		{
			break;
		}
	}
}
