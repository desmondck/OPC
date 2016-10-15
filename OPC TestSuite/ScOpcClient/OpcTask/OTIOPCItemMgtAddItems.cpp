// OTIOPCItemMgtAddItems.cpp: implementation of the OTIOPCItemMgtAddItems class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OTIOPCItemMgtAddItems.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

OTIOPCItemMgtAddItems::OTIOPCItemMgtAddItems() : OpcTask( OT_IOPCItemMgt_AddItems, _T("Ìí¼ÓÎ»ºÅ") )
{
}

OTIOPCItemMgtAddItems::~OTIOPCItemMgtAddItems()
{

}

HRESULT OTIOPCItemMgtAddItems::DoRun()
{
	for( GROUP_ITEMS_MAP::iterator it = m_GroupToItems.begin(); it != m_GroupToItems.end(); ++it )
	{
		OpcGroupProxy* pGroup = g_pOpcSvrProxy->FindGroup( it->first );
		if( pGroup )
			pGroup->AddItems( it->second );
	}

	return S_OK;
}

IOpcTask* OTIOPCItemMgtAddItems::CreateInstance()
{
	return new OTIOPCItemMgtAddItems();
}

HRESULT OTIOPCItemMgtAddItems::DoUnserialize( TaskFileReader& taskFileReader )
{
	HRESULT hr = _UnserializeGroupItems( taskFileReader, m_GroupToItems );
	if( FAILED(hr) )
		return hr;

	for( GROUP_ITEMS_MAP::iterator it = m_GroupToItems.begin(); it != m_GroupToItems.end(); ++it )
	{
		if( it->second.size() == 0 )
			return E_TASK_INVALID_ALL_SYM;
	}

	return hr;
}
