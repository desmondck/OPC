// OTAsyncIO2Write.cpp: implementation of the OTAsyncIO2Write class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OTAsyncIO2Write.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

OTAsyncIO2Write::OTAsyncIO2Write() : OpcTask( OT_IOPCAsyncIO2_Write, TNAME_ASYNC_IO_WRITE2 ), m_dwValueIndex(0)
{

}

OTAsyncIO2Write::~OTAsyncIO2Write()
{

}

HRESULT OTAsyncIO2Write::DoUnserialize( TaskFileReader& taskFileReader )
{
	//数据值
	HRESULT hr = _UnserializeVariants( taskFileReader, m_vDataValues );
	if( FAILED(hr) )
		return hr;
	
	return _UnserializeGroupItems( taskFileReader, m_GroupToItems );
}

IOpcTask* OTAsyncIO2Write::CreateInstance()
{
	return new OTAsyncIO2Write();
}

HRESULT OTAsyncIO2Write::DoRun()
{
	for( GROUP_ITEMS_MAP::const_iterator it = m_GroupToItems.begin(); it != m_GroupToItems.end(); ++it )
	{
		OpcGroupProxy* pGroup = g_pOpcSvrProxy->FindGroup( it->first );
		if( pGroup )
			pGroup->AsyncWrite2( m_vDataValues[m_dwValueIndex], it->second );
	}	

	//定位至下一次运行时写值的内容
	if( m_dwValueIndex == (m_vDataValues.size() - 1) )
		m_dwValueIndex = 0;
	else
		++m_dwValueIndex;
	
	
	return S_OK;
}
