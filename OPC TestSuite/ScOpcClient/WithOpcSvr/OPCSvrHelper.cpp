// OPCSvrHelper.cpp: implementation of the OPCSvrHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OPCSvrHelper.h"
#define __GUID_DEFINED__
#include "opcda_cats.c"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

HRESULT OPCSvrHelper::EnumOpcServers( const CString& strSvrAddr, const CString& protocolVer, vector<OPCServerInfo>& opcSvrList )
{
	USES_CONVERSION;
	
	//参数准备
	CATID catID = CATID_OPCDAServer20;
	if( protocolVer == OPC_PROTOCOL_10 )
		catID = CATID_OPCDAServer10;

	const CLSID CLSID_OPCServerList = {0x13486D51,0x4821,0x11D2,{0xA4,0x94,0x3C,0xB3,0x06,0xC1,0x00,0x00}};
	
	COSERVERINFO si;	
	si.dwReserved1 = 0;
	si.pwszName = NULL;
	if( !strSvrAddr.IsEmpty() )
		si.pwszName = T2OLE(strSvrAddr);
	si.pAuthInfo = NULL;
	si.dwReserved2 = 0;
	
	MULTI_QI  qi;
	qi.pIID = &IID_IOPCServerList;
	qi.pItf = NULL;
	qi.hr = 0;
	
	//获取枚举接口
	HRESULT hr = CoCreateInstanceEx( CLSID_OPCServerList, NULL, CLSCTX_ALL, &si, 1, &qi );
	if( FAILED(hr) )
		return hr;
	if( FAILED(qi.hr) )
		return qi.hr;
	
	IOPCServerList* pServers = (IOPCServerList*)qi.pItf;
	
	IEnumGUID *pEnumGUID=NULL;
	hr = pServers->EnumClassesOfCategories( 1, &catID, 1, &catID, &pEnumGUID );
	if( SUCCEEDED(hr) )
	{
		const DWORD NEXT_COUNT = 100;
		
		unsigned long count;
		CLSID clsid[NEXT_COUNT];
		
		do
		{
			hr = pEnumGUID->Next( NEXT_COUNT, clsid, &count );
			for( ULONG index=0; index < count; index++ )
			{
				LPOLESTR pszProgID;
				LPOLESTR pszUserType;
				HRESULT hr2 = pServers->GetClassDetails(clsid[index], &pszProgID, &pszUserType);
				if( SUCCEEDED(hr2) )
				{
					opcSvrList.push_back( OPCServerInfo(pszProgID, pszUserType, clsid[index]) );
					
					CoTaskMemFree(pszProgID);
					CoTaskMemFree(pszUserType);
				}
			}
		} while( hr == S_OK );
		
		pEnumGUID->Release();
		pServers->Release();
		
		return hr;
	}
	
	pServers->Release();
	return hr;	
}

HRESULT OPCSvrHelper::Connect( const CString& strSvrAddr, const CString& strSvrName, const CString& strProtVer, OPCServer& opcServer )
{
	if( opcServer.IsOk() )
		return E_FAIL;

	CLSID clsID;
	if( !_FindSvrClsID( strSvrAddr, strSvrName, strProtVer, clsID ) )
		return E_FAIL;
	
	HRESULT hr = S_OK;
	LPUNKNOWN pUnkn = NULL;
	if( _IsLocalServer(strSvrAddr) )
	{
		hr = CoCreateInstance( clsID, NULL, CLSCTX_ALL, IID_IUnknown, (LPVOID *)&pUnkn );
		if( FAILED(hr) || pUnkn == NULL)
			return E_TASK_CONN_FAILED;
	}
	else  // 远程
	{
		USES_CONVERSION;
		
		COSERVERINFO si;
		MULTI_QI  qi;
		ZeroMemory( &si, sizeof(COSERVERINFO) );
		ZeroMemory( &qi, sizeof(MULTI_QI) );
		
		si.pwszName = T2OLE( strSvrAddr );
		qi.pIID = &IID_IOPCServer;
		
		hr = CoCreateInstanceEx( clsID, NULL, CLSCTX_REMOTE_SERVER, &si, 1, &qi );
		if( FAILED( hr ) || FAILED( qi.hr ) || qi.pItf == NULL )
			return E_TASK_CONN_FAILED;
		
		pUnkn = qi.pItf;
	}
	
	hr = opcServer.Attach( pUnkn );
	pUnkn->Release();  
	if( FAILED(hr) )
		return E_TASK_REG_PROXY;
	
	return S_OK;	
}

BOOL OPCSvrHelper::_IsLocalServer( const CString& strSvrAddr )
{
	if ( strSvrAddr.IsEmpty() || (_tcsicmp( _T(""), strSvrAddr )==0)
		|| (_tcsicmp( _T("127.0.0.1"), strSvrAddr ) == 0 ) || (_tcsicmp( _T("localhost"), strSvrAddr ) == 0 ) )
	{
		return TRUE;
	}
	
	TCHAR szLocalHost[MAX_COMPUTERNAME_LENGTH + 1]; // 本机名
	DWORD dwHostSize = sizeof(szLocalHost);
	if( GetComputerName( szLocalHost, &dwHostSize ) == TRUE 
		&& _tcsicmp( szLocalHost, strSvrAddr ) == 0 )
	{
		return TRUE;
	}	
	
	return FALSE;
}

BOOL OPCSvrHelper::_FindSvrClsID( const CString& strSvrAddr, const CString& strSvrName, const CString& strProtVer, CLSID& clsID )
{
	vector<OPCServerInfo> opcSvrList;
	EnumOpcServers( strSvrAddr, strProtVer, opcSvrList );

	for( int i = 0; i < opcSvrList.size(); ++i )
	{
		if( opcSvrList[i].Name == strSvrName )
		{
			clsID = opcSvrList[i].ClsID;
			return TRUE;
		}
	}

	return FALSE;
}
