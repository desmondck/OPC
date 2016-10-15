// OTIOPCSyncIORead.cpp: implementation of the OTIOPCSyncIORead class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OTIOPCSyncIORead.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

OTIOPCSyncIORead::OTIOPCSyncIORead() : OpcTask( OT_IOPCSyncIO_Read, TNAME_SYNC_IO_READ )
{

}

OTIOPCSyncIORead::~OTIOPCSyncIORead()
{

}

HRESULT OTIOPCSyncIORead::DoUnserialize( TaskFileReader& taskFileReader )
{
	//สýพÝิด
	OneTaskParam oneParam;
	if( !taskFileReader.ReadParamLine(oneParam) || oneParam.ParamName.Compare( SYMBOL_DATA_SOURCE ) != 0 )
		return E_TASK_SREAD_NO_SOURCE;
	if( oneParam.ParamValues.size() != 1 )
		return E_TASK_INVALID_PARAM;

	if( oneParam.ParamValues[0].CompareNoCase( SYMBOL_DS_DEVICE ) == 0 )
		m_dwSource = OPC_DS_DEVICE;
	else if( oneParam.ParamValues[0].CompareNoCase( SYMBOL_DS_CACHE ) == 0 )
		m_dwSource = OPC_DS_CACHE;
	else
		return E_TASK_INVALID_PARAM;

	return _UnserializeGroupItems( taskFileReader, m_GroupToItems );
}

HRESULT OTIOPCSyncIORead::DoRun()
{
	for( GROUP_ITEMS_MAP::const_iterator it = m_GroupToItems.begin(); it != m_GroupToItems.end(); ++it )
	{
		OpcGroupProxy* pGroup = g_pOpcSvrProxy->FindGroup( it->first );
		if( pGroup )
			pGroup->SyncRead( m_dwSource, it->second );
	}

	return S_OK;
}

IOpcTask* OTIOPCSyncIORead::CreateInstance()
{
	return new OTIOPCSyncIORead();
}

HRESULT OTIOPCSyncIORead::_ReadData( OpcGroupProxy* pGroup, const ITEM_LIST& items )
{
	return S_OK;
}