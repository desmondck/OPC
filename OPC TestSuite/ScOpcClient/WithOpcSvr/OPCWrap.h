//**************************************************************************
//
//  Copyright (c) FactorySoft, INC. 1996-1998, All Rights Reserved
//
//**************************************************************************
//
//  Filename   :  OPCWrap.h
//  $Author    :  Jim Hansen
//
//  Subsystem  :  FactorySoft OPC Client
//
//  Description:  Template wrapper classes for the OPC COM interfaces
//                These classes automatically QueryInterface, AddRef, and
//                Release when they are done, reducing reference count errors.
//
//**************************************************************************

#ifndef __OPCWRAP_H__               // Only Include Once
#define __OPCWRAP_H__

#include "opcda.h"
#include "opccomn.h"

#ifdef _DEBUG
#define TRACE_MSG(call, hr)  { \
	TRACE(_T("hr=%lx\n"), (hr));  \
	TCHAR msg[MAX_PATH*5]; \
	FormatMessage( FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM, \
	NULL, \
	GetScode( hr ), \
	MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), \
	msg, MAX_PATH, NULL ); \
	TRACE(msg); \
	TRACE(_T("\n")); \
	::MessageBox( 0, msg, call, MB_OK ); \
      }
#else
#define TRACE_MSG(call,hr)  ;   // an empty statement
#endif


//*******************************************************************
template <class T, const IID* pIID>
class OInterfaceWrap
{
public:
    OInterfaceWrap() : m_pI(NULL) {}
    ~OInterfaceWrap() { Detach(); }
	
    operator T*() {return m_pI;}
    operator IUnknown*() {return (IUnknown*)m_pI;}
    operator IUnknown**() {return (IUnknown**)&m_pI;}
    operator LPVOID *() {return (LPVOID *)&m_pI;}
	
    HRESULT Attach(IUnknown* pUnk)
	{
		ASSERT( pUnk != NULL );
		if( m_pI == pUnk)
			return S_OK;
		Detach();
		HRESULT hr = pUnk->QueryInterface( *pIID, (LPVOID*)&m_pI);
		//                if( FAILED(hr) )
		//                    TRACE_MSG(_T("QueryInterface"),hr);
		return hr;
	}
	
    HRESULT Attach(T* pI)
	{
		ASSERT( pI != NULL );
		if( m_pI == pI)
			return S_OK;
		Detach();
		m_pI = pI;
		m_pI->AddRef();
		return S_OK;
	}
	
    void Detach()
	{
		if( m_pI )
			m_pI->Release();
		m_pI = NULL;
	}
	
    HRESULT QueryInterface(REFIID iid, void ** ppvObject)
	{
		if( m_pI )
			return m_pI->QueryInterface(iid, ppvObject);
		return E_FAIL;
	}
	
    BOOL IsOk() const {return (m_pI != NULL); }
	
protected:
    T* m_pI;
};

//*******************************************************************
//  Server Interfaces
//*******************************************************************
typedef OInterfaceWrap<IOPCServer, &IID_IOPCServer> IOPCServerWrap;

class OPCServer : public IOPCServerWrap
{
public:
    OPCServer() {}
	
