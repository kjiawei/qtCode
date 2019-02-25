// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__B78B08E9_A7E5_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_MAINFRM_H__B78B08E9_A7E5_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TheChildFrame.h"

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
	CTheChildFrame *m_pAdd, *m_pChange, *m_pSearch; // 指向三个功能窗口
	BOOL m_bLogin; // 登录状态
	BOOL m_bItemAdd, m_bItemChange, m_bItemSearch; // 相应的菜单项及工具栏按钮是否可用
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSystemConnect();
	afx_msg void OnDestroy();
	afx_msg void OnSystemDisconnect();
	afx_msg void OnUpdateSystemDisconnect(CCmdUI* pCmdUI);
	afx_msg void OnManageAdd();
	afx_msg void OnManagerChange();
	afx_msg void OnUpdateManageAdd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateManagerChange(CCmdUI* pCmdUI);
	afx_msg void OnUpdateManagerSearch(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSystemConnect(CCmdUI* pCmdUI);
	afx_msg void OnManagerSearch();
	afx_msg void OnWindowMiniall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__B78B08E9_A7E5_11D6_8649_0088CC174723__INCLUDED_)
