#include "stdafx.h"
#include "include.h"

int* MakeRandomArr(size_t size)
{
	int* resultArr = (int*) malloc(sizeof(int)*size);
	memset(resultArr, NULL, sizeof(int)*size);

	for(size_t idx = 0; idx < size; ++idx)
	{
		resultArr[idx] = rand() % MAX_NUM;
	}
	return resultArr;
}

int* MakeIncreaseArr(size_t size)
{
	int* resultArr = (int*) malloc(sizeof(int)*size);
	memset(resultArr, NULL, sizeof(int)*size);

	for(size_t idx = 0; idx < size; ++idx)
	{
		resultArr[idx] = rand() % MAX_NUM;
		if(idx != 0)
		{
			resultArr[idx] += resultArr[idx - 1];
		}
	}
	return resultArr;
}

int* MakeDecreaseArr(size_t size)
{
	int* resultArr = (int*) malloc(sizeof(int)*size);
	memset(resultArr, NULL, sizeof(int)*size);

	for(size_t idx = 0; idx < size; ++idx)
	{
		resultArr[idx] = 100 + rand() % MAX_NUM;
		if(idx != 0)
		{
			resultArr[idx] -= resultArr[idx - 1];
		}
	}
	return resultArr;
}

void PrintArr(int* arr, size_t size)
{
	for(size_t idx = 0; idx < size; ++idx)
	{
		printf("%d ", arr[idx]);
	}
	printf("\n");
}


void Swap(int*arr, int dstIdx, int srcIdx, int size)
{
	if(arr == NULL || dstIdx >= size || srcIdx >= size)
	{
		return;
	}
	int temp = arr[dstIdx];
	arr[dstIdx] = arr[srcIdx];
	arr[srcIdx] = temp;
}