    HRESULT AddGroup(
		LPCWSTR     szName,
		BOOL        bActive,
		DWORD       dwRequestedUpdateRate,
		OPCHANDLE   hClientGroup,
		LONG      * pTimeBias,
		FLOAT     * pPercentDeadband,
		DWORD       dwLCID,
		OPCHANDLE * phServerGroup,
		DWORD     * pRevisedUpdateRate,
		REFIID      riid,
		LPUNKNOWN * ppUnk)
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->AddGroup(szName, bActive, dwRequestedUpdateRate,
			hClientGroup, pTimeBias, pPercentDeadband,
			dwLCID, phServerGroup, pRevisedUpdateRate,
			riid, ppUnk );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCServer::AddGroup"),hr);
        return hr; }
	
    HRESULT GetErrorString(
		HRESULT     dwError,
		LCID     dwLocale,
		LPWSTR     *   ppString)
	{ //ASSERT( IsOk() );
        HRESULT hr = m_pI->GetErrorString( dwError, dwLocale, ppString );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCServer::GetErrorString"),hr);
        return hr; }
	
    HRESULT GetGroupByName(
		LPCWSTR     szName,
		REFIID      riid,
		LPUNKNOWN * ppUnk)
	{ //ASSERT( IsOk() );
        HRESULT hr = m_pI->GetGroupByName( szName, riid, ppUnk );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCServer::GetGroupByName"),hr);
        return hr; }
	
    HRESULT GetStatus(OPCSERVERSTATUS **ppServerStatus)
	{ //ASSERT( IsOk() );
        HRESULT hr = m_pI->GetStatus( ppServerStatus );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCServer::GetStatus"),hr);
        return hr; }
	
    HRESULT RemoveGroup(
		OPCHANDLE   hServerGroup,
		BOOL     bForce)
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->RemoveGroup( hServerGroup, bForce );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCServer::RemoveGroup"),hr);
        return hr; }
	
    HRESULT CreateGroupEnumerator(
		OPCENUMSCOPE dwScope,
		REFIID      riid,
		LPUNKNOWN * ppUnk)
	{ //ASSERT( IsOk() );
        HRESULT hr = m_pI->CreateGroupEnumerator( dwScope, riid, ppUnk );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCServer::CreateGroupEnumerator"),hr);
        return hr; }
};

//*******************************************************************
typedef OInterfaceWrap<IOPCItemProperties,
&IID_IOPCItemProperties> IOPCItemPropertiesWrap;

class OPCItemProperties : public IOPCItemPropertiesWrap
{
public:
    OPCItemProperties() {}
	
    HRESULT QueryAvailableProperties(
		LPWSTR szItemID,
		DWORD *pdwCount,
		DWORD **ppPropertyIDs,
		LPWSTR **ppDescriptions,
		VARTYPE **ppvtDataTypes)
	{ //ASSERT( IsOk() );
        HRESULT hr = m_pI->QueryAvailableProperties( szItemID,
			pdwCount, ppPropertyIDs, ppDescriptions, ppvtDataTypes );
        if( FAILED( hr ) )
            TRACE_MSG(_T("OPCItemProperties::QueryAvailableProperties"),hr);
        return hr; }
	
    HRESULT GetItemProperties(
		LPWSTR szItemID,
		DWORD dwCount,
		DWORD *pdwPropertyIDs,
		VARIANT **ppvData,
		HRESULT **ppErrors)
	{ //ASSERT( IsOk() );
        HRESULT hr = m_pI->GetItemProperties( szItemID,
			dwCount, pdwPropertyIDs, ppvData, ppErrors );
        if( FAILED( hr ) )
            TRACE_MSG(_T("OPCItemProperties::QueryAvailableProperties"),hr);
        return hr; }
	
    HRESULT LookupItemIDs(
		LPWSTR szItemID,
		DWORD dwCount,
		DWORD *pdwPropertyIDs,
		LPWSTR **ppszNewItemIDs,
		HRESULT **ppErrors)
	{ //ASSERT( IsOk() );
        HRESULT hr = m_pI->LookupItemIDs( szItemID,
			dwCount, pdwPropertyIDs, ppszNewItemIDs, ppErrors );
        if( FAILED( hr ) )
            TRACE_MSG(_T("OPCItemProperties::QueryAvailableProperties"),hr);
        return hr; }
};

//*******************************************************************
typedef OInterfaceWrap<IOPCServerPublicGroups,
&IID_IOPCServerPublicGroups> IOPCServerPublicGroupsWrap;

class OPCServerPublicGroups : public IOPCServerPublicGroupsWrap
{
public:
    OPCServerPublicGroups() {}
	// not yet implemented
};

//*******************************************************************
typedef OInterfaceWrap<IOPCBrowseServerAddressSpace,
&IID_IOPCBrowseServerAddressSpace> IOPCBrowseServerAddressSpaceWrap;

