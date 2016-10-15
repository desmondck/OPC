// ItemAttrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ItemAttrDlg.h"
#include "VariantHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ItemAttrDlg dialog


ItemAttrDlg::ItemAttrDlg( OpcItem* pItem,CWnd* pParent /*=NULL*/)
: CDialog(ItemAttrDlg::IDD, pParent), m_pItem(pItem)
{
	//{{AFX_DATA_INIT(ItemAttrDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ItemAttrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ItemAttrDlg)
	DDX_Control(pDX, IDC_ATTR_LIST, m_AttrList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ItemAttrDlg, CDialog)
	//{{AFX_MSG_MAP(ItemAttrDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ItemAttrDlg message handlers

BOOL ItemAttrDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_AttrList.InsertColumn(0, _T("Item Id"), LVCFMT_LEFT, 170, 0);
	m_AttrList.InsertColumn(1, _T("Access Path"), LVCFMT_LEFT, 100, 0);
	m_AttrList.InsertColumn(2, _T("Active"), LVCFMT_LEFT, 100, 0);
	m_AttrList.InsertColumn(3, _T("Client Handle"), LVCFMT_LEFT, 100, 0);
	m_AttrList.InsertColumn(4, _T("Server Handle"), LVCFMT_LEFT, 100, 0);
	m_AttrList.InsertColumn(5, _T("Access Rights"), LVCFMT_LEFT, 50, 0);
	m_AttrList.InsertColumn(6, _T("Requested Data Type"), LVCFMT_LEFT, 100, 0);
	m_AttrList.InsertColumn(7, _T("Native Data Type"), LVCFMT_LEFT, 100, 0);
	m_AttrList.InsertColumn(8, _T("EU Type"), LVCFMT_LEFT, 50, 0);

	_ReloadAttrList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ItemAttrDlg::_ReloadAttrList()
{
	OpcGroupProxy* pGroup = g_pOpcSvrProxy->FindGroup( m_pItem->GetGroupName() );
	if( !pGroup )
		return;

	EnumOPCItemAttributes enumerator;
	HRESULT hr = pGroup->CreateEnumerator( enumerator );
	if( SUCCEEDED(hr) && enumerator.IsOk() )
		_FillAttrList( enumerator );

	pGroup->Release();
}

void ItemAttrDlg::_FillAttrList( EnumOPCItemAttributes& enumerator )
{
	int index = 0;
	while( enumerator.IsOk() )
	{
		ULONG count=0;
		OPCITEMATTRIBUTES* pAttributes = NULL;
		HRESULT hr = enumerator.Next( 1, &pAttributes, &count );
		if( hr != S_OK )
			break;

		_FillAttrItem( index++, pAttributes );

		VariantClear( &pAttributes->vEUInfo );
		CoTaskMemFree( pAttributes->szAccessPath );
		CoTaskMemFree( pAttributes->szItemID );
		if( pAttributes->pBlob )
			CoTaskMemFree( pAttributes->pBlob );
		CoTaskMemFree( pAttributes );
   }
}

void ItemAttrDlg::_FillAttrItem( DWORD dwIndex, OPCITEMATTRIBUTES* pAttributes )
{
USES_CONVERSION;
	LV_ITEM     lvitem;
	CString		text;

	//Item Id
	memset(&lvitem, 0, sizeof(LV_ITEM));
	lvitem.mask     = LVIF_TEXT; 
	lvitem.iItem    = dwIndex;
	lvitem.iSubItem = 0;
	lvitem.pszText  = OLE2T(pAttributes->szItemID);
	lvitem.iImage   = 2;
	m_AttrList.InsertItem(&lvitem);
	
	//Access Path
	lvitem.mask     = LVIF_TEXT;
	lvitem.iSubItem = 1;
	lvitem.pszText = OLE2T(pAttributes->szAccessPath);
	m_AttrList.SetItem(&lvitem);

	//Active
	lvitem.mask     = LVIF_TEXT;
	lvitem.iSubItem = 2;
	text = pAttributes->bActive ? _T("ON") : _T("OFF");
	lvitem.pszText = (LPTSTR)(LPCTSTR)text;
	m_AttrList.SetItem(&lvitem);

	//Client Handle
	lvitem.mask     = LVIF_TEXT;
	lvitem.iSubItem = 3;
	text.Format( "%d", pAttributes->hClient );
	lvitem.pszText = (LPTSTR)(LPCTSTR)text;
	m_AttrList.SetItem(&lvitem);

	//Server Handle
	lvitem.mask     = LVIF_TEXT;
	lvitem.iSubItem = 4;
	text.Format( "%d", pAttributes->hServer );
	lvitem.pszText = (LPTSTR)(LPCTSTR)text;
	m_AttrList.SetItem(&lvitem);

	//Access Rights
	lvitem.mask     = LVIF_TEXT;
	lvitem.iSubItem = 5;
	text.Empty();
	if( pAttributes->dwAccessRights & OPC_READABLE )
		text += "R";
	if( pAttributes->dwAccessRights & OPC_WRITEABLE )
		text += "W";
	lvitem.pszText = (LPTSTR)(LPCTSTR)text;
	m_AttrList.SetItem(&lvitem);

	//Requested Data Type
	lvitem.mask     = LVIF_TEXT;
	lvitem.iSubItem = 6;
	VariantHelper::VarTypeToString( pAttributes->vtRequestedDataType, text );
	lvitem.pszText = (LPTSTR)(LPCTSTR)text;
	m_AttrList.SetItem(&lvitem);

	//Native Data Type
	lvitem.mask     = LVIF_TEXT;
	lvitem.iSubItem = 7;
	VariantHelper::VarTypeToString( pAttributes->vtCanonicalDataType, text );
	lvitem.pszText = (LPTSTR)(LPCTSTR)text;
	m_AttrList.SetItem(&lvitem);

	//EU Type
	lvitem.mask     = LVIF_TEXT;
	lvitem.iSubItem = 8;
	text.Format( "%d", pAttributes->dwEUType );
	lvitem.pszText = (LPTSTR)(LPCTSTR)text;
	m_AttrList.SetItem(&lvitem);

	if( m_pItem->GetClientHandle() == pAttributes->hClient )
		m_AttrList.SetItemState( dwIndex, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED);
}
