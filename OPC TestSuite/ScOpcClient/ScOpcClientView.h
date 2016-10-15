// ScOpcClientView.h : interface of the CScOpcClientView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCOPCCLIENTVIEW_H__02645D69_8C07_4CA1_A70D_76DB0AC25E1D__INCLUDED_)
#define AFX_SCOPCCLIENTVIEW_H__02645D69_8C07_4CA1_A70D_76DB0AC25E1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CScOpcClientView : public CListView
{
protected: // create from serialization only
	CScOpcClientView();
	DECLARE_DYNCREATE(CScOpcClientView)

// Attributes
public:
	CScOpcClientDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScOpcClientView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CScOpcClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CScOpcClientView)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnItemAttr();
	afx_msg void OnItemProp();
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateItemAttr(CCmdUI* pCmdUI);
	afx_msg void OnUpdateItemProp(CCmdUI* pCmdUI);
	afx_msg void OnUpdateItemRead(CCmdUI* pCmdUI);
	afx_msg void OnUpdateItemRemove(CCmdUI* pCmdUI);
	afx_msg void OnUpdateItemWrite(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	UINT RefreshData();
	void _UpdateDataToView( DWORD dwItemVersion, const vector<OpcItem*>& items );
	void _ClearAllItem();
private:
	HANDLE	m_hQuitEvent;
	HANDLE	m_hThread;

	OpcItem*	m_pSelItem;
	DWORD	m_dwItemVersion;
};

#ifndef _DEBUG  // debug version in ScOpcClientView.cpp
inline CScOpcClientDoc* CScOpcClientView::GetDocument()
   { return (CScOpcClientDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCOPCCLIENTVIEW_H__02645D69_8C07_4CA1_A70D_76DB0AC25E1D__INCLUDED_)
