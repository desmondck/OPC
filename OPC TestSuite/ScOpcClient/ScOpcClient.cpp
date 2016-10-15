// ScOpcClient.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ScOpcClient.h"

#include "MainFrm.h"
#include "ScOpcClientDoc.h"
#include "ScOpcClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScOpcClientApp

BEGIN_MESSAGE_MAP(CScOpcClientApp, CWinApp)
	//{{AFX_MSG_MAP(CScOpcClientApp)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScOpcClientApp construction

CScOpcClientApp::CScOpcClientApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CScOpcClientApp object

CScOpcClientApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CScOpcClientApp initialization

BOOL CScOpcClientApp::InitInstance()
{
	AfxEnableControlContainer();

	CoInitializeEx( NULL, COINIT_MULTITHREADED );
	// Standard initialization
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	
	// Change the registry key under which our settings are stored.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register document templates

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CScOpcClientDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CScOpcClientView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

int CScOpcClientApp::ExitInstance()
{
	CoUninitialize();

	return CWinApp::ExitInstance();
}
