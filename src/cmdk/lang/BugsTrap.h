#ifndef CMDK_BUGSTRAP_H
#define CMDK_BUGSTRAP_H

#ifdef CMDK_BUGS_TRAPPING_MODE
// ������� ��� ������ ������. � �������� ��������� �������� ������ � ��������� ������.
void CMDK_AddBugTrappedInDesc(const char* bugDesc);
// ������� ��� ������ ����� � ������ � ������� - ��� ������ ������� �������� ��� ����� � ������.
void CMDK_AddBugTrappedInFileAndLine(const char* fname, int line);
// ������� ��� ������ �������� ����� ���������� - ��� ������ ������� �������� ��� � �������� ���������.
void CMDK_AddBugTrappedInIntParam(const char* name, int value);
#else
#define CMDK_AddBugTrappedInDesc(bugDesc) ((void) 0)
#define CMDK_AddBugTrappedInFileAndLine(fname, line) ((void) 0)
#define CMDK_AddBugTrappedInIntParam(name, value) ((void) 0)
#endif // CMDK_BUGS_TRAPPING_MODE

#endif // CMDK_BUGSTRAP_H