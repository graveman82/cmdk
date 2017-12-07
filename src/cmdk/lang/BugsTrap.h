#ifndef CMDK_BUGSTRAP_H
#define CMDK_BUGSTRAP_H

#ifdef CMDK_BUGS_TRAPPING_MODE
// Функция для записи ошибок. В качестве параметра передать строку с описанием ошибки.
void CMDK_AddBugTrappedInDesc(const char* bugDesc);
// Функция для записи файла и строки с ошибкой - при вызове функции передать имя файла и строки.
void CMDK_AddBugTrappedInFileAndLine(const char* fname, int line);
// Функция для записи значений целых параметров - при вызове функции передать имя и значение параметра.
void CMDK_AddBugTrappedInIntParam(const char* name, int value);
#else
#define CMDK_AddBugTrappedInDesc(bugDesc) ((void) 0)
#define CMDK_AddBugTrappedInFileAndLine(fname, line) ((void) 0)
#define CMDK_AddBugTrappedInIntParam(name, value) ((void) 0)
#endif // CMDK_BUGS_TRAPPING_MODE

#endif // CMDK_BUGSTRAP_H