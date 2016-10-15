// OpcItem.cpp: implementation of the OpcItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpcItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

DWORD OpcItem::m_IdGenerator = 0;

OpcItem::OpcItem( const CString& groupName, const CString& strCltName, const CString& strItemName, VARTYPE vtRequest /*= VT_EMPTY */ )
: m_strGroupName(groupName), m_strCltName(strCltName), m_strItemName(strItemName), m_vtRequest(vtRequest)
, m_dwQuality(OPC_QUALITY_BAD), m_hServer(NULL), m_lRef(0)
{
	m_hClient = ++m_IdGenerator;

	VariantInit( &m_vValue );
	ZeroMemory( &m_ftTime, sizeof(m_ftTime) );
	
	AddRef();
}

DWORD OpcItem::AddRef()
{
	return InterlockedIncrement( &m_lRef );
}

DWORD OpcItem::Release()
{ 	
	if( InterlockedDecrement( &m_lRef ) == 0 )
		delete this;
	
	return m_lRef;
}

HRESULT OpcItem::GetVQT( VARIANT& value, DWORD& dwQuality, FILETIME& ftTime )
{
	VariantInit( &value );
	HRESULT hr = VariantCopy( &value, &m_vValue );
	if( FAILED(hr) )
		return hr;
	
	dwQuality = m_dwQuality;
	ftTime = m_ftTime;
	return S_OK;
}

HRESULT OpcItem::SetVQT( const VARIANT& value, DWORD quality, FILETIME fileTime )
{
	VARTYPE vtType = m_vtRequest;
	if( vtType == VT_EMPTY )
		vtType = value.vt;
	
	VariantClear( &m_vValue );
	HRESULT hr = VariantChangeType( &m_vValue, &((VARIANT)value), 0, vtType );
	if( FAILED(hr) )
		return hr;
	
	m_dwQuality = quality;
	m_ftTime = fileTime;
	return S_OK;
}