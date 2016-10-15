// ErrorHelper.h: interface for the ErrorHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ERRORHELPER_H__4B6FB549_5EA6_4538_8FEE_B29ECDD948A2__INCLUDED_)
#define AFX_ERRORHELPER_H__4B6FB549_5EA6_4538_8FEE_B29ECDD948A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef map<HRESULT, CString> ERR_MSG_MAP;

class ErrorHelper  
{
public:
	static BOOL GetErrorMessage( HRESULT hr, CString& strErrMsg );
private:
	ErrorHelper() {}
	virtual ~ErrorHelper() {}
	
	static void _Init();
	static ERR_MSG_MAP	m_TaskErrMsgs;
};

#endif // !defined(AFX_ERRORHELPER_H__4B6FB549_5EA6_4538_8FEE_B29ECDD948A2__INCLUDED_)
