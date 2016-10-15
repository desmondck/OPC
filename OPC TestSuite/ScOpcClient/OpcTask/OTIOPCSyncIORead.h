// OTIOPCSyncIORead.h: interface for the OTIOPCSyncIORead class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OTIOPCSYNCIOREAD_H__1E0549EF_1626_4DE1_9CAC_348478125B5E__INCLUDED_)
#define AFX_OTIOPCSYNCIOREAD_H__1E0549EF_1626_4DE1_9CAC_348478125B5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class OTIOPCSyncIORead : public OpcTask 
{
public:
	OTIOPCSyncIORead();
	virtual ~OTIOPCSyncIORead();

	virtual IOpcTask*	CreateInstance();
private:
	virtual HRESULT		DoUnserialize( TaskFileReader& taskFileReader );
	virtual HRESULT		DoRun();
private:
	HRESULT _ReadData( OpcGroupProxy* pGroup, const ITEM_LIST& items );

	OPCDATASOURCE	m_dwSource;
	GROUP_ITEMS_MAP	m_GroupToItems;
};

#endif // !defined(AFX_OTIOPCSYNCIOREAD_H__1E0549EF_1626_4DE1_9CAC_348478125B5E__INCLUDED_)
