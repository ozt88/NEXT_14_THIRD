#include "stdafx.h"
#include "include.h"

int Swap(Heap_t* heap, int srcPos, int dstPos, int size)
{
	if(heap == NULL || srcPos >= size || dstPos >= size)
	{
		return -1;
	}

	int temp = heap->element[srcPos];
	heap->element[srcPos] = heap->element[dstPos];
	heap->element[dstPos] = temp;

	return 0;
}

Heap_t* MakeTestRandomHeap()
{
	Heap_t* ret = new Heap_t();
	
	ret->capacity = MAX_CAPACITY;
	ret->size = rand() % MAX_CAPACITY;
	int* heapData = (int*) malloc(sizeof(int)*ret->size);
	memset(heapData, NULL, sizeof(int)*ret->size);
	for(int elemIdx = 1; elemIdx < ret->size; ++elemIdx)
	{
		heapData[elemIdx] = rand() % MAX_NUM;
	}
	ret->element = heapData;

	return ret;
}

void PrintHeap(Heap_t* heap)
{
	for(int line = 1; line < heap->size; line *= 2)
	{
		for(int i = 0; i < line; ++i)
		{
			if(i + line >= heap->size)
			{
				break;
			}
			printf("%d ", heap->element[i + line]);
		}
		printf("\n");
	}
}

void PrintHeapLikeArray(Heap_t* heap)
{
	printf("\n[ ");
	for(int i = 1; i < heap->size; ++i)
	{
		printf("%d ,", heap->element[i]);
	}
	printf(" ]\n");
}