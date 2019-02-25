#if !defined(AFX_SEARCHVIEW_H__797F6907_A971_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_SEARCHVIEW_H__797F6907_A971_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CSearchView : public CFormView
{
protected:
	CSearchView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSearchView)

// Form Data
public:
	//{{AFX_DATA(CSearchView)
	enum { IDD = IDD_FORMVIEW_SEARCH };
	CListCtrl	m_cList;
	CComboBox	m_cJob;
	CComboBox	m_cEdulevel;
	CComboBox	m_cDepartment;
	CString	m_strID;
	CString	m_strSpecialty;
	CString	m_strMemo;
	CString	m_strPasswd;
	CString	m_strName;
	CString	m_strBirthday;
	CString	m_strAddress;
	CString	m_strTel;
	CString	m_strEmail;
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
	//{{AFX_VIRTUAL(CSearchView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSearchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSearchView)
	afx_msg void OnDestroy();
	afx_msg void OnChangeSearchEdtId();
	afx_msg void OnSearchBtnChange();
	afx_msg void OnSearchBtnChgpasswd();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHVIEW_H__797F6907_A971_11D6_8649_0088CC174723__INCLUDED_)
