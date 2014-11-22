#pragma once

#define OUT 
#define MAX_SIZE 10
#define MAX_NUM 100
#define MAX_ARR_NUM 32

int		partition(int* arr, int startIdx, int endIdx);
void	test_partition();
bool	isRightPivot(int* arr, int startIdx, int endIdx, int pivot);
bool	partition_check(int* arr, int size);

int		quickSort(int* arr, int startIdx, int endIdx);
bool	quickSort_check(int* arr, size_t size);
void	test_quicksort();


int*	MakeRandomArr(size_t size);
int*	MakeIncreaseArr(size_t size);
int*	MakeDecreaseArr(size_t size);

void	PrintArr(int* arr, size_t size);
void	Swap(int*arr, int dstIdx, int srcIdx, int size);
