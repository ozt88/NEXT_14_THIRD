// prac.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include < windows.h >     // windows.h�� ��Ŭ��� ��ŵ�ϴ�.
#include <iostream>

using namespace std;

void gotoxy(int x, int y)
{
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setcolor(int color, int bgcolor)
{
	color &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ( bgcolor << 4 ) | color);
}

int main()
{          
	char buf[100] = {0, };
	for(int i = 0; i < 100; ++i)
	{
		gotoxy(0, i);
		std::cout << "Hello, world!" << endl << endl;
		gotoxy(0, i + 20);
		std::cout << "                                                            " << endl;
		gets_s(buf);

	}
	return 0;
}

