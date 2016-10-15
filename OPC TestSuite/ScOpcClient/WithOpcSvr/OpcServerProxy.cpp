// OpcSvrProxy.cpp: implementation of the OpcSvrProxy class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpcServerProxy.h"
#include "OPCSvrHelper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

OpcServerProxy::OpcServerProxy( const ServerInfo& svrInfo ) : m_SvrInfo(svrInfo)
{
	m_pItemProp = new OPCItemProperties();

	m_pIShutdown = new OPCShutdownObject();
	m_pIShutdown->AddRef();	
}

OpcServerProxy::~OpcServerProxy()
{
	Disconnect();
	m_pIShutdown->Release();
	delete m_pItemProp;
}

void OpcServerProxy::GetSvrInfo( ServerInfo& svrInfo )
{
	svrInfo = m_SvrInfo;
}

HRESULT OpcServerProxy::Connect()
{
	if( m_OPCServer.IsOk() )
		return E_TASK_HAS_CONNECTED;

	return OPCSvrHelper::Connect( m_SvrInfo.SvrNode, m_SvrInfo.SvrName, m_SvrInfo.ProtocolVer, m_OPCServer );
}

void OpcServerProxy::Disconnect()
{
	CSLock lock(m_CSLock);

	for( ALL_GROUPS::iterator it = m_AllGroups.begin(); it != m_AllGroups.end(); ++it )
	{
		OpcGroupProxy* pGroupProxy = it->second;
		GroupState state = pGroupProxy->GetState();

		m_OPCServer.RemoveGroup( state.hServerGroup, TRUE );
		pGroupProxy->Release();
	}
	m_AllGroups.clear();

	if( m_OPCServer.IsOk() )
		m_OPCServer.Detach();
}

HRESULT OpcServerProxy::AddGroup( GroupState& state )
{
	if( !m_OPCServer.IsOk() )
		return E_TASK_SVR_UNSPECIFIED;

	if( m_AllGroups.find( state.strGroupName ) != m_AllGroups.end() )
		return E_TASK_DUPLICATE_NAME;

	//向服务器订阅组
	OpcGroupProxy* pGroupProxy = new OpcGroupProxy( state );
	IUnknown* pUnknown = NULL;
	LPWSTR szName = CoTaskMemory::Alloc( state.strGroupName );
	HRESULT hr = m_OPCServer.AddGroup( szName, state.bActive, state.dwReqUpdateRate, state.hClientGroup, &(state.lTimeBias),
		&(state.fPercentDeadband), state.dwLCID, &(state.hServerGroup), &(state.dwRevUpdateRate), IID_IOPCGroupStateMgt, &pUnknown );
	CoTaskMemory::Free( &szName );
	if( FAILED(hr) )
	{
		pGroupProxy->Release();
		return hr;
	}
	
	CSLock lock(m_CSLock);

	pGroupProxy->Attach( pUnknown );
	m_AllGroups[state.strGroupName] = pGroupProxy;

	return hr;
}

void OpcServerProxy::RemoveGroup( const CString& strGroupName )
{
	CSLock lock(m_CSLock);
 	m_AllGroups.erase( strGroupName );	
}

void OpcServerProxy::GetAllGroupNames( vector<CString>& groupNames )
{
	CSLock lock(m_CSLock);
	for( ALL_GROUPS::iterator it = m_AllGroups.begin(); it != m_AllGroups.end(); ++it )
		groupNames.push_back( it->first );
}

OpcGroupProxy* OpcServerProxy::FindGroup( const CString& strGroupName )
{
	CSLock lock(m_CSLock);

	ALL_GROUPS::iterator it = m_AllGroups.find( strGroupName );
	if( it != m_AllGroups.end() )
	{
		OpcGroupProxy* pGroupProxy = it->second;
		pGroupProxy->AddRef();

		return pGroupProxy;
	}

	CString strLogMsg;
	strLogMsg.Format( "指定组名不存在: %s", strGroupName );
	TaskLogFile::TraceError( strLogMsg );

	return NULL;
}

void OpcServerProxy::GetAllGroups( ALL_GROUPS& allGroups )
{
	CSLock lock(m_CSLock);

	for( ALL_GROUPS::iterator it = m_AllGroups.begin(); it != m_AllGroups.end(); ++it )
	{
		OpcGroupProxy* pGroup = it->second;
		
		pGroup->AddRef();
		allGroups[it->first] = pGroup;
	}
}

void OpcServerProxy::GetBrowser( OPCBrowseServerAddressSpace& browser )
{
	if( m_OPCServer.IsOk() && !browser.IsOk() )
		browser.Attach( m_OPCServer );
}

void OpcServerProxy::SetShutdownCallback( IShutdownHandler* pShutdownHandler )
{
	m_pIShutdown->SetCallbackObject( pShutdownHandler );
}

HRESULT OpcServerProxy::GetErrorString( HRESULT dwError, LCID dwLocale, CString& strErrMsg )
{
	if( !m_OPCServer.IsOk() )
		return E_FAIL;

	LPWSTR pString = NULL;
	HRESULT hr = m_OPCServer.GetErrorString( dwError, dwLocale, &pString );
	if( SUCCEEDED(hr) )
	{
		strErrMsg = pString;
		CoTaskMemFree( pString );
	}

	return hr;
}

OPCItemProperties* OpcServerProxy::GetItemPropObject()
{
	if( !m_pItemProp->IsOk() )
		m_pItemProp->Attach( m_OPCServer );

	return m_pItemProp;
}
