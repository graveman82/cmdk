#include <io.h>
#include <stdio.h>
#include <string.h>

//-----------------------------------------------------------------------------

#ifdef CMDK_BUGS_TRAPPING_MODE
void CMDK_AddBugTrappedInDesc(const char* bugDesc)
{
	const char* fname = "BugsTrappedInCMDK.txt";
	const char* fmode = 0;
	if (access(fname, 0) == 0)
		fmode = "a";
	else 
		fmode = "w";
	FILE* fp = fopen(fname, fmode);
	if (fp == 0) return;
	fputs(bugDesc, fp);
	fclose(fp);
}

void CMDK_AddBugTrappedInFileAndLine(const char* fname, int line)
{
	static char buf[272];
	sprintf(buf, "%s(%d)\n", fname, line);
	CMDK_AddBugTrappedInDesc(buf);
}

void CMDK_AddBugTrappedInIntParam(const char* name, int value)
{
	static char buf[32];
	sprintf(buf, "  %s: %d;\n", name, value);
	CMDK_AddBugTrappedInDesc(buf);
}

#endif // CMDK_BUGS_TRAPPING_MODE