class OPCBrowseServerAddressSpace : public IOPCBrowseServerAddressSpaceWrap
{
public:
    OPCBrowseServerAddressSpace() {}
	
	HRESULT QueryOrganization( OPCNAMESPACETYPE * pNameSpaceType)
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->QueryOrganization( pNameSpaceType );
        if( FAILED( hr ) )
            TRACE_MSG(_T("Browse::QueryOrganization"),hr);
        return hr; }
	
	HRESULT ChangeBrowsePosition(
		OPCBROWSEDIRECTION dwBrowseDirection,
		LPCWSTR           szString)
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->ChangeBrowsePosition( dwBrowseDirection, szString );
		//        if( FAILED( hr ) )  // error means can't go farther, etc.
		//            TRACE_MSG(_T("Browse::ChangeBrowsePosition"),hr);
        return hr; }
	
	HRESULT BrowseOPCItemIDs(
		OPCBROWSETYPE     dwBrowseFilterType,
		LPCWSTR           szFilterCriteria,
		VARTYPE           vtDataTypeFilter,
		DWORD             dwAccessRightsFilter,
		LPENUMSTRING *    ppIEnumString)
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->BrowseOPCItemIDs( dwBrowseFilterType, szFilterCriteria,
			vtDataTypeFilter, dwAccessRightsFilter, ppIEnumString );
        if( FAILED( hr ) )
            TRACE_MSG(_T("Browse::BrowseOPCItemIDs"),hr);
        return hr; }
	
	HRESULT GetItemID(LPWSTR   szItemDataID,
		LPWSTR * szItemID)
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->GetItemID( szItemDataID, szItemID );
        if( FAILED( hr ) )
            TRACE_MSG(_T("Browse::GetItemID"),hr);
        return hr; }
	
	HRESULT BrowseAccessPaths( LPCWSTR        szItemID,
		LPENUMSTRING * ppIEnumString)
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->BrowseAccessPaths( szItemID, ppIEnumString );
        if( FAILED( hr ) )
            TRACE_MSG(_T("Browse::BrowseAccessPaths"),hr);
        return hr; }
};

//*******************************************************************
//    Group Interfaces
//*******************************************************************
typedef OInterfaceWrap<IOPCGroupStateMgt,
&IID_IOPCGroupStateMgt> IOPCGroupStateMgtWrap;

class OPCGroupStateMgt : public IOPCGroupStateMgtWrap
{
public:
    OPCGroupStateMgt() {}
	
	HRESULT GetState( DWORD     * pUpdateRate,
		BOOL      * pActive,
		LPWSTR    * ppName,
		LONG      * pTimeBias,
		FLOAT     * pPercentDeadband,
		DWORD     * pLCID,
		OPCHANDLE * phClientGroup,
		OPCHANDLE * phServerGroup )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->GetState( pUpdateRate, pActive, ppName, pTimeBias,
			pPercentDeadband, pLCID, phClientGroup, phServerGroup );
        if( FAILED( hr ) )
            TRACE_MSG(_T("OPCGroupStateMgt::GetState"),hr);
        return hr; }
	
	HRESULT SetState( DWORD     * pRequestedUpdateRate,
		DWORD     * pRevisedUpdateRate,
		BOOL      * pActive,
		LONG      * pTimeBias,
		FLOAT     * pPercentDeadband,
		DWORD     * pLCID,
		OPCHANDLE * phClientGroup )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->SetState( pRequestedUpdateRate, pRevisedUpdateRate, pActive,
			pTimeBias, pPercentDeadband, pLCID, phClientGroup );
        if( FAILED( hr ) )
            TRACE_MSG(_T("OPCGroupStateMgt::SetState"),hr);
        return hr; }
	
	HRESULT SetName( LPCWSTR szName )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->SetName( szName );
        if( FAILED( hr ) )
            TRACE_MSG(_T("OPCGroupStateMgt::SetName"),hr);
        return hr; }
	
	HRESULT CloneGroup(LPCWSTR     szName,
		REFIID      riid,
		LPUNKNOWN * ppUnk )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->CloneGroup( szName, riid, ppUnk );
        if( FAILED( hr ) )
            TRACE_MSG(_T("OPCGroupStateMgt::CloneGroup"),hr);
        return hr; }
};

