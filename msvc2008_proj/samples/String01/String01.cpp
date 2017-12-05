// String01.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

void PrintString(const lang::String& s)
{
	char buf[64];
	s.getBytes(&buf[0], 64, "ASCII-7");
	std::cout << buf << std::endl;
}

// ������������ ������
void Example_ctors()
{
	lang::String s1;									// ����������� �� ���������
	lang::String s2("Hello, world!");					// ����������� �� ANSI-�����
	lang::String s3("Hello, world!", strlen("Hello"));	// ����������� �� ������� �������� ANSI � �����
	lang::String s4(s2);								// ����������� �����
	
	// ��������, ��� ����������
	PrintString(s1);
	PrintString(s2);
	PrintString(s3);
	PrintString(s4);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Example_ctors();
	std::cout << "Press any key to quit...\n";
	getch();
	return 0;
}

