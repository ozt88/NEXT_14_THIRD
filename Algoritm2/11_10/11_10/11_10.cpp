// 11_10.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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

