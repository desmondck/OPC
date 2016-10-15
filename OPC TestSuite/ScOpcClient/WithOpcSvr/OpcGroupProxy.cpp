// OpcGroupProxy.cpp: implementation of the OpcGroupProxy class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpcGroupProxy.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

OpcGroupProxy::OpcGroupProxy( const GroupState& groupState ) 
: m_State(groupState), m_lRef(1), m_dwCBConnection(0), m_lItemVersion(0)
{
	m_pSyncIO	= new OPCSyncIO();
	m_pAsyncIO2	= new OPCAsyncIO2();

	m_pICallback = new OPCCallbackObject();
	m_pICallback->AddRef();
	m_pICallback->SetCallbackObject( this );

	AddRef();
}

OpcGroupProxy::~OpcGroupProxy()
{
	m_pICallback->Release();

	delete m_pAsyncIO2;
	delete m_pSyncIO;
}

void OpcGroupProxy::Attach( IUnknown* pUnknown )
{
	*((IUnknown**)m_GroupStateMgt) = pUnknown;

	HRESULT hr = AtlAdvise( m_GroupStateMgt, m_pICallback->GetUnknown(),IID_IOPCDataCallback, &m_dwCBConnection );

	m_ItemMgt.Attach( m_GroupStateMgt );

	if( !m_pSyncIO->IsOk() )
		m_pSyncIO->Attach( m_GroupStateMgt );
	if( !m_pAsyncIO2->IsOk() )
		m_pAsyncIO2->Attach( m_GroupStateMgt );
}

BOOL OpcGroupProxy::IsOk()
{
	return m_GroupStateMgt.IsOk();
}

HRESULT OpcGroupProxy::AddItems( const ITEM_LIST& items )
{
	if( !m_ItemMgt.IsOk() )
		return E_FAIL;

	DWORD dwCount = items.size();
	OPCITEMDEF* pIDef = new OPCITEMDEF[dwCount];
	{
		CSLock lock(m_CSLock);

		for( int i = 0; i < dwCount; ++i )
		{
			//创建Item对象
			CString strItemName;
			VARTYPE vtDataType;
			_GetItemInfo( items[i], strItemName, vtDataType );
			OpcItem* pItem = new OpcItem( m_State.strGroupName, items[i], strItemName, vtDataType );
			
			//参数构建
			pIDef[i].dwBlobSize		= 0;
			pIDef[i].pBlob			= NULL;
			pIDef[i].bActive		= TRUE;
			pIDef[i].hClient		= pItem->GetClientHandle();
			pIDef[i].szItemID		= CoTaskMemory::Alloc( pItem->GetItemName() );
			pIDef[i].szAccessPath	= NULL;
			pIDef[i].vtRequestedDataType = pItem->GetRequestType();
			
			//添加订阅位号列表
			m_CltItems[ pIDef[i].hClient ] = pItem;
			m_CltNameToItems[ pItem->GetCltName() ] = pItem;
			InterlockedIncrement(&m_lItemVersion);
		}
	}

	//订阅位号
	HRESULT* pErrors = NULL;
	OPCITEMRESULT* pResults = NULL;
	HRESULT hr = m_ItemMgt.AddItems( dwCount, pIDef, &pResults, &pErrors);
	if( SUCCEEDED(hr) )
	{
		CSLock lock(m_CSLock);
		for( int i = 0; i < dwCount; ++i )
		{
			if( pResults[i].pBlob != NULL )
				CoTaskMemFree( pResults[i].pBlob );

			if( SUCCEEDED( pErrors[i] ) )	//添加到成功订阅列表
			{
				OPCHANDLE hClient = pIDef[i].hClient;
				m_CltItems[hClient]->SetServerHandle( pResults[i].hServer );
			}
		}
		
		CoTaskMemFree( pResults );
		CoTaskMemFree( pErrors );
	}

	for( int i = 0; i < dwCount; ++i )
		LocalFree((HLOCAL)pIDef[i].szItemID);
	delete[] pIDef;
	
	return hr;
}
// 
// OpcItem* OpcGroupProxy::FindItem( OPCHANDLE hClient )
// {
// 	HANDLE_ITEMS::iterator it = m_CltItems.find( hClient );
// 	if( it == m_CltItems.end() )
// 		return NULL;
// 
// 	it->second->AddRef();
// 	return it->second;
// }

