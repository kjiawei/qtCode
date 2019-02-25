#if !defined(AFX_THECHILDFRAME_H__F9DBFDC2_A881_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_THECHILDFRAME_H__F9DBFDC2_A881_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TheChildFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTheChildFrame frame

class CTheChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CTheChildFrame)
public:
	CTheChildFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTheChildFrame)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTheChildFrame();

	// Generated message map functions
	//{{AFX_MSG(CTheChildFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THECHILDFRAME_H__F9DBFDC2_A881_11D6_8649_0088CC174723__INCLUDED_)
