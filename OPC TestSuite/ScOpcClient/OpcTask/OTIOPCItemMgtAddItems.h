// OTIOPCItemMgtAddItems.h: interface for the OTIOPCItemMgtAddItems class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OTIOPCITEMMGTADDITEMS_H__AF1E83ED_7C7C_4D68_93C9_367A652818C9__INCLUDED_)
#define AFX_OTIOPCITEMMGTADDITEMS_H__AF1E83ED_7C7C_4D68_93C9_367A652818C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OpcTask.h"

class OTIOPCItemMgtAddItems : public OpcTask  
{
public:
	OTIOPCItemMgtAddItems();
	virtual ~OTIOPCItemMgtAddItems();

	virtual IOpcTask* CreateInstance();
private:
	virtual HRESULT	DoRun();
	virtual HRESULT DoUnserialize( TaskFileReader& taskFileReader );

	GROUP_ITEMS_MAP	m_GroupToItems;
};

#endif // !defined(AFX_OTIOPCITEMMGTADDITEMS_H__AF1E83ED_7C7C_4D68_93C9_367A652818C9__INCLUDED_)