//*******************************************************************
typedef OInterfaceWrap<IOPCPublicGroupStateMgt,
&IID_IOPCPublicGroupStateMgt> IOPCPublicGroupStateMgtWrap;

class OPCPublicGroupStateMgt : public IOPCPublicGroupStateMgtWrap
{
public:
	OPCPublicGroupStateMgt() {}
	
	HRESULT GetState( BOOL * pPublic )
	{ //ASSERT( IsOk() );
        HRESULT hr = m_pI->GetState( pPublic );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCPublicGroupStateMgt::GetState"),hr);
        return hr; }
	
	HRESULT MoveToPublic( void )
	{ //ASSERT( IsOk() );
        HRESULT hr = m_pI->MoveToPublic( );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCPublicGroupStateMgt::MoveToPublic"),hr);
        return hr; }
	
};

//*******************************************************************
typedef OInterfaceWrap<IOPCSyncIO, &IID_IOPCSyncIO> IOPCSyncIOWrap;

class OPCSyncIO : public IOPCSyncIOWrap
{
public:
    OPCSyncIO() {}
	
	HRESULT Read(  OPCDATASOURCE   dwSource,
		DWORD           dwNumItems,
		OPCHANDLE     * phServer,
		OPCITEMSTATE ** ppItemValues,
		HRESULT      ** ppErrors )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->Read(dwSource, dwNumItems, phServer, ppItemValues, ppErrors );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCSyncIO::Read"),hr);
        return hr; }
	
	HRESULT Write( DWORD        dwNumItems,
		OPCHANDLE  * phServer,
		VARIANT    * pItemValues,
		HRESULT   ** ppErrors )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->Write(dwNumItems, phServer, pItemValues, ppErrors );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCSyncIO::Write"),hr);
        return hr; }
	
};

//*******************************************************************
typedef OInterfaceWrap<IOPCAsyncIO, &IID_IOPCAsyncIO> IOPCAsyncIOWrap;

class OPCAsyncIO : public IOPCAsyncIOWrap
{
public:
    OPCAsyncIO() {}
	
	HRESULT Read(  DWORD           dwConnection,
		OPCDATASOURCE   dwSource,
		DWORD           dwNumItems,
		OPCHANDLE     * phServer,
		DWORD         * pTransactionID,
		HRESULT      ** ppErrors )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->Read( dwConnection, dwSource, dwNumItems, phServer,
			pTransactionID, ppErrors );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCAsyncIO::Read"),hr);
        return hr; }
	
	HRESULT Write( DWORD       dwConnection,
		DWORD       dwNumItems,
		OPCHANDLE * phServer,
		VARIANT   * pItemValues,
		DWORD     * pTransactionID,
		HRESULT ** ppErrors )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->Write( dwConnection, dwNumItems, phServer, pItemValues,
			pTransactionID, ppErrors );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCAsyncIO::Write"),hr);
        return hr; }
	
	HRESULT Refresh(DWORD           dwConnection,
		OPCDATASOURCE   dwSource,
		DWORD         * pTransactionID )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->Refresh(dwConnection, dwSource, pTransactionID );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCAsyncIO::Refresh"),hr);
        return hr; }
	
	HRESULT Cancel( DWORD dwTransactionID )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->Cancel( dwTransactionID );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCAsyncIO::Cancel"),hr);
        return hr; }
	
};

//*******************************************************************
typedef OInterfaceWrap<IOPCAsyncIO2, &IID_IOPCAsyncIO2> IOPCAsyncIO2Wrap;

class OPCAsyncIO2 : public IOPCAsyncIO2Wrap
{
public:
    OPCAsyncIO2() {}
	
