#include "stdafx.h"
#include "include.h"

int ExtractMaxHeap(Heap_t* heap, int* maxValue)
{
	if(heap == NULL)
		return -1;
	int size = heap->size;
	Swap(heap, 1, --( heap->size ), size);
	*maxValue = heap->element[heap->size];
	MaxHeapify(heap, 1);

	return 0;
}

void TestExtractMaxHeap()
{
	Heap_t* testHeap = MakeTestRandomHeap();
	int resultValue = 0;
	MaxHeapBuild(testHeap);
	printf("\n=====Test Extract MaxHeap=====\n");
	printf("\n------before-----\n");
	PrintHeap(testHeap);
	ExtractMaxHeap(testHeap, &resultValue);
	printf("\n------after-----\n");
	PrintHeap(testHeap);
	printf("\nExtracted Value : %d\n", resultValue);

}