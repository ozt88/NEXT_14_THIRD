// 12-15(bfs).cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
struct Node_t
{
	int _data = 0;
	bool _isVisited = false;
	std::vector<Node_t*> _neighbors;
};

int BFS(Node_t* sourceNode)
{
	if(sourceNode == NULL)
		return 1;

	Node_t* checkNode = NULL;
	std::queue<Node_t*> checkingQueue;

	sourceNode->_isVisited = true;
	checkingQueue.push(sourceNode);

	while(!checkingQueue.empty())
	{
		checkNode = checkingQueue.front();
		printf("%d", checkNode->_data);
		for(auto neighbor : checkNode->_neighbors)
		{
			if(!neighbor->_isVisited)
			{
				neighbor->_isVisited = true;
				checkingQueue.push(neighbor);
			}
		}
		checkingQueue.pop();
	}
	return 0;
}



int _tmain(int argc, _TCHAR* argv[])
{

	return 0;
}

