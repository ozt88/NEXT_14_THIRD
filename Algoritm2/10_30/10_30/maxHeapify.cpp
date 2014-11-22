// 10_30.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
	//����ó��
	if( heap == NULL || heap->size < pos || pos == 0)
		return;

	int leftPos = 0 , rightPos = 0;
	//�켱 maxPos�� �˻� ����� ��ġ������
	int maxPos = pos;

	//���� �ڽ��� ������ �����ڽİ� ���Ͽ� maxPos����
	if( heap->size > pos * 2 )
	{
		leftPos = pos * 2;
		if( heap->element[leftPos] > heap->element[maxPos] )
			maxPos = leftPos;
	}

	//������ �ڽ��� ������ ������ �ڽİ� ���Ͽ� maxPos����
	if( heap->size > pos * 2 + 1 )
	{
		rightPos = pos * 2 + 1;
		if( heap->element[rightPos] > heap->element[maxPos] )
			maxPos = rightPos;
	}

	//maxPos�� ���ŵǾ����� pos�� maxPos�� �ִ� ���� �����Ŀ�
	//maxPos��ġ�������� �ٽ� heapify����
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

	//�ش� �ٿ� ���� �����ϱ����� line�̶�� ������ �������ϴ�.
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

//������ �迭�� ����� �ڿ������� MaxHeapify�� �����Ͽ� MaxHeap�� ����� �Լ�
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

//MaxHeap���� Ȯ���ϴ� �Լ�
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

//MaxHeapify�� Heap�� ����ϰ� MaxHeap�� �´��� ����ϴ� �Լ�
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

//testNum��ŭ heapify�� �˻��ϴ� �Լ�
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

