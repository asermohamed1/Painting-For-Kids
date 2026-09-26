#include "ApplicationManager.h"
#include "GUI/Output.h"
#include"random"
using namespace std;

// Debug builds only: every CRT/runtime-check error is also written with its call stack
// (function, file and line) to debug_log.txt, then the normal error dialog is shown
#ifdef _DEBUG
#include <crtdbg.h>
#include <dbghelp.h>
#include <cstdio>
#pragma comment(lib, "dbghelp.lib")
static int __cdecl DebugReportHook(int, char* msg, int*)
{
	FILE* f = fopen("debug_log.txt", "a");
	if (f)
	{
		fprintf(f, "=== %s\n", msg);
		HANDLE proc = GetCurrentProcess();
		static bool symInit = SymInitialize(proc, NULL, TRUE) != FALSE;
		void* frames[40];
		USHORT n = CaptureStackBackTrace(0, 40, frames, NULL);
		char buf[sizeof(SYMBOL_INFO) + 256];
		SYMBOL_INFO* sym = (SYMBOL_INFO*)buf;
		for (USHORT i = 0; i < n; i++)
		{
			sym->SizeOfStruct = sizeof(SYMBOL_INFO);
			sym->MaxNameLen = 255;
			IMAGEHLP_LINE64 line = { sizeof(IMAGEHLP_LINE64) };
			DWORD disp = 0;
			DWORD64 addr = (DWORD64)frames[i];
			const char* name = SymFromAddr(proc, addr, NULL, sym) ? sym->Name : "?";
			if (SymGetLineFromAddr64(proc, addr, &disp, &line))
				fprintf(f, "  %s  (%s:%lu)\n", name, line.FileName, line.LineNumber);
			else
				fprintf(f, "  %s\n", name);
		}
		fclose(f);
	}
	return FALSE; // continue with the normal error handling (dialog)
}
#endif

int main()
 {
#ifdef _DEBUG
	_CrtSetReportHook(DebugReportHook); //log debug errors with their call stack
#endif

	ActionType ActType;
	//Create an object of ApplicationManager
	ApplicationManager AppManager;
	
	do
	{		
		//Read user action
		ActType = AppManager.GetUserAction();

		//Exexute the action
		AppManager.ExecuteAction(ActType);

		//Update the interface
		AppManager.UpdateInterface();	

	} while(!AppManager.IsExitRequested());
	
}

