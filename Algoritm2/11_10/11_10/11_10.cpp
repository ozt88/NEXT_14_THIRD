// 11_10.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#define SCORE_MAX 101
int calculateRanks(int* score, int* rank, int totalNum)
{
	if(score == NULL) 
		return -1;
	int scoreBoard[SCORE_MAX] = {0, };
	for(int idx = 0; idx < totalNum; ++idx)
	{
		scoreBoard[score[idx]]++;
	}

	for(int score = 1; score < SCORE_MAX; ++score)
	{

	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

