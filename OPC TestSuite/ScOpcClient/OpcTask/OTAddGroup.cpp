// OTAddGroup.cpp: implementation of the OTAddGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OTAddGroup.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

OTAddGroup::OTAddGroup() : OpcTask( OT_AddGroup, _T("添加组") )
{

}

OTAddGroup::~OTAddGroup()
{

}

HRESULT OTAddGroup::DoRun()
{
	for( int i = 0; i < m_Groups.size(); ++i )
	{
		HRESULT hr = g_pOpcSvrProxy->AddGroup( m_Groups[i] );
		if( FAILED(hr) )
			return hr;
	}

	return S_OK;
}

IOpcTask* OTAddGroup::CreateInstance()
{
	return new OTAddGroup();
}

HRESULT OTAddGroup::DoUnserialize( TaskFileReader& taskFileReader )
{
	//至少需包含一个组信息
	OneTaskParam oneParam;
	while( taskFileReader.ReadParamLine( oneParam ) )
	{
		if( oneParam.ParamValues.size() != 4 )
			return E_TASK_INVALID_PARAM;
		
		GroupState groupState;
		groupState.strGroupName		= oneParam.ParamValues[0];		//组名
		groupState.bActive			= atoi(oneParam.ParamValues[1]);//激活状态
		groupState.dwReqUpdateRate	= atoi(oneParam.ParamValues[2]);//刷新周期
		groupState.fPercentDeadband = atof(oneParam.ParamValues[3]);//死区
		
		m_Groups.push_back( groupState );
	}
	
	if( m_Groups.size() == 0 )
		return E_TASK_INVALID_PARAM;

	return S_OK;
}