HRESULT OpcGroupProxy::CreateEnumerator( EnumOPCItemAttributes& enumerator )
{
	return m_ItemMgt.CreateEnumerator( IID_IEnumOPCItemAttributes, enumerator );
}

void OpcGroupProxy::UpdateData( HANDLE hClient, VARIANT& variant, WORD quality, FILETIME time )
{
	CSLock lock(m_CSLock);

	_UpdateData( hClient, variant, quality, time );
}

void OpcGroupProxy::UpdateData( DWORD dwCount, HANDLE* pClientHandles, VARIANT* pValues, WORD* pQualities, FILETIME* pTimes, HRESULT* pErrors )
{
	CSLock lock(m_CSLock);

	for( int i = 0; i < dwCount; ++i )
	{
		if( FAILED(pErrors[i]) )
			continue;

		_UpdateData( pClientHandles[i], pValues[i], pQualities[i], pTimes[i] );
	}
}

void OpcGroupProxy::_UpdateData( HANDLE hClient, VARIANT& variant, WORD quality, FILETIME& time )
{
	if( hClient == NULL )
		return;

	HANDLE_ITEMS::iterator it = m_CltItems.find( (OPCHANDLE)hClient );
	if( it == m_CltItems.end() )
		return;

	OpcItem* pItem = it->second;
	pItem->SetVQT( variant, quality, time );
}

void OpcGroupProxy::GetData( vector<OpcItem*>& items )
{
	CSLock lock(m_CSLock);

	DWORD dwCount = m_CltItems.size();
	if( dwCount == 0 )
		return;
	
	for( HANDLE_ITEMS::iterator it = m_CltItems.begin(); it != m_CltItems.end(); ++it )
	{
		OpcItem* pItem = it->second;

		pItem->AddRef();
		items.push_back( pItem );
	}
}

// OPCSyncIO* OpcGroupProxy::GetSyncIoObject()
// {
// 	if( !m_pSyncIO->IsOk() )
// 		m_pSyncIO->Attach( m_GroupStateMgt );
// 
// 	return m_pSyncIO;
// }
// 
// OPCAsyncIO2* OpcGroupProxy::GetAsyncIo2Object()
// {
// 	if( !m_pAsyncIO2->IsOk() )
// 		m_pAsyncIO2->Attach( m_GroupStateMgt );
// 	
// 	return m_pAsyncIO2;	
// }

BOOL OpcGroupProxy::_GetItemInfo( const CString& strItemInfo, CString& strItemName, VARTYPE& vtDataType )
{
	int indexLeft = strItemInfo.Find( SUB_SEP_LEFT );
	if( indexLeft < 0 )	//无附属信息
	{
		strItemName = strItemInfo;
		vtDataType = VT_EMPTY;

		return TRUE;
	}
	
	//存在附属信息
	int indexRight = strItemInfo.Find( SUB_SEP_RIGHT );
	if( indexLeft <= 0 || indexRight != strItemInfo.GetLength() - 1 )
		return FALSE;

	strItemName = strItemInfo.Left( indexLeft );
	CString strVT = strItemInfo.Mid( indexLeft + 1 );
	strVT.Remove( SUB_SEP_RIGHT );

	return VariantHelper::VarTypeFromString( strVT, vtDataType );
}

///////////////////////OPCSyncIO///////////////////////////////////////////////////
HRESULT OpcGroupProxy::SyncRead( OPCDATASOURCE dwDataSource, const ITEM_LIST& items )
{
	//参数组装
	vector<OPCHANDLE> svrHandleList;
	_GetItemSvrHandles( items, svrHandleList );
	DWORD dwCount = svrHandleList.size();
	if( dwCount == 0 )
		return S_FALSE;

	//读取操作
	OPCITEMSTATE* pItemValues = NULL;
	HRESULT* pErrors = NULL;
	HRESULT hr = m_pSyncIO->Read( dwDataSource, dwCount, &(svrHandleList[0]), &pItemValues, &pErrors );
	if( FAILED(hr) )
		return hr;

	//数据更新
	for( int i = 0; i < dwCount; ++ i)
	{
		if( FAILED( pErrors[i] ) )
			continue;

		OPCITEMSTATE* pItemState = pItemValues + i;
		UpdateData( (HANDLE)pItemState->hClient, pItemState->vDataValue, pItemState->wQuality, pItemState->ftTimeStamp );
		VariantClear( &(pItemState->vDataValue) );
	}
	
	CoTaskMemory::Free( &pItemValues );
	CoTaskMemory::Free( &pErrors );
		
	return hr;	
}

