
// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__89BE063F_CEEE_4B0B_8339_23114C33E052__INCLUDED_)
#define AFX_STDAFX_H__89BE063F_CEEE_4B0B_8339_23114C33E052__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define _WIN32_DCOM     // This includes new DCOM calls

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxcview.h>
#include <atlbase.h>        // ATL conversion functions

#include <set>
#include <map>
#include <vector>
using namespace std;

#include "VariantHelper.h"

#include "resource.h"
#include "ErrorDefine.h"
#include "ErrorHelper.h"

#include "LockHelper.h"
typedef LockHelper<CCriticalSectionLock> CSLock;

#include "OpcServerProxy.h"
extern OpcServerProxy* g_pOpcSvrProxy;

#include "CoTaskMemory.h"

#include "OpcTask/Context.h"
extern Context	g_Context;

#include "OpcTask/OpcTask.h"

#include "TaskLogFile.h"
#include "OpcTask/TaskFileMacroDef.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__89BE063F_CEEE_4B0B_8339_23114C33E052__INCLUDED_)
