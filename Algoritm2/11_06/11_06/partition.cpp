#include "stdafx.h"
#include "include.h"

int partition(int* arr, int startIdx, int endIdx)
{
	int endOfLowBlock = startIdx - 1;
	int pivotIdx = endIdx;
	for(int checkIdx = startIdx; checkIdx < pivotIdx; checkIdx++)
	{
		if(arr[pivotIdx] > arr[checkIdx])
		{
			Swap(arr, ++endOfLowBlock, checkIdx, endIdx + 1);
		}
	}
	Swap(arr, endOfLowBlock + 1, pivotIdx, endIdx + 1);
	pivotIdx = endOfLowBlock + 1;
	return pivotIdx;
}

void test_partition()
{
	int* arrList[MAX_ARR_NUM] = {0, };
	int successCount = 0;
	printf("\n=====RANDOM TEST=====\n");
	for(successCount = 0; successCount < MAX_ARR_NUM; ++successCount)
	{
		arrList[successCount] = MakeRandomArr(successCount + 1);
		if(partition_check(arrList[successCount], successCount + 1))
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
		if(partition_check(arrList[successCount], successCount + 1))
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
		if(partition_check(arrList[successCount], successCount + 1))
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

bool partition_check(int* arr, int size)
{
	int pivot = partition(arr, 0, size - 1);
	char* result = isRightPivot(arr, 0, size - 1, pivot) ? 
		"PARTITION SUCCESS\n": "PARTITION FAILED\n";
	printf("%s", result);

	return result;
}

bool isRightPivot(int* arr, int startIdx, int endIdx, int pivot)
{
	int checkIdx = pivot;
	while(checkIdx-- > startIdx)
	{
		if(arr[checkIdx] > arr[pivot])
		{
			return false;
		}
	}
	checkIdx = pivot;
	while(checkIdx++ < endIdx)
	{
		if(arr[checkIdx] < arr[pivot])
		{
			return false;
		}
	}

	return true;
}