	HRESULT Read(  DWORD           dwNumItems,
		OPCHANDLE     * phServer,
		DWORD           pTransactionID,
		DWORD         * pCancelID,
		HRESULT      ** ppErrors )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->Read( dwNumItems, phServer,
			pTransactionID, pCancelID, ppErrors );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCAsyncIO2::Read"),hr);
        return hr; }
	
	HRESULT Write( DWORD       dwNumItems,
		OPCHANDLE * phServer,
		VARIANT   * pItemValues,
		DWORD       pTransactionID,
		DWORD     * pCancelID,
		HRESULT  ** ppErrors )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->Write( dwNumItems, phServer, pItemValues,
			pTransactionID, pCancelID, ppErrors );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCAsyncIO2::Write"),hr);
        return hr; }
	
	HRESULT Refresh2(OPCDATASOURCE   dwSource,
		DWORD           pTransactionID,
		DWORD         * pCancelID )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->Refresh2(dwSource, pTransactionID, pCancelID );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCAsyncIO2::Refresh2"),hr);
        return hr; }
	
	HRESULT Cancel2( DWORD dwCancelID )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->Cancel2( dwCancelID );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCAsyncIO2::Cancel2"),hr);
        return hr; }
	
	HRESULT SetEnable( BOOL bEnable )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->SetEnable( bEnable );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCAsyncIO2::SetEnable"),hr);
        return hr; }
	
	HRESULT GetEnable( BOOL *pbEnable )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->GetEnable( pbEnable );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCAsyncIO2::GetEnable"),hr);
        return hr; }
	
};

//*******************************************************************
typedef OInterfaceWrap<IOPCItemMgt, &IID_IOPCItemMgt> IOPCItemMgtWrap;

class OPCItemMgt : public IOPCItemMgtWrap
{
public:
    OPCItemMgt() {}
	
	HRESULT AddItems(
		DWORD            dwNumItems,
		OPCITEMDEF     * pItemArray,
		OPCITEMRESULT ** ppAddResults,
		HRESULT       ** ppErrors )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->AddItems(dwNumItems, pItemArray, ppAddResults, ppErrors);
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCItemMgt::AddItems"),hr);
        return hr; }
	
	
	HRESULT ValidateItems(
		DWORD             dwNumItems,
		OPCITEMDEF      * pItemArray,
		BOOL              bBlobUpdate,
		OPCITEMRESULT  ** ppValidationResults,
		HRESULT        ** ppErrors )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->ValidateItems(dwNumItems, pItemArray,
			bBlobUpdate, ppValidationResults, ppErrors);
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCItemMgt::ValidateItems"),hr);
        return hr; }
	
	
	HRESULT RemoveItems(
		DWORD        dwNumItems,
		OPCHANDLE  * phServer,
		HRESULT   ** ppErrors )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->RemoveItems(dwNumItems, phServer, ppErrors);
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCItemMgt::RemoveItems"),hr);
        return hr; }
	
	
	HRESULT SetActiveState(
		DWORD        dwNumItems,
		OPCHANDLE  * phServer,
		BOOL         bActive,
		HRESULT   ** ppErrors )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->SetActiveState(dwNumItems, phServer, bActive, ppErrors);
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCItemMgt::SetActiveState"),hr);
        return hr; }
	
	
	HRESULT SetClientHandles(
		DWORD        dwNumItems,
		OPCHANDLE  * phServer,
		OPCHANDLE  * phClient,
		HRESULT   ** ppErrors )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->SetClientHandles(dwNumItems, phServer, phClient, ppErrors );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCItemMgt::SetClientHandles"),hr);
        return hr; }
	
	
	HRESULT SetDatatypes(
		DWORD        dwNumItems,
		OPCHANDLE  * phServer,
		VARTYPE    * pRequestedDatatypes,
		HRESULT   ** ppErrors )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->SetDatatypes(dwNumItems, phServer, pRequestedDatatypes, ppErrors);
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCItemMgt::SetDatatypes"),hr);
        return hr; }
	
	
	HRESULT CreateEnumerator(REFIID riid, LPUNKNOWN * ppUnk )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->CreateEnumerator(riid, ppUnk);
        if( FAILED( hr ) )
            TRACE_MSG(_T("IOPCItemMgt::CreateEnumerator"),hr);
        return hr; }
};

