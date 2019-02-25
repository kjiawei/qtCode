// RectDoc.h : interface of the CRectDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECTDOC_H__54F67C8B_EFFA_11D5_9B6C_959406F6741C__INCLUDED_)
#define AFX_RECTDOC_H__54F67C8B_EFFA_11D5_9B6C_959406F6741C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRectDoc : public CDocument
{
protected: // create from serialization only
	CRectDoc();
	DECLARE_DYNCREATE(CRectDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRectDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRectDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECTDOC_H__54F67C8B_EFFA_11D5_9B6C_959406F6741C__INCLUDED_)
