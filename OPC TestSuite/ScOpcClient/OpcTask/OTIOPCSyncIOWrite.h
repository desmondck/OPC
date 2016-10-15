// OTIOPCSyncIOWrite.h: interface for the OTIOPCSyncIOWrite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OTIOPCSYNCIOWRITE_H__D8578A11_6A1E_4FF3_A2A8_5CCC5790AF21__INCLUDED_)
#define AFX_OTIOPCSYNCIOWRITE_H__D8578A11_6A1E_4FF3_A2A8_5CCC5790AF21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class OTIOPCSyncIOWrite : public OpcTask  
{
public:
	OTIOPCSyncIOWrite();
	virtual ~OTIOPCSyncIOWrite();

	virtual IOpcTask*	CreateInstance();
private:
	virtual HRESULT		DoUnserialize( TaskFileReader& taskFileReader );
	virtual HRESULT		DoRun();
private:
	BOOL _GetDataValueInfo( const CString& strDataInfo, VARIANT& vValue );
	vector<VARIANT>	m_vDataValues;
	GROUP_ITEMS_MAP	m_GroupToItems;

	DWORD m_dwValueIndex;
};

#endif // !defined(AFX_OTIOPCSYNCIOWRITE_H__D8578A11_6A1E_4FF3_A2A8_5CCC5790AF21__INCLUDED_)
