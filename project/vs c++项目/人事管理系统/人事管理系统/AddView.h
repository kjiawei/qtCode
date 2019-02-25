#if !defined(AFX_ADDVIEW_H__F9DBFDC3_A881_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_ADDVIEW_H__F9DBFDC3_A881_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CAddView : public CFormView
{
protected:
	CAddView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAddView)

// Form Data
public:
	//{{AFX_DATA(CAddView)
	enum { IDD = IDD_FORMVIEW_ADD };
	CComboBox	m_cEdulevel;
	CComboBox	m_cJob;
	CComboBox	m_cDepartment;
	CString	m_strID;
	CString	m_strPasswd;
	CString	m_strName;
	CString	m_strBirthday;
	CString	m_strDepartment;
	CString	m_strJob;
	CString	m_strEdulevel;
	CString	m_strSpecialty;
	CString	m_strAddress;
	CString	m_strTel;
	CString	m_strEmail;
	CString	m_strMemo;
	CBrush m_brush;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	void Init();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAddView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CAddView)
	afx_msg void OnAddBtnAdd();
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDVIEW_H__F9DBFDC3_A881_11D6_8649_0088CC174723__INCLUDED_)
