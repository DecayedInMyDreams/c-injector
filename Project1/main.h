#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include "config.h"

using namespace std;

DWORD getpid(const char* pn) {
	DWORD Pid = NULL;
	HANDLE hs = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hs != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(pe);

		if (Process32First(hs, &pe))
		{
			do {
				if (!_stricmp(pe.szExeFile, pn))
				{
					Pid = pe.th32ProcessID;
					break;
				}
			} while (Process32Next(hs, &pe));
		}
	}
	CloseHandle(hs);
	return Pid;
}