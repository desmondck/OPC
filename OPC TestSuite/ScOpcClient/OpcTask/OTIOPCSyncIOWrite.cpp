// OTIOPCSyncIOWrite.cpp: implementation of the OTIOPCSyncIOWrite class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OTIOPCSyncIOWrite.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

OTIOPCSyncIOWrite::OTIOPCSyncIOWrite() : OpcTask( OT_IOPCSyncIO_Write, TNAME_SYNC_IO_WRITE ), m_dwValueIndex(0)
{

}

OTIOPCSyncIOWrite::~OTIOPCSyncIOWrite()
{

}

HRESULT OTIOPCSyncIOWrite::DoUnserialize( TaskFileReader& taskFileReader )
{
	//数据值
	HRESULT hr = _UnserializeVariants( taskFileReader, m_vDataValues );
	if( FAILED(hr) )
		return hr;
	
	return _UnserializeGroupItems( taskFileReader, m_GroupToItems );
}

HRESULT OTIOPCSyncIOWrite::DoRun()
{
	for( GROUP_ITEMS_MAP::const_iterator it = m_GroupToItems.begin(); it != m_GroupToItems.end(); ++it )
	{
		OpcGroupProxy* pGroup = g_pOpcSvrProxy->FindGroup( it->first );
		if( pGroup )
			pGroup->SyncWrite( m_vDataValues[m_dwValueIndex], it->second );
	}	

	//定位至下一次运行时写值的内容
	if( m_dwValueIndex == (m_vDataValues.size() - 1) )
		m_dwValueIndex = 0;
	else
		++m_dwValueIndex;

	
	return S_OK;
}

IOpcTask* OTIOPCSyncIOWrite::CreateInstance()
{
	return new OTIOPCSyncIOWrite();
}
