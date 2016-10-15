// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ScOpcClient.h"
#include "AboutDlg.h"
#include "MainFrm.h"

#include <PROCESS.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

OpcServerProxy* g_pOpcSvrProxy;
Context g_Context;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_OPC_TEST_RUN, OnOpcTestRun)
	ON_COMMAND(ID_OPC_TEST_STOP, OnOpcTestStop)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

unsigned int _stdcall ThreadRunTest( void* pParam )
{
	if( !pParam )
		return -1;

	CoInitializeEx( NULL, COINIT_MULTITHREADED );
	CMainFrame* pMainFrame = (CMainFrame*)pParam;
	pMainFrame->RunTest();
	CoUninitialize();

	_endthreadex(0);
	return 0;
}

CMainFrame::CMainFrame() : m_hRunThread(NULL), m_hStopEvent(NULL)
{
}

CMainFrame::~CMainFrame()
{
	g_Context.Stop();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

void CMainFrame::OnOpcTestRun() 
{
	if( WaitForSingleObject( m_hRunThread, 1000 ) == WAIT_TIMEOUT || g_Context.TasksInRunning() )
	{
		AfxMessageBox( "运行中，请等待此次运行完成!" );
		return;
	}
	else
	{
		CloseHandle( m_hRunThread );
		CloseHandle( m_hStopEvent );
		
		m_hRunThread = (HANDLE)_beginthreadex( NULL, 0, ThreadRunTest, this, 0, NULL );
		m_hStopEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
	}
}

void CMainFrame::RunTest()
{
	HRESULT hr = g_Context.RunAllTasks();
	if( FAILED(hr) )
		AfxMessageBox( "任务运行失败" );
		//ShowErrorMessage( hr );
}

void CMainFrame::OnOpcTestStop() 
{
	g_Context.Stop();
	AfxMessageBox( "测试已终止运行!" );
}

void CMainFrame::OnHelpAbout() 
{
	AboutDlg aboutDlg;
	aboutDlg.DoModal();
}
