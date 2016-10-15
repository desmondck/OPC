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

	//�μ�IOPCEventServer:: CreateEventSubscription
	virtual DWORD ReviseMaxSize( DWORD dwMaxSize ) const = 0;
	virtual DWORD ReviseBufTime( DWORD dwBufferTime ) const = 0;

	//OPC�ͻ���ִ�б���ȷ��
	virtual HRESULT ClientAlarmAck( DWORD dwCount, IOpcConditionEvent** ppEvents, LPCTSTR pszAckId, LPCTSTR pszComment, HRESULT* pErrors ) = 0;
};

class SC_OPC_AE_CLASS ScOpcAeSvr
{
public:
	ScOpcAeSvr();
	~ScOpcAeSvr();
	
	void SetProductInfo( LPCTSTR strVendor, WORD wMajorVersion, WORD wMinorVersion, WORD wBuildNumber );
	void SetState( OPCEVENTSERVERSTATE dwServerState );

	//׼������
	void SetMaxClient( DWORD dwMaxCltCount );		//֧�����ͻ��˵����Ӹ���, 0��ʾ������
	void SetMaxEventCount( DWORD dwMaxEventCount );	//���ͱ���/�¼����ޣ�0��ʾ������
	void SetReportable( BOOL bReportable );
	void SetCallback( IOpcAeCallback* pCallback );

	//Category
	void AddCategory( DWORD dwCategoryId, const OpcEventCategory& category );
	void RemoveCategory( DWORD dwCategoryId );
	void RemoveAllCategory();

	//����������/ֹͣ
	BOOL StartServer( HINSTANCE hInstance, CLSID* pCLSID );
	BOOL StopServer();
	FILETIME GetStartTime();
	
	//������ע��/��ע��
	HRESULT RegisterServer();
	HRESULT UnregisterServer();
	
	//������ʹ��״̬
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
