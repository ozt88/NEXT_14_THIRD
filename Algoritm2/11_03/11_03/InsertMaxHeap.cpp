#include "stdafx.h"
#include "include.h"

int IncreaseKeyMaxHeap(Heap_t* heap, int idx, int key)
{
	if(key < heap->element[idx])
	{
		return -1;
	}

	heap->element[idx] = key;
	int size = heap->size;
	int parent = idx / 2;
	while(parent >= 0 && heap->element[parent] > heap->element[idx])
	{
		Swap(heap, parent, idx, size);
		idx = parent;
		parent = idx / 2;
	}
}


int InsertMaxHeap(Heap_t* heap, int key)
{
	if(heap == NULL)
		return 0;
	if(++heap->size > heap->capacity)
	{
		//DOUBLING
	}
	heap->element[heap->size - 1] = key - 1;
	return IncreaseKeyMaxHeap(heap, heap->size - 1, key);
}

