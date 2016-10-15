#include "stdafx.h"
#include "ConnectionPoint.h"

CComModule _Module;  // just needed to keep ATL happy

//**************************************************************************
// Called by the server at the update rate when data changes
STDMETHODIMP OPCCallback::OnDataChange( DWORD Transid, OPCHANDLE grphandle, HRESULT masterquality, HRESULT mastererror, DWORD count, 
									   OPCHANDLE* clienthandles, VARIANT* values, WORD* quality, FILETIME* time, HRESULT* errors)
{
	m_pUpdateDataHandler->UpdateData( count, (HANDLE*)clienthandles, values, quality, time, errors );
	return S_OK;
}

//**************************************************************************
// Called by the server to complete an ASyncIO2::Read
STDMETHODIMP OPCCallback::OnReadComplete( DWORD Transid, OPCHANDLE grphandle, HRESULT masterquality, HRESULT mastererror, DWORD count, 
									   OPCHANDLE* clienthandles, VARIANT* values, WORD* quality, FILETIME* time, HRESULT* errors)
{
	m_pUpdateDataHandler->UpdateData( count, (HANDLE*)clienthandles, values, quality, time, errors );
	return S_OK;
}

//**************************************************************************
// Called by the server to complete an ASyncIO2::Write
STDMETHODIMP OPCCallback::OnWriteComplete( DWORD Transid, OPCHANDLE grphandle, HRESULT mastererr, DWORD count, 
										  OPCHANDLE* clienthandles, HRESULT* errors)
{
   return S_OK;
}

//**************************************************************************
// Called by the server to complete an ASyncIO2::Cancel
STDMETHODIMP OPCCallback::OnCancelComplete( DWORD transid, OPCHANDLE grphandle)
{
   return S_OK;
}

void OPCCallback::SetCallbackObject( IUpdateDataHandler* pUpdateData )
{
	m_pUpdateDataHandler = pUpdateData;
}

//**************************************************************************
// Called by 2.0 servers when shutting down.
STDMETHODIMP OPCShutdown::ShutdownRequest(LPCWSTR szReason)
{
	if( m_pShutdownHandler )
		m_pShutdownHandler->ShutDown();

	return S_OK;
}

void OPCShutdown::SetCallbackObject( IShutdownHandler* pShutdown )
{
	m_pShutdownHandler = pShutdown;
}
