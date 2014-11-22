#include "stdafx.h"
#include "include.h"



int MaxHeapify(Heap_t* heap, int rootIdx)
{
	if(heap == NULL || rootIdx == 0)
		return -1;

	int leftIdx = 0;
	int rightIdx = 0;
	int maxIdx = rootIdx;
	if(heap->size > rootIdx * 2)
	{
		leftIdx = rootIdx * 2;
		if(heap->element[maxIdx] < heap->element[leftIdx])
			maxIdx = leftIdx;
	}
	if(heap->size > rootIdx * 2 + 1)
	{
		rightIdx = rootIdx * 2 + 1;
		if(heap->element[maxIdx] < heap->element[rightIdx])
			maxIdx = rightIdx;
	}

	if(maxIdx != rootIdx)
	{
		Swap(heap, rootIdx, maxIdx, heap->size);
		return MaxHeapify(heap, maxIdx);
	}

	return 0;
}