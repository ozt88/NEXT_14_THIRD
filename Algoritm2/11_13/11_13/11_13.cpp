// 11_13.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#define MAX_ARR_NUM 5
#define MAX_NUM 10000




int CountingSort(int* inputArr, int inputSize, 
				 int* resultArr, int k)
{
	if(inputArr == NULL )
	{
		return -1;
	}
	int* countArr = (int*) malloc(sizeof(int)*k);
	memset(countArr, 0, sizeof(int)*k);

	for(int inputIdx = 0; inputIdx < inputSize; ++inputIdx)
	{
		countArr[inputArr[inputIdx]]++;
	}
	for(int countIdx = 1; countIdx < k; ++countIdx)
	{
		countArr[countIdx] += countArr[countIdx - 1];
	}
	for(int resultIdx = inputSize - 1; resultIdx >= 0; --resultIdx)
	{
		resultArr[ --(countArr[inputArr[resultIdx]]) ] = inputArr[resultIdx];
	}

	if(countArr != NULL)
	{
		free(countArr);
		countArr = NULL;
	}
	return 0;
}

int CountingSortByDigit(int* arr, int inputSize, int digitUnit, int digit)
{
	if(arr == NULL)
	{
		return -1;
	}
	int* countArr = (int*) malloc(sizeof(int)*digitUnit);
	int* resultArr = (int*) malloc(sizeof(int)*inputSize);
	memset(countArr, 0, sizeof(int)*digitUnit);
	memset(resultArr, 0, sizeof(int)*inputSize);
	int input = 0;

	for(int inputIdx = 0; inputIdx < inputSize; ++inputIdx)
	{
		input = arr[inputIdx] % ( digit*digitUnit ) / digit;
		countArr[input]++;
	}
	for(int countIdx = 1; countIdx < digitUnit; ++countIdx)
	{
		countArr[countIdx] += countArr[countIdx - 1];
	}
	for(int resultIdx = inputSize - 1; resultIdx >= 0; --resultIdx)
	{
		input = arr[resultIdx] % ( digit*digitUnit ) / digit;
		resultArr[--( countArr[input] )] = arr[resultIdx];
	}

	for(int copyIdx = 0; copyIdx < inputSize; ++copyIdx)
	{
		arr[copyIdx] = resultArr[copyIdx];
	}

	if(resultArr)
	{
		free(resultArr);
		resultArr = NULL;
	}
	if(countArr)
	{
		free(countArr);
		countArr = NULL;
	}

	return 0;
}

int RadixSort(int* arr, int size, int digitUnit)
{
	if(arr == NULL)
	{
		return -1;
	}
	for(int digit = 1; digit < MAX_NUM; digit*=digitUnit)
	{
		CountingSortByDigit(arr, size, digitUnit, digit);
	}
	return 0;
}

int testCountingSort(int* arr, int size)
{
	if(arr == NULL)
	{
		return -1;
	}
	int resultArr[MAX_ARR_NUM] = {0, };
	printf("CountingSort\nbefore:");
	for(int i = 0; i < MAX_ARR_NUM; ++i)
	{
		arr[i] = rand() % MAX_NUM;
		printf("%d ,", arr[i]);
	}
	printf("\nafter:");
	CountingSort(arr, MAX_ARR_NUM, resultArr, MAX_NUM);
	for(int i = 0; i < MAX_ARR_NUM; ++i)
	{
		printf("%d ,", resultArr[i]);
	}
	printf("\n");
	return 0;
}


int testRadixSort(int* arr, int size)
{
	if(arr == NULL)
	{
		return -1;
	}
	printf("RadixSort\nbefore:");
	for(int i = 0; i < MAX_ARR_NUM; ++i)
	{
		arr[i] = rand() % MAX_NUM;
		printf("%d ,", arr[i]);
	}
	printf("\nafter:");
	RadixSort(arr, MAX_ARR_NUM, 10);
	for(int i = 0; i < MAX_ARR_NUM; ++i)
	{
		printf("%d ,", arr[i]);
	}
	printf("\n");
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned) time(NULL));
	int test[MAX_ARR_NUM] = {0,};

	testCountingSort(test, MAX_ARR_NUM);
	testRadixSort(test, MAX_ARR_NUM);
	
	return 0;
}

