// ScOpcClientView.cpp : implementation of the CScOpcClientView class
//

#include "stdafx.h"
#include "ScOpcClient.h"
#include "ScOpcClientDoc.h"
#include "ScOpcClientView.h"

#include "ItemPropDlg.h"
#include "ItemAttrDlg.h"

#include "VariantHelper.h"
#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT _stdcall ThreadProc( void* pThis )
{
	CScOpcClientView* pView = (CScOpcClientView*)pThis;
	
	return pView->RefreshData();
}


IMPLEMENT_DYNCREATE(CScOpcClientView, CListView)

BEGIN_MESSAGE_MAP(CScOpcClientView, CListView)
	//{{AFX_MSG_MAP(CScOpcClientView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ITEM_ATTR, OnItemAttr)
	ON_COMMAND(ID_ITEM_PROP, OnItemProp)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_UPDATE_COMMAND_UI(ID_ITEM_ATTR, OnUpdateItemAttr)
	ON_UPDATE_COMMAND_UI(ID_ITEM_PROP, OnUpdateItemProp)
	ON_UPDATE_COMMAND_UI(ID_ITEM_READ, OnUpdateItemRead)
	ON_UPDATE_COMMAND_UI(ID_ITEM_REMOVE, OnUpdateItemRemove)
	ON_UPDATE_COMMAND_UI(ID_ITEM_WRITE, OnUpdateItemWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

enum {COLUMN_NAME, COLUMN_VALUE, COLUMN_TIME};

CScOpcClientView::CScOpcClientView() : m_pSelItem(NULL), m_dwItemVersion(0)
{
	m_dwDefaultStyle = WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT;
}

CScOpcClientView::~CScOpcClientView()
{
}

BOOL CScOpcClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CScOpcClientView drawing

void CScOpcClientView::OnDraw(CDC* pDC)
{
	CScOpcClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CScOpcClientView diagnostics

#ifdef _DEBUG
void CScOpcClientView::AssertValid() const
{
	CListView::AssertValid();
}

void CScOpcClientView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CScOpcClientDoc* CScOpcClientView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScOpcClientDoc)));
	return (CScOpcClientDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScOpcClientView message handlers

void CScOpcClientView::OnInitialUpdate() 
{
	CListCtrl& list = GetListCtrl();
	if( list.GetHeaderCtrl()->GetItemCount() )
		return;	//初始化动作已完成

	list.InsertColumn( COLUMN_NAME,  _T("Tag"), LVCFMT_LEFT, 220, 0 );
	list.InsertColumn( COLUMN_VALUE,  _T("Value"), LVCFMT_LEFT, 150, 1 );	
	list.InsertColumn( COLUMN_TIME,  _T("Time"), LVCFMT_LEFT, 150, 1 );
	
	m_hQuitEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
	m_hThread = (HANDLE)_beginthreadex( NULL, 0, ThreadProc, this, 0, NULL );

	CListView::OnInitialUpdate();
}

UINT CScOpcClientView::RefreshData()
{
	while( WaitForSingleObject( m_hQuitEvent, 1000 ) == WAIT_TIMEOUT )
	{
		if( g_pOpcSvrProxy == NULL )
		{
			_ClearAllItem();
			continue;
		}
		
		ALL_GROUPS allGroups;
		g_pOpcSvrProxy->GetAllGroups( allGroups );
		
		DWORD dwItemVersion = 0;
		//按组依次更新数据
		vector<OpcItem*>	items;
		for( ALL_GROUPS::iterator it = allGroups.begin(); it != allGroups.end(); ++it )
		{
			OpcGroupProxy* pGroup = it->second;
			
			pGroup->GetData( items );
			dwItemVersion += pGroup->GetItemVersion();

			pGroup->Release();
		}
		
		if (!::IsIconic(AfxGetMainWnd()->GetSafeHwnd()))	// 最小化不处理刷新
		{
			_UpdateDataToView( dwItemVersion, items );
		}
		
		for( int i = 0; i < items.size(); ++i )
			items[i]->Release();
	}

	return 0;
}

void CScOpcClientView::_UpdateDataToView( DWORD dwItemVersion, const vector<OpcItem*>& items )
{
	CListCtrl& list = GetListCtrl();
	list.SetRedraw( FALSE );

	if( dwItemVersion != m_dwItemVersion )
	{
		m_dwItemVersion = dwItemVersion;
		//清除原有数据
		_ClearAllItem();

		UpdateWindow();
		list.SetItemCount( items.size() );
		
		LV_ITEM lv_item;
		lv_item.mask = LVIF_TEXT | LVIF_PARAM;
		lv_item.iSubItem = COLUMN_NAME;
		
		for( int i = 0; i < items.size(); ++i )
		{
			OpcItem* pItem = items[i];
			
			CString name = pItem->GetItemName();
			//插入到View中
			lv_item.iItem = i;
			lv_item.pszText = (LPSTR)(LPCTSTR)name;
			pItem->AddRef();
			lv_item.lParam = (LPARAM)pItem;
			list.InsertItem( &lv_item );
		}
	}

	//更新数据
	for( int i = 0; i < items.size(); ++i )
	{
		OpcItem* pItem = items[i];

		//获取VQT
		VARIANT variant;
		DWORD dwQuality;
		FILETIME ftTime;
		HRESULT hr = pItem->GetVQT( variant, dwQuality, ftTime );
		if( FAILED(hr) )
			continue;

		//设置Value项
		CString strValue;
		VariantHelper::VariantToString( variant, strValue );
		VariantClear( &variant );

		DWORD dwOpcQuality = dwQuality & OPC_QUALITY_MASK;
		if( dwOpcQuality != OPC_QUALITY_GOOD )
		{
			if( dwOpcQuality == OPC_QUALITY_UNCERTAIN )
				strValue += _T(" (uncertain)");
			else if( dwOpcQuality == OPC_QUALITY_BAD )
				strValue = _T("Bad");
		}

		list.SetItem( i, COLUMN_VALUE,LVIF_TEXT,(LPSTR)(LPCTSTR)strValue,0,0,0,0 );

		//设置时间戳
		CTime time( ftTime );
		list.SetItem( i,COLUMN_TIME,LVIF_TEXT, time.Format(_T("%c")),0,0,0,0 );
	}

	list.SetRedraw( TRUE );
}

void CScOpcClientView::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	m_pSelItem = (OpcItem*)pNMListView->lParam;
	
	*pResult = 0;
}

//右键菜单
void CScOpcClientView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu popMenu;	
	if( popMenu.LoadMenu(IDR_VIEW_RB_MENU) )
		popMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x,point.y, AfxGetMainWnd());
}

void CScOpcClientView::OnItemAttr() 
{
	ItemAttrDlg dlg(m_pSelItem);
	dlg.DoModal();
}

void CScOpcClientView::OnItemProp() 
{
	ItemPropDlg dlg(m_pSelItem);
	dlg.DoModal();
}


void CScOpcClientView::OnUpdateItemAttr(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_pSelItem != NULL );
}

void CScOpcClientView::OnUpdateItemProp(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_pSelItem != NULL );
}

void CScOpcClientView::OnUpdateItemRead(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_pSelItem != NULL );
}

void CScOpcClientView::OnUpdateItemRemove(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_pSelItem != NULL );
}

void CScOpcClientView::OnUpdateItemWrite(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_pSelItem != NULL );
}

void CScOpcClientView::_ClearAllItem()
{
	CListCtrl& list = GetListCtrl();

	for( int i = 0; i < list.GetItemCount(); ++i )
	{
		OpcItem* pItem = (OpcItem*)list.GetItemData( i );
		pItem->Release();
	}

	list.DeleteAllItems();
}
