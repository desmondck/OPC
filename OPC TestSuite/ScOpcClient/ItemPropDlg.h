#if !defined(AFX_ITEMPROPDLG_H__833E382A_560E_413F_9B50_2285DFEC3186__INCLUDED_)
#define AFX_ITEMPROPDLG_H__833E382A_560E_413F_9B50_2285DFEC3186__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ItemPropDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ItemPropDlg dialog

class ItemPropDlg : public CDialog
{
// Construction
public:
	ItemPropDlg( OpcItem* pItem, CWnd* pParent = NULL );   // standard constructor

// Dialog Data
	//{{AFX_DATA(ItemPropDlg)
	enum { IDD = IDD_ITEM_PROP_DLG };
	CListCtrl	m_PropList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ItemPropDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ItemPropDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		void _ReloadPropList();
private:
	OpcItem* m_pItem;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ITEMPROPDLG_H__833E382A_560E_413F_9B50_2285DFEC3186__INCLUDED_)
