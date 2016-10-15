// OpcDaDemoSvr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "OpcDaDemoSvr.h"
#include <iostream>
#include <string>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	HWND hConsoleWin = GetConsoleWindow();
	ShowWindow( hConsoleWin, SW_MINIMIZE );

	CoInitializeEx( NULL, COINIT_MULTITHREADED );

	BOOL bAutoClose = FALSE;

	OpcDaDemoSvr svr;
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
			Sleep(5000);
			if( !svr.ServerInUse() )
				break;

			IOpcDaCltInfoList* pCltInfoList = svr.GetClientInfoList();
			if( pCltInfoList )
			{
				DWORD dwClientCount = pCltInfoList->GetClientCount();
				cout << "All Client Numbers: " << dwClientCount << endl;

				for( int i = 0; i < dwClientCount; ++i )
				{
					IOpcDaCltInfo* pClientInfo = pCltInfoList->GetClient( i );
					cout << "\tClient Name: " << pClientInfo->GetName() << endl;
					cout << "\tClient Id:" << pClientInfo->GetId() << endl;

					DWORD dwGroupCount = pClientInfo->GetGroupCount();
					for( int k = 0; k < dwGroupCount; ++k )
					{
						cout << "\t\tGroup Name: " << pClientInfo->GetGroupName(k) 
							 << "\tItem Count: " << pClientInfo->GetItemCount(k) << endl;
					}
				}

				pCltInfoList->Release();
			}
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

