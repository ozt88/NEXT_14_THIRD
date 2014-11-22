#define MAX_CAPACITY 20
#define MAX_NUM 100
#define OUT
struct Heap_t
{
	//0번째는 사용하지 않습니다.
	Heap_t()
	{
		size = 1;
		capacity = MAX_CAPACITY;
		element = NULL;
	}
	~Heap_t()
	{
		if(element != NULL)
		{
			delete element;
			element = NULL;
		}
	}

	int size;
	int capacity;
	int* element;

};

int			Swap(Heap_t* heap, int srcPos, int dstPos, int size);
Heap_t*		MakeTestRandomHeap();
void		PrintHeap(Heap_t* heap);
void		PrintHeapLikeArray(Heap_t* heap);

int			MaxHeapify(Heap_t* heap, int rootIdx);
void		MaxHeapBuild(Heap_t* heap);
void		TestMaxHeapBuild();

void		HeapSort(Heap_t* heap);
void		TestHeapSort();

int			ExtractMaxHeap(Heap_t* heap, OUT int* maxValue);
void		TestExtractMaxHeap();

int			IncreaseKeyMaxHeap(Heap_t* heap, int idx, int key);
int			InsertMaxHeap(Heap_t* heap, int key);
