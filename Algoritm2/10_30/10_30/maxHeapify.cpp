// 10_30.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <crtdbg.h>
#define MAX_CAPACITY 20
#define MAX_NUM 100

struct heap_t
{
	~heap_t()
	{
		if( element != NULL )
		{
			delete element;
			element = NULL;
		}
	}
	int size;
	int capacity;
	int* element;
};

void swap( heap_t* heap , int srcPos , int dstPos )
{
	int temp = heap->element[srcPos];
	heap->element[srcPos] = heap->element[dstPos];
	heap->element[dstPos] = temp;
}

void max_heapify( heap_t* heap , int pos )
{
	//예외처리
	if( heap == NULL || heap->size < pos || pos == 0)
		return;

	int leftPos = 0 , rightPos = 0;
	//우선 maxPos를 검사 노드의 위치값으로
	int maxPos = pos;

	//왼쪽 자식이 있으면 왼쪽자식과 비교하여 maxPos갱신
	if( heap->size > pos * 2 )
	{
		leftPos = pos * 2;
		if( heap->element[leftPos] > heap->element[maxPos] )
			maxPos = leftPos;
	}

	//오른쪽 자식이 있으면 오른쪽 자식과 비교하여 maxPos갱신
	if( heap->size > pos * 2 + 1 )
	{
		rightPos = pos * 2 + 1;
		if( heap->element[rightPos] > heap->element[maxPos] )
			maxPos = rightPos;
	}

	//maxPos가 갱신되었으면 pos와 maxPos에 있는 원소 스왑후에
	//maxPos위치에서부터 다시 heapify적용
	if( maxPos != pos )
	{
		swap( heap , maxPos , pos );
		return max_heapify( heap , maxPos );
	}
}


void printHeap(heap_t* heap)
{
	for( int idx = 1; idx < heap->size; ++idx )
	{
		printf( "%d " , heap->element[idx] );
	}
	printf( "\n" );

	//해당 줄에 따라서 개행하기위해 line이라는 값으로 루프돕니다.
	for( int line = 1; line < heap->size; line *= 2 )
	{
		for( int i = 0; i < line; ++i )
		{
			if( i + line >= heap->size )
			{
				break;
			}
			printf( "%d " , heap->element[i + line] );
		}
		printf( "\n" );
	}
}

//랜덤한 배열을 만들고 뒤에서부터 MaxHeapify를 적용하여 MaxHeap을 만드는 함수
heap_t* makeSampleMaxHeap()
{
	heap_t* testHeap = new heap_t();
	int* heapData = ( int* )malloc( sizeof( int )*MAX_CAPACITY );
	memset( heapData , 0 , sizeof( int )*MAX_CAPACITY );

	testHeap->capacity = MAX_CAPACITY;
	testHeap->size = rand() % MAX_CAPACITY;

	for( int forwardIdx = 1; forwardIdx < testHeap->size; ++forwardIdx )
	{
		heapData[forwardIdx] = rand() % MAX_NUM;
	}

	testHeap->element = heapData;

	for( int backwardIdx = testHeap->size - 1; backwardIdx > 0; --backwardIdx )
	{
		max_heapify( testHeap , backwardIdx );
	}

	return testHeap;
}

//MaxHeap인지 확인하는 함수
bool isMaxHeap( heap_t* heap )
{
	if( heap == NULL )
	{
		return 0;
	}
	int leftChildIdx = 0;
	int rightChildIdx = 0;
	for( int idx = 1; idx < heap->size; ++idx )
	{
		if( 2 * idx < heap->size )
		{
			leftChildIdx = 2 * idx;
			if( heap->element[leftChildIdx] > heap->element[idx] )
				return false;
		}
		if( 2 * idx  + 1 < heap->size )
		{
			rightChildIdx = 2 * idx + 1;
			if( heap->element[rightChildIdx] > heap->element[idx] )
				return false;
		}
	}
	return true;
}

//MaxHeapify된 Heap을 출력하고 MaxHeap이 맞는지 출력하는 함수
void test_heapify()
{
	heap_t* testHeap = makeSampleMaxHeap();
	printHeap( testHeap );
	char* strIsMaxHeap = isMaxHeap( testHeap ) ? "This is Max Heap." : "This is not Max Heap.";
	printf( "%s\n" , strIsMaxHeap );

	if( testHeap != nullptr )
	{
		delete testHeap;
		testHeap = nullptr;
	}
}

//testNum만큼 heapify를 검사하는 함수
void testIter(int testNum)
{
	for( int i = 0; i < testNum; ++i )
	{
		heap_t* testHeap = makeSampleMaxHeap();
		_ASSERT( isMaxHeap( testHeap ) );
		if( testHeap != nullptr )
		{
			delete testHeap;
			testHeap = nullptr;
		}
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	srand( (unsigned int)time( NULL ) );
	test_heapify();
	testIter( 10000 );
	return 0;
}

