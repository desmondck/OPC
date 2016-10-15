// OpcGroupProxy.h: interface for the OpcGroupProxy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPCGROUPPROXY_H__86159498_573E_4DEA_9FB6_833635ECEBCB__INCLUDED_)
#define AFX_OPCGROUPPROXY_H__86159498_573E_4DEA_9FB6_833635ECEBCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IUpdateDataHandler.h"
#include "ConnectionPoint.h"
#include "OpcItem.h"

struct GroupState
{
	DWORD	dwReqUpdateRate;
	DWORD	dwRevUpdateRate;
	BOOL	bActive;
	CString	strGroupName;
	LONG	lTimeBias;
	FLOAT	fPercentDeadband;
	DWORD	dwLCID;
	OPCHANDLE	hClientGroup;
	OPCHANDLE	hServerGroup;
	
	GroupState() : dwReqUpdateRate(0), dwRevUpdateRate(0), bActive(TRUE), lTimeBias(0), fPercentDeadband(0.0), dwLCID(0)
		, hClientGroup(NULL), hServerGroup(NULL), strGroupName(_T("ScDefaultGroup"))
	{
		
	}
};

typedef vector<CString> ITEM_LIST;
typedef map< CString, ITEM_LIST > GROUP_ITEMS_MAP;

typedef map<OPCHANDLE, OpcItem*> HANDLE_ITEMS;
typedef map<OpcItem*, OPCHANDLE> ITEM_HANDLES;
typedef map<CString, OpcItem*>	CLTNAME_ITEMS_MAP;

class OpcGroupProxy : public IUpdateDataHandler
{
public:
	OpcGroupProxy( const GroupState& groupState );

	void AddRef() { InterlockedIncrement(&m_lRef); }
	void Release() 
	{ 
		if( InterlockedDecrement(&m_lRef) == 0 )
			delete this;
	}

	void	Attach( IUnknown* pUnknown );
	BOOL	IsOk();
	GroupState GetState() { return m_State; }
	CString	GetName() { return m_State.strGroupName; }

	HRESULT AddItems( const ITEM_LIST& items );
	DWORD	GetItemVersion();
	HRESULT CreateEnumerator( EnumOPCItemAttributes& enumerator );

	OpcItem* FindItem( OPCHANDLE hClient );

	virtual void UpdateData( HANDLE hClient, VARIANT& variant, WORD quality, FILETIME time );
	virtual void UpdateData( DWORD dwCount, HANDLE* pClientHandles, VARIANT* pValues, WORD* pQualities, FILETIME* pTimes, HRESULT* pErrors );

	void	GetData( vector<OpcItem*>& items );

	//OPCSyncIO
	HRESULT SyncRead( OPCDATASOURCE dwDataSource, const ITEM_LIST& items );
	HRESULT SyncWrite( const VARIANT& vValue, const ITEM_LIST& items );

	//AsyncRead2
	HRESULT AsyncRead2( const ITEM_LIST& items );
	HRESULT AsyncWrite2( const VARIANT& vValue, const ITEM_LIST& items );
private:
	virtual ~OpcGroupProxy();

	void _UpdateData( HANDLE hClient, VARIANT& variant, WORD quality, FILETIME& time );
	BOOL _GetItemInfo( const CString& strItemInfo, CString& strItemName, VARTYPE& vtDataType );
	void _GetItemSvrHandles( const ITEM_LIST& items, vector<OPCHANDLE>& svrHandleList );
private:
	GroupState	m_State;

	OPCGroupStateMgt	m_GroupStateMgt;
	OPCItemMgt			m_ItemMgt;

	//下述两个对象在并发上存在问题
	OPCSyncIO*			m_pSyncIO;
	OPCAsyncIO2*		m_pAsyncIO2;

	OPCCallbackObject*	m_pICallback;
	DWORD	m_dwCBConnection;
private:	//Item
	CCriticalSectionLock	m_CSLock;
	HANDLE_ITEMS		m_CltItems;
	CLTNAME_ITEMS_MAP	m_CltNameToItems;

private:
	volatile LONG	m_lRef;
	volatile LONG	m_lItemVersion;
};

#endif // !defined(AFX_OPCGROUPPROXY_H__86159498_573E_4DEA_9FB6_833635ECEBCB__INCLUDED_)
