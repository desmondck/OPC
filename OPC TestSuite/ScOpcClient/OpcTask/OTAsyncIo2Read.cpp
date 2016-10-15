// OTAsyncIo2Read.cpp: implementation of the OTAsyncIo2Read class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OTAsyncIo2Read.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

OTAsyncIo2Read::OTAsyncIo2Read() : OpcTask( OT_IOPCAsyncIO2_Read, TNAME_ASYNC_IO_READ2 )
{

}

OTAsyncIo2Read::~OTAsyncIo2Read()
{

}

HRESULT OTAsyncIo2Read::DoUnserialize( TaskFileReader& taskFileReader )
{
	return _UnserializeGroupItems( taskFileReader, m_GroupToItems );
}

IOpcTask* OTAsyncIo2Read::CreateInstance()
{
	return new OTAsyncIo2Read();
}

HRESULT OTAsyncIo2Read::DoRun()
{
	for( GROUP_ITEMS_MAP::const_iterator it = m_GroupToItems.begin(); it != m_GroupToItems.end(); ++it )
	{
		OpcGroupProxy* pGroup = g_pOpcSvrProxy->FindGroup( it->first );
		if( pGroup )
			pGroup->AsyncRead2( it->second );
	}
	
	return S_OK;	
}
