#include "stdafx.h"
#include "include.h"

void MaxHeapBuild(Heap_t* heap)
{
	for(int backwardIdx = heap->size - 1; backwardIdx > 0; --backwardIdx)
	{
		MaxHeapify(heap, backwardIdx);
	}
}

void TestMaxHeapBuild()
{
	Heap_t* testHeap = MakeTestRandomHeap();
	printf("\n======MaxHeap Build Test======\n");
	printf("\n----------before----------\n");
	PrintHeap(testHeap);

	MaxHeapBuild(testHeap);
	printf("\n----------after----------\n");
	PrintHeap(testHeap);
	printf("\n");

}