//*******************************************************************
typedef OInterfaceWrap<IDataObject, &IID_IDataObject> IDataObjectWrap;

class DataObject : public IDataObjectWrap
{
public:
    DataObject() {}
	
	HRESULT DAdvise ( FORMATETC* pformatetc,
		DWORD advf,
		IAdviseSink* pAdvSink,
		DWORD* pdwConnection)
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->DAdvise(pformatetc, advf, pAdvSink, pdwConnection );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IDataObject::DAdvise"),hr);
        return hr; }
	
	HRESULT DUnadvise ( DWORD dwConnection)
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->DUnadvise(dwConnection);
        if( FAILED( hr ) )
            TRACE_MSG(_T("IDataObject::DUnadvise"),hr);
        return hr; }
	
	HRESULT EnumDAdvise ( IEnumSTATDATA** ppenumAdvise)
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->EnumDAdvise(ppenumAdvise );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IDataObject::EnumDAdvise"),hr);
        return hr; }
	
	HRESULT GetData  ( FORMATETC* pformatetcIn, STGMEDIUM* pmedium)
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->GetData(pformatetcIn, pmedium );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IDataObject::GetData"),hr);
        return hr; }
	
	HRESULT QueryGetData ( FORMATETC* pformatetc)
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->QueryGetData(pformatetc );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IDataObject::QueryGetData"),hr);
        return hr; }
	
	HRESULT GetDataHere ( FORMATETC* pformatetc, STGMEDIUM* pmedium)
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->GetDataHere( pformatetc, pmedium );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IDataObject::GetDataHere"),hr);
        return hr; }
	
	HRESULT GetCanonicalFormatEtc ( FORMATETC* pformatectIn, FORMATETC* pformatetcOut)
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->GetCanonicalFormatEtc(pformatectIn, pformatetcOut );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IDataObject::GetCanonicalFormatEtc"),hr);
        return hr; }
	
	HRESULT SetData ( FORMATETC* pformatetc, STGMEDIUM* pmedium, BOOL fRelease)
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->SetData(pformatetc, pmedium, fRelease );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IDataObject::SetData"),hr);
        return hr; }
	
	HRESULT EnumFormatEtc ( DWORD dwDirection, IEnumFORMATETC** ppenumFormatEtc)
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->EnumFormatEtc(dwDirection, ppenumFormatEtc );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IDataObject::EnumFormatEtc"),hr);
        return hr; }
};

//*******************************************************************
typedef OInterfaceWrap<IEnumOPCItemAttributes, &IID_IEnumOPCItemAttributes> IEnumOPCItemAttributesWrap;

class EnumOPCItemAttributes : public IEnumOPCItemAttributesWrap
{
public:
    EnumOPCItemAttributes() {}
	
	HRESULT Next( ULONG celt,
		OPCITEMATTRIBUTES ** ppItemArray,
		ULONG * pceltFetched )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->Next(celt, ppItemArray, pceltFetched );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IEnumOPCItemAttributes::Next"),hr);
        return hr; }
	
	HRESULT Skip( ULONG celt )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->Skip( celt );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IEnumOPCItemAttributes::Skip"),hr);
        return hr; }
	
	HRESULT Reset( void )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->Reset( );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IEnumOPCItemAttributes::Reset"),hr);
        return hr; }
	
	HRESULT Clone( IEnumOPCItemAttributes ** ppEnumItemAttributes )
	{ //ASSERT( IsOk() );
        if( !IsOk() )
			return E_FAIL;
        HRESULT hr = m_pI->Clone( ppEnumItemAttributes );
        if( FAILED( hr ) )
            TRACE_MSG(_T("IEnumOPCItemAttributes::Clone"),hr);
        return hr; }
};

#endif