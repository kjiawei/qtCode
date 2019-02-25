#if !defined(AFX_SCOREBOARDDLG_H__BFAC9726_2370_4669_8AE7_4FD8338A36D6__INCLUDED_)
#define AFX_SCOREBOARDDLG_H__BFAC9726_2370_4669_8AE7_4FD8338A36D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScoreBoardDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScoreBoardDlg dialog

class CScoreBoardDlg : public CDialog
{
// Construction
public:
	CScoreBoardDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScoreBoardDlg)
	enum { IDD = IDD_SCOREBOARD };
	CString	m_scoreBoardMessages;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScoreBoardDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScoreBoardDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCOREBOARDDLG_H__BFAC9726_2370_4669_8AE7_4FD8338A36D6__INCLUDED_)
