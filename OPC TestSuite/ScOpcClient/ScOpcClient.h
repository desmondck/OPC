// ScOpcClient.h : main header file for the SCOPCCLIENT application
//

#if !defined(AFX_SCOPCCLIENT_H__0CEB3B03_6E6F_4FED_92FB_49CA2FDF0613__INCLUDED_)
#define AFX_SCOPCCLIENT_H__0CEB3B03_6E6F_4FED_92FB_49CA2FDF0613__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CScOpcClientApp:
// See ScOpcClient.cpp for the implementation of this class
//

class CScOpcClientApp : public CWinApp
{
public:
	CScOpcClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScOpcClientApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CScOpcClientApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCOPCCLIENT_H__0CEB3B03_6E6F_4FED_92FB_49CA2FDF0613__INCLUDED_)
