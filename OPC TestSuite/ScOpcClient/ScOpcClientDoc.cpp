// ScOpcClientDoc.cpp : implementation of the CScOpcClientDoc class
//

#include "stdafx.h"
#include "ScOpcClient.h"

#include "ScOpcClientDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CScOpcClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CScOpcClientDoc, CDocument)
	//{{AFX_MSG_MAP(CScOpcClientDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CScOpcClientDoc::CScOpcClientDoc()
{
}

CScOpcClientDoc::~CScOpcClientDoc()
{
}

BOOL CScOpcClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

void CScOpcClientDoc::Serialize(CArchive& ar)
{
// 	//����
// 	if (ar.IsStoring())
// 		return;	
// 
// 	//��
// 	if( g_Context.TasksInRunning() )
// 	{
// 		AfxMessageBox( "�����У�����ֹͣ�˴�����!" );
// 		return;
// 	}
// 
// 	g_Context.ClearAllTask();
// 	CString strErrMsg;
// 	if( SUCCEEDED( g_Context.Unserialize(ar, strErrMsg) ) )
// 		AfxMessageBox( "������������ɹ�" );
// 	else
// 		AfxMessageBox( strErrMsg );
}

#ifdef _DEBUG
void CScOpcClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CScOpcClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

void CScOpcClientDoc::OnFileOpen() 
{
	//ԭ������������
	if( g_Context.TasksInRunning() )
	{
		AfxMessageBox( "�����У�����ֹͣ�˴�����!" );
		return;
	}
	
	g_Context.ClearAllTask();
	
	
	CFileDialog fileDlg(TRUE);
	if( fileDlg.DoModal() != IDOK )
		return;
	
	CString strFullName = fileDlg.GetPathName();
	CFile file( strFullName, CFile::modeRead );
	CArchive ar( &file, CArchive::load );
	
	CString strErrMsg;
	if( FAILED( g_Context.Unserialize(ar, strErrMsg) ) )
	{
		AfxMessageBox( strErrMsg );
		SetTitle( strFullName );
		return;
	}
	
	AfxMessageBox( "������������ɹ�" );
	SetTitle( strFullName );	
}
