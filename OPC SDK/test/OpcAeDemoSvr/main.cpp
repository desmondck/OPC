// OpcAeDemoSvr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

#include "OpcAeDemoSvr.h"

int _tmain(int argc, _TCHAR* argv[])
{
	HWND hConsoleWin = GetConsoleWindow();
	ShowWindow( hConsoleWin, SW_MINIMIZE );

	CoInitializeEx( NULL, COINIT_MULTITHREADED );

	BOOL bAutoClose = FALSE;

	OpcAeDemoSvr svr;
	if( argc == 2 )
	{
		_strupr((char*)argv[1]);

		if( strstr((const char*)argv[1], "UNREGSERVER") != NULL )
		{
			svr.UnregServer();
			return 0 ;
		}
		else if( strstr((const char*)argv[1], "REGSERVER") != NULL )
		{
			svr.RegServer();
			return 0;
		}
		else if( strstr((const char*)argv[1], "AUTOMATION") != NULL || strstr((const char*)argv[1], "EMBEDDING") != NULL )
			bAutoClose = TRUE;
	}

	svr.Start();

	if( bAutoClose )
	{
		while(TRUE)
		{
			Sleep(1000);
			if( !svr.ServerInUse() )
				break;
		}
	}
	else
	{
		cout << "Press any key to exit " <<endl;
		getchar();
	}

	svr.Stop();

	CoUninitialize();
	return 0;
}

