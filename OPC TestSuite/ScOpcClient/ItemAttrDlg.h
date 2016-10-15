#if !defined(AFX_ITEMATTRDLG_H__F1D1C3AB_EE30_44F1_9621_EC258801DF1D__INCLUDED_)
#define AFX_ITEMATTRDLG_H__F1D1C3AB_EE30_44F1_9621_EC258801DF1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ItemAttrDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ItemAttrDlg dialog

class ItemAttrDlg : public CDialog
{
// Construction
public:
	ItemAttrDlg( OpcItem* pItem, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ItemAttrDlg)
	enum { IDD = IDD_ITEM_ATTR_DLG };
	CListCtrl	m_AttrList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ItemAttrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ItemAttrDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:	
	void _ReloadAttrList();
	void _FillAttrList( EnumOPCItemAttributes& enumerator );
	void _FillAttrItem( DWORD dwIndex, OPCITEMATTRIBUTES* pAttributes );

	OpcItem* m_pItem;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ITEMATTRDLG_H__F1D1C3AB_EE30_44F1_9621_EC258801DF1D__INCLUDED_)
