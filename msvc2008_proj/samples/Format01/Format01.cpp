// Format01.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include "stdafx.h"


void PrintString(const lang::String& s)
{
	char buf[64];
	s.getBytes(&buf[0], 64, "ASCII-7");
	std::cout << buf << std::endl;
}

//  онструкторы строки
void Example_Format()
{
	lang::Format fmt("second is {1,##.00#}; first is {0,0.00}", 27.857, 137.5649 );
	lang::String s1 = fmt.format();

	lang::Format fmt2("second is {1,00.00#}; first is {0,000000.00}", 27.8, 137.5649 );
	lang::String s2 = fmt2.format();

	
	// печатаем, что получилось
	PrintString(s1);
	PrintString(s2);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Example_Format();
	std::cout << "Press any key to quit...\n";
	getch();
	return 0;
}