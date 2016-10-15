// ScOpcClientDoc.h : interface of the CScOpcClientDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCOPCCLIENTDOC_H__8E71B119_9A68_4BCF_83B9_79807E463863__INCLUDED_)
#define AFX_SCOPCCLIENTDOC_H__8E71B119_9A68_4BCF_83B9_79807E463863__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CScOpcClientDoc : public CDocument
{
protected: // create from serialization only
	CScOpcClientDoc();
	DECLARE_DYNCREATE(CScOpcClientDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScOpcClientDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CScOpcClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CScOpcClientDoc)
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCOPCCLIENTDOC_H__8E71B119_9A68_4BCF_83B9_79807E463863__INCLUDED_)
