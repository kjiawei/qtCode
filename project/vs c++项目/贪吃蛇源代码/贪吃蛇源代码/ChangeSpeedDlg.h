#if !defined(AFX_CHANGESPEEDDLG_H__86C7AB5F_8A48_412F_8531_5615AF15D95B__INCLUDED_)
#define AFX_CHANGESPEEDDLG_H__86C7AB5F_8A48_412F_8531_5615AF15D95B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChangeSpeedDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChangeSpeedDlg dialog

class CChangeSpeedDlg : public CDialog
{
// Construction
public:
	CChangeSpeedDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChangeSpeedDlg)
	enum { IDD = IDD_CHANGESPEEDDLG };
	int		m_speed;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeSpeedDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChangeSpeedDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGESPEEDDLG_H__86C7AB5F_8A48_412F_8531_5615AF15D95B__INCLUDED_)
