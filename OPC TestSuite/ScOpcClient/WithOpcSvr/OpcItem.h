// OpcItem.h: interface for the OpcItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPCITEM_H__87B548F5_FC5E_4D9F_922B_87EEED4E0C57__INCLUDED_)
#define AFX_OPCITEM_H__87B548F5_FC5E_4D9F_922B_87EEED4E0C57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class OpcItem
{
public:
	OpcItem( const CString& groupName, const CString& strCltName, const CString& strItemName, VARTYPE vtRequest = VT_EMPTY );

	DWORD	AddRef();
	DWORD	Release();

	inline CString	GetCltName() { return m_strCltName; }
	inline CString	GetItemName() { return m_strItemName; }
	inline CString	GetGroupName() { return m_strGroupName; }
	inline VARTYPE	GetRequestType() { return m_vtRequest; }
	inline void		SetRequestType( VARTYPE vtRequest ) { m_vtRequest = vtRequest; }
	inline OPCHANDLE GetServerHandle() { return m_hServer; }
	inline void		SetServerHandle( OPCHANDLE hServer ) { m_hServer = hServer; }
	inline OPCHANDLE GetClientHandle() { return m_hClient; }
	
	HRESULT GetVQT( VARIANT& value, DWORD& dwQuality, FILETIME& ftTime );
	HRESULT SetVQT( const VARIANT& value, DWORD quality, FILETIME fileTime );
private:
	
	OpcItem ( const OpcItem& Item ) {}	//拷贝构造私有化
	~OpcItem() {}
private:
	CString		m_strItemName;
	CString		m_strCltName;
	CString		m_strGroupName;

	OPCHANDLE	m_hClient;
	OPCHANDLE	m_hServer;
	
	VARTYPE		m_vtRequest;
	VARIANT		m_vValue;
	DWORD		m_dwQuality;
	FILETIME	m_ftTime;

	volatile long	m_lRef;

	static DWORD	m_IdGenerator;
};


#endif // !defined(AFX_OPCITEM_H__87B548F5_FC5E_4D9F_922B_87EEED4E0C57__INCLUDED_)
