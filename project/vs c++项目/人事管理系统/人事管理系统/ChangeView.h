#if !defined(AFX_CHANGEVIEW_H__797F6901_A971_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_CHANGEVIEW_H__797F6901_A971_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChangeView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChangeView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CChangeView : public CFormView
{
protected:
	CChangeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CChangeView)

// Form Data
public:
	//{{AFX_DATA(CChangeView)
	enum { IDD = IDD_FORMVIEW_CHANGE };
	CComboBox	m_cJob;
	CComboBox	m_cDepartment;
	CString	m_strID;
	CTime	m_Time;
	CString	m_strName;
	CString	m_strDescription;
	CBrush m_brush;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	BOOL m_bExist;
	void Init();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CChangeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CChangeView)
	afx_msg void OnDestroy();
	afx_msg void OnChangeChangeEdtId();
	afx_msg void OnChangeBtnChange();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGEVIEW_H__797F6901_A971_11D6_8649_0088CC174723__INCLUDED_)
