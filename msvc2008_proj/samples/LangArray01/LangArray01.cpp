// LangArray01.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


void PrintArray(lang::Array<char, 8>& arr)
{
	std::cout << "array: \n";
	for (int i = 0; i < arr.size(); i++)
	{
		std::cout << "a[" << i << "]=" << arr[i] << std::endl;
	}
	std::cout << "size: " << arr.size() << std::endl;
}

void Example01()
{
	lang::Array<char, 8> chBuf1;
	chBuf1.add('w');
	chBuf1.add('o');
	chBuf1.add('l');
	chBuf1.add('d');
	PrintArray(chBuf1);
	chBuf1.add(2, 'r');
	PrintArray(chBuf1);
	chBuf1.add(0, ' ');
	chBuf1.add(0, 'o');
	chBuf1.add(0, 'l');
	chBuf1.add(0, 'l');
	chBuf1.add(0, 'e');
	chBuf1.add(0, 'H');
	chBuf1.add('!');
	PrintArray(chBuf1);
	int l_count = 0;
	for (char* b = chBuf1.begin(); b != chBuf1.end(); b++)
	{
		if ((*b) == 'l') l_count++;
	}
	std::cout << "l character met " << l_count << " times\n";
	chBuf1.clear();
	PrintArray(chBuf1);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Example01();
	std::cout << "Press any key to quit...\n";
	getch();
	return 0;
}