HRESULT OpcGroupProxy::SyncWrite( const VARIANT& vValue, const ITEM_LIST& items )
{
	//参数组装
	vector<OPCHANDLE> svrHandleList;
	_GetItemSvrHandles( items, svrHandleList );
	DWORD dwCount = svrHandleList.size();
	if( dwCount == 0 )
		return S_FALSE;
	vector<VARIANT> dataValueList( dwCount );
	for( int i = 0; i < dwCount; ++i )
		dataValueList[i] = vValue;
	
	TaskLogFile::BeginTrace( TNAME_SYNC_IO_WRITE, m_State.strGroupName );
	DWORD dwStartTicks = GetTickCount();
	/************************************************************************/
	HRESULT* pErrors = NULL;
	HRESULT hr = m_pSyncIO->Write( dwCount, &(svrHandleList[0]), &(dataValueList[0]), &pErrors );
	/************************************************************************/
	DWORD dwSpanTicks = GetTickCount() - dwStartTicks;
	TaskLogFile::TraceSpan( TNAME_SYNC_IO_WRITE, dwSpanTicks );

	if( SUCCEEDED(hr) )
 		CoTaskMemory::Free( &pErrors );	

	return hr;
}

///////////////////////IOPCAsyncIO2///////////////////////////////////////////////////
HRESULT OpcGroupProxy::AsyncRead2( const ITEM_LIST& items )
{
	//参数组装
	vector<OPCHANDLE> svrHandleList;
	_GetItemSvrHandles( items, svrHandleList );
	DWORD dwCount = svrHandleList.size();
	if( dwCount == 0 )
		return S_FALSE;

	DWORD dwCancelID = 0;
	HRESULT* pErrors = NULL;
	HRESULT hr = m_pAsyncIO2->Read( dwCount, &(svrHandleList[0]), 0, &dwCancelID, &pErrors );

	if( SUCCEEDED(hr) )
		CoTaskMemory::Free( &pErrors );

	return hr;
}

HRESULT OpcGroupProxy::AsyncWrite2( const VARIANT& vValue, const ITEM_LIST& items )
{
	//参数组装
	vector<OPCHANDLE> svrHandleList;
	_GetItemSvrHandles( items, svrHandleList );
	DWORD dwCount = svrHandleList.size();
	if( dwCount == 0 )
		return S_FALSE;
	vector<VARIANT> dataValueList( dwCount );
	for( int i = 0; i < dwCount; ++i )
		dataValueList[i] = vValue;
	
	TaskLogFile::BeginTrace( TNAME_ASYNC_IO_WRITE2, m_State.strGroupName );
	DWORD dwStartTicks = GetTickCount();
	/************************************************************************/
	DWORD dwCancelId;
	HRESULT* pErrors = NULL;
	HRESULT hr = m_pAsyncIO2->Write( dwCount, &(svrHandleList[0]), &(dataValueList[0]), 0, &dwCancelId, &pErrors );
	/************************************************************************/
	DWORD dwSpanTicks = GetTickCount() - dwStartTicks;
	TaskLogFile::TraceSpan( TNAME_ASYNC_IO_WRITE2, dwSpanTicks );
	
	if( SUCCEEDED(hr) )
		CoTaskMemory::Free( &pErrors );	
	
	return hr;	
}

void OpcGroupProxy::_GetItemSvrHandles( const ITEM_LIST& items, vector<OPCHANDLE>& svrHandleList )
{
	DWORD dwCount = items.size();
	if( dwCount == 1 && items[0] == SYMBOL_ALL )	//读取全部位号
	{		
		for( HANDLE_ITEMS::iterator it = m_CltItems.begin(); it != m_CltItems.end(); ++it )
			svrHandleList.push_back( it->second->GetServerHandle() );
	}
	else
	{	
		for( int i = 0; i < items.size(); ++i )
		{
			CLTNAME_ITEMS_MAP::iterator it = m_CltNameToItems.find( items[i] );
			if( it == m_CltNameToItems.end() )
			{
				CString strErrMsg;
				strErrMsg.Format( "%s 未订阅，无法读取", items[i] );
				TaskLogFile::TraceError( strErrMsg );
			}
			else
			{
				svrHandleList.push_back( it->second->GetServerHandle() );
			}
		}
	}
}

DWORD OpcGroupProxy::GetItemVersion()
{
	return m_lItemVersion;
}
