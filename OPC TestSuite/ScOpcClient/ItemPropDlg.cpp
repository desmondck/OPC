// ItemPropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "scopcclient.h"
#include "ItemPropDlg.h"
#include "VariantHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ItemPropDlg dialog


ItemPropDlg::ItemPropDlg( OpcItem* pItem, CWnd* pParent /*=NULL*/)
	: CDialog(ItemPropDlg::IDD, pParent), m_pItem(pItem)
{
	//{{AFX_DATA_INIT(ItemPropDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ItemPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ItemPropDlg)
	DDX_Control(pDX, IDC_PROP_LIST, m_PropList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ItemPropDlg, CDialog)
	//{{AFX_MSG_MAP(ItemPropDlg)
	ON_BN_CLICKED(IDC_REFRESH, OnRefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ItemPropDlg message handlers

BOOL ItemPropDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_PropList.InsertColumn(0, _T("Property"), LVCFMT_LEFT, 170, 0);
	m_PropList.InsertColumn(1, _T("Value"), LVCFMT_LEFT, 130, 0);
	

	_ReloadPropList();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ItemPropDlg::_ReloadPropList()
{
	m_PropList.DeleteAllItems();

	OPCItemProperties* pItemPropObj = g_pOpcSvrProxy->GetItemPropObject();

	DWORD numItems = 0;
	DWORD* pParameterIDs = NULL;
	LPWSTR* pDescriptions = NULL;
	VARTYPE* pDataTypes = NULL;
	USES_CONVERSION;
	HRESULT hr = pItemPropObj->QueryAvailableProperties( T2OLE(m_pItem->GetItemName()), &numItems, &pParameterIDs, &pDescriptions, &pDataTypes );
	if( FAILED(hr) )
		return ;

	VARIANT* pValues = NULL;
	HRESULT* pErrors = NULL;
	hr = pItemPropObj->GetItemProperties( T2OLE(m_pItem->GetItemName()), numItems, pParameterIDs, &pValues, &pErrors );
	if( SUCCEEDED(hr) )
	{
		LV_ITEM     lvitem;
		for( DWORD iIndex=0; iIndex<numItems; iIndex++)
		{
			memset(&lvitem, 0, sizeof(LV_ITEM));
			lvitem.mask     = LVIF_TEXT; //|LVIF_IMAGE;
			lvitem.iItem    = iIndex;
			lvitem.iSubItem = 0;
			lvitem.pszText  = OLE2T(pDescriptions[iIndex]);
			lvitem.iImage   = 2;
			m_PropList.InsertItem(&lvitem);
			
			lvitem.mask     = LVIF_TEXT;
			lvitem.iSubItem = 1;
			CString text;
			VariantHelper::VariantToString(pValues[iIndex], text);
			lvitem.pszText = (LPTSTR)(LPCTSTR)text;
			m_PropList.SetItem(&lvitem);
			
			if( pDescriptions[iIndex] ) 
				CoTaskMemFree( pDescriptions[iIndex] );
			if( pValues ) 
				VariantClear( &pValues[iIndex] );
		}
	}

	CoTaskMemory::Free( &pParameterIDs, &pDescriptions, &pDataTypes, &pValues, &pErrors );
}

void ItemPropDlg::OnRefresh() 
{
	_ReloadPropList();
}
