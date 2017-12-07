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

void Example02()
{
	lang::Array<char, 20> chBuf1;
	const char* w1 = "I am a game developer";
	chBuf1.setSize(strlen(w1)+1);
	for (int i = 0; i < strlen(w1); i++)
	{
		chBuf1[i] = w1[i];
	}
	chBuf1[strlen(w1)] = 0;
	std::cout << "array: \n";
	std::cout << chBuf1.begin() << std::endl;
	std::cout << "size: " << chBuf1.size() << std::endl;
	
	const char* w2 = "I am a dude";
	chBuf1.setSize(strlen(w2)+1);
	for (int i = 0; i < strlen(w2); i++)
	{
		chBuf1[i] = w2[i];
	}
	chBuf1[strlen(w2)] = 0;
	std::cout << "array: \n";
	std::cout << chBuf1.begin() << std::endl;
	std::cout << "size: " << chBuf1.size() << std::endl;

	chBuf1.setSize(chBuf1.size() - 1); // remove terminate null
	chBuf1.add(' ');
	chBuf1.add('a');
	chBuf1.add('n');
	chBuf1.add('d');
	chBuf1.add(' ');
	chBuf1.add('a');
	chBuf1.add(' ');
	chBuf1.add('g');
	chBuf1.add('a');
	chBuf1.add('m');
	chBuf1.add('e');
	chBuf1.add(' ');
	chBuf1.add('d');
	chBuf1.add('e');
	chBuf1.add('v');
	chBuf1.add('e');
	chBuf1.add('l');
	chBuf1.add('o');
	chBuf1.add('p');
	chBuf1.add('e');
	chBuf1.add('r');
	chBuf1.add('!');
	chBuf1.add('\0');
	std::cout << "array: \n";
	std::cout << chBuf1.begin() << std::endl;
	std::cout << "size: " << chBuf1.size() << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Example01\n";
	Example01();
	std::cout << "Press any key to continue...\n";
	getch();
	std::cout << "Example02\n";
	Example02();
	std::cout << "Press any key to quit...\n";
	getch();
	return 0;
}

