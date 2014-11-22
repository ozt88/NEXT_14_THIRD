#include "stdafx.h"
#include "include.h"

int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned)time(NULL));
	TestMaxHeapBuild();
	TestHeapSort();
	TestExtractMaxHeap();
	return 0;
}
