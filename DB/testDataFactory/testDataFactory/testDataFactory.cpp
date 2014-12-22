// testDataFactory.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#define NUMOFRECORDS 1000000

int _tmain(int argc, _TCHAR* argv[])
{
	std::ofstream outstream;
	std::string output;
	char sint[10] = {0, };

	outstream.open("book_data.csv");
	if(outstream.fail())
	{
		std::cout << " error \n";
		return 1;
	}

	srand((unsigned) time(NULL));
	for(int i = 0; i < NUMOFRECORDS; i++)
	{
		output = "";
		_itoa_s(i, sint, 10); output.append(sint); // id
		output.append(",");
		output.append("title"); output.append(sint); // title
		output.append(",");
		output.append("author");
		_itoa_s(( rand() % 1000 ), sint, 10); output.append(sint); // author
		outstream << output << std::endl;
	}
	outstream.close();
	return 0;
}

