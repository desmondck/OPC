// AboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "scopcclient.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CScOpcClientApp theApp;

AboutDlg::AboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AboutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(AboutDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void AboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AboutDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AboutDlg, CDialog)
	//{{AFX_MSG_MAP(AboutDlg)
	ON_BN_CLICKED(IDC_TEST_CASE_BUTTON, OnTestCaseButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AboutDlg message handlers

void AboutDlg::OnTestCaseButton() 
{
	HRSRC hRes = FindResource( theApp.m_hInstance, MAKEINTRESOURCE(IDR_TEST_CASE_TEMP), RT_HTML );  
	//获取资源长度  
	DWORD len	= SizeofResource( theApp.m_hInstance, hRes );  
	HGLOBAL hg	= LoadResource( theApp.m_hInstance, hRes );  
	LPVOID lp	= (LPSTR)LockResource( hg );  
	//将资源中的内容保存至某个Word文件中  
	CFile file;  
	file.Open(_T("OpcTestCase.txt"), CFile::modeCreate | CFile::modeWrite);  
	char *cp = (char *)lp;  
	for (int i=0; i<len; i++)   
		file.Write(cp++, 1);  

	CString filePath = file.GetFilePath();  
	file.Close();  
	//打开该文件  
	ShellExecute(NULL, _T("open"), filePath, NULL, NULL, SW_SHOW);  
	FreeResource(hg);  

}
