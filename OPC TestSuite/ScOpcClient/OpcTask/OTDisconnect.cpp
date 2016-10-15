// OTDisconnect.cpp: implementation of the OTDisconnect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OTDisconnect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

OTDisconnect::OTDisconnect() : OpcTask( OT_Disconnect, TNAME_DISCONNECT )
{

}

OTDisconnect::~OTDisconnect()
{

}

HRESULT OTDisconnect::DoRun()
{
	if( g_pOpcSvrProxy )
	{
		g_pOpcSvrProxy->Disconnect();
		delete g_pOpcSvrProxy;
		g_pOpcSvrProxy = NULL;
	}
	
	return S_OK;
}

IOpcTask* OTDisconnect::CreateInstance()
{
	return new OTDisconnect();
}

HRESULT OTDisconnect::DoUnserialize( TaskFileReader& taskFileReader )
{
	return TRUE;
}
