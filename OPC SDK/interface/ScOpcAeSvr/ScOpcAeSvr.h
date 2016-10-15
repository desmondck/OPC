// ScOpcAeSvr.h: interface for the ScOpcAeSvr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCOPCAESVR_H__F5C9EA70_E089_4279_B199_2BC4FC0CCA0E__INCLUDED_)
#define AFX_SCOPCAESVR_H__F5C9EA70_E089_4279_B199_2BC4FC0CCA0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _ScOpcAeSvr_Imp_
	#define SC_OPC_AE_CLASS __declspec(dllexport)
#else
	#define SC_OPC_AE_CLASS __declspec(dllimport)
#endif

#include "opc_ae.h"
#include "opcaedef.h"
#include "IOpcAreaNode.h"
#include "OpcCondition.h"
#include "OpcEventCategory.h"
#include "IOpcEvent.h"
#include "OpcAeObjFactory.h"

interface IOpcAeCallback
{
	virtual const IOpcAreaNode* GetBrowser( DWORD& dwVersion, TCHAR& cSeparator ) = 0;

	//参见IOPCEventServer:: CreateEventSubscription
	virtual DWORD ReviseMaxSize( DWORD dwMaxSize ) const = 0;
	virtual DWORD ReviseBufTime( DWORD dwBufferTime ) const = 0;

	//OPC客户端执行报警确认
	virtual HRESULT ClientAlarmAck( DWORD dwCount, IOpcConditionEvent** ppEvents, LPCTSTR pszAckId, LPCTSTR pszComment, HRESULT* pErrors ) = 0;
};

class SC_OPC_AE_CLASS ScOpcAeSvr
{
public:
	ScOpcAeSvr();
	~ScOpcAeSvr();
	
	void SetProductInfo( LPCTSTR strVendor, WORD wMajorVersion, WORD wMinorVersion, WORD wBuildNumber );
	void SetState( OPCEVENTSERVERSTATE dwServerState );

	//准备工作
	void SetMaxClient( DWORD dwMaxCltCount );		//支持最大客户端的连接个数, 0表示无限制
	void SetMaxEventCount( DWORD dwMaxEventCount );	//推送报警/事件上限，0表示无限制
	void SetReportable( BOOL bReportable );
	void SetCallback( IOpcAeCallback* pCallback );

	//Category
	void AddCategory( DWORD dwCategoryId, const OpcEventCategory& category );
	void RemoveCategory( DWORD dwCategoryId );
	void RemoveAllCategory();

	//服务器启动/停止
	BOOL StartServer( HINSTANCE hInstance, CLSID* pCLSID );
	BOOL StopServer();
	FILETIME GetStartTime();
	
	//服务器注册/反注册
	HRESULT RegisterServer();
	HRESULT UnregisterServer();
	
	//服务器使用状态
	DWORD ServerInUse();

	HRESULT ReportEvent( IOpcSimpleEvent* pEvent );

	IOpcConditionEvent*	FindEvent( DWORD dwAreaDepth, DWORD* pdwAreaIds, LPCTSTR strSource, LPCTSTR strCondName );
	
	void RemoveEvent( DWORD dwAreaDepth, DWORD* pdwAreaIds, LPCTSTR strSource, LPCTSTR strCondName );
	void RemoveEvents( DWORD dwAreaDepth, DWORD* pdwAreaIds, LPCTSTR strSource );

	void RemoveAllEvents();
private:
	void*	m_pData;
};

#endif // !defined(AFX_SCOPCAESVR_H__F5C9EA70_E089_4279_B199_2BC4FC0CCA0E__INCLUDED_)
