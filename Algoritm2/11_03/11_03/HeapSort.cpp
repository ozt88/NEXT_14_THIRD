#include "stdafx.h"
#include "include.h"


void HeapSort(Heap_t* heap)
{
	MaxHeapBuild(heap);
	int size = heap->size;
	for(int idx = 2; idx < size; ++idx)
	{
		Swap(heap, 1, --( heap->size ), size);
		MaxHeapify(heap, 1);
	}
	heap->size = size;
}

void TestHeapSort()
{
	Heap_t* testHeap = MakeTestRandomHeap();
	HeapSort(testHeap);
	printf("=====Heap Sorted Array=====\n");
	PrintHeapLikeArray(testHeap);
}

