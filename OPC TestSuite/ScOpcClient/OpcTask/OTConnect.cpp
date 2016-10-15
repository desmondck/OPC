// OTConnect.cpp: implementation of the OTConnect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OTConnect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

OTConnect::OTConnect() : OpcTask( OT_Connect, TNAME_CONNECT )
{
}

OTConnect::~OTConnect()
{
}

HRESULT OTConnect::DoRun()
{
	if( g_pOpcSvrProxy )
		delete g_pOpcSvrProxy;

	g_pOpcSvrProxy = new OpcServerProxy( m_SvrInfo );
	return g_pOpcSvrProxy->Connect();
}

IOpcTask* OTConnect::CreateInstance()
{
	return new OTConnect();
}

HRESULT OTConnect::DoUnserialize( TaskFileReader& taskFileReader )
{
	OneTaskParam oneParam;
	if( !taskFileReader.ReadParamLine( oneParam ) )
		return E_TASK_INVALID_PARAM;

	if( oneParam.ParamValues.size() != 2 )
		return E_TASK_INVALID_PARAM;

	m_SvrInfo.SvrNode = oneParam.ParamValues[0];
	m_SvrInfo.SvrName = oneParam.ParamValues[1];

	return S_OK;
}
