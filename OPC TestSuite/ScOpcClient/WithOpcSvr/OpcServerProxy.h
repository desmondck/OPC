// OpcSvrProxy.h: interface for the OpcSvrProxy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPCSVRPROXY_H__3CBAE142_B362_427D_9FF4_81C42CA42406__INCLUDED_)
#define AFX_OPCSVRPROXY_H__3CBAE142_B362_427D_9FF4_81C42CA42406__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OPCWrap.h"
#include "OpcGroupProxy.h"
#include "ConnectionPoint.h"
#include "OPCSvrHelper.h"

#include <map>
using namespace std;

struct ServerInfo
{
	CString	SvrNode;
	CString SvrName;
	DWORD	ProtocolVer;

	ServerInfo() : ProtocolVer(OPC_PROTOCOL_20), SvrNode("localhost")
	{
	}
};

typedef map<CString, OpcGroupProxy*> ALL_GROUPS;

class OpcServerProxy  
{
public:
	OpcServerProxy( const ServerInfo& svrInfo );
	virtual ~OpcServerProxy();

	void	GetSvrInfo( ServerInfo& svrInfo );

	HRESULT Connect();
	void	Disconnect();

	void	SetShutdownCallback( IShutdownHandler* pShutdownHandler );

	HRESULT	AddGroup( GroupState& groupState );
	void	RemoveGroup( const CString& strGroupName );
	void	GetAllGroups( ALL_GROUPS& allGroups );
	void	GetAllGroupNames( vector<CString>& groupNames );
	OpcGroupProxy* FindGroup( const CString& strGroupName );

	HRESULT GetErrorString( HRESULT dwError, LCID dwLocale, CString& strErrMsg );

	void	GetBrowser( OPCBrowseServerAddressSpace& browser );
    OPCItemProperties*	GetItemPropObject();
private:
	CCriticalSectionLock m_CSLock;
	ServerInfo	m_SvrInfo;

	ALL_GROUPS	m_AllGroups;
private:
	OPCServer	m_OPCServer;
	OPCItemProperties*	m_pItemProp;

	OPCShutdownObject*	m_pIShutdown;
};

#endif // !defined(AFX_OPCSVRPROXY_H__3CBAE142_B362_427D_9FF4_81C42CA42406__INCLUDED_)
