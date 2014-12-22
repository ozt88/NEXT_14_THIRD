// HW2C.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "stdlib.h"
#include <crtdbg.h>
#define MAX_SIZE 100
#define MAX_VALUE 1000

template<class T>
void Swap(T* arr, int dst, int src)
{
	T temp = arr[dst];
	arr[dst] = arr[src];
	arr[src] = temp;
}

int RandomizedPartition(int* arr, int start, int last)
{
	_ASSERT(arr != NULL);
	int pivotIdx = start + rand() % ( last - start );
	int pivotValue = arr[pivotIdx];
	int endOfLowBlock = start - 1;

	Swap(arr, pivotIdx, last);
	pivotIdx = last;

	for(int checkIdx = start; checkIdx < last; checkIdx++)
	{
		if(arr[checkIdx] < pivotValue)
		{
			Swap(arr, ++endOfLowBlock, checkIdx);
		}
	}

	Swap(arr, endOfLowBlock + 1, pivotIdx);
	pivotIdx = endOfLowBlock + 1;

	return pivotIdx;
}

int SelectionIter(int* arr, int start, int last, int k)
{
	if(start >= last)
	{
		return arr[start];
	}

	int pivot = RandomizedPartition(arr, start, last);
	if(pivot == k)
	{
		return arr[pivot];
	}
	else if(pivot > k)
	{
		return SelectionIter(arr, start, pivot - 1, k);
	}
	else
	{
		return SelectionIter(arr, pivot + 1, last, k);
	}
}

int Selection(int* arr, size_t size, int k)
{
	if(arr == NULL || size == 0 )
	{
		fputs("Input Array Error!", stderr);
		return 1;
	}
	return SelectionIter(arr, 0, size - 1, k);
}


int QuickSortIter(int* arr, int start, int last)
{
	if(arr == NULL )
	{
		fputs("Input Array Error!", stderr);
		return 1;
	}
	if(start >= last)
	{
		return 0;
	}
	int pivot = RandomizedPartition(arr, start, last);
	QuickSortIter(arr, start, pivot - 1);
	QuickSortIter(arr, pivot + 1, last);
	return 0;
}

int QuickSort(int* arr, size_t size)
{
	if(arr == NULL || size == 0)
	{
		fputs("Input Array Error!", stderr);
		return 1;
	}
	return QuickSortIter(arr, 0, size - 1);
}

bool IsSelected(int* arr, size_t size, int k)
{
	int selectedValue = Selection(arr, size, k);
	QuickSort(arr, size);
	return arr[k] == selectedValue ? true : false;
}

bool SelectionTest(int* arr, size_t size)
{
	bool ret = false;
	for(int i = 0; i < 1000; ++i)
	{
		ret = IsSelected(arr, size, rand() % size);
		if(ret == false)
		{
			break;
		}
	}
	return ret;
}
int _tmain(int argc, _TCHAR* argv[])
{
	size_t size = rand()%MAX_SIZE;
	int test[MAX_SIZE] = {0, };
	for(int i = 0; i < size; ++i)
	{
		test[i] = rand() % MAX_VALUE;
	}
	char* msg = SelectionTest(test, size) ? "SUCCESS!\n" : "FALSE\n";
	fputs(msg, stdout);
	return 0;
}

