// zhaoliang.h : main header file for the zhaoliang application
//

#if !defined(AFX_zhaoliang_H__B78B08E5_A7E5_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_zhaoliang_H__B78B08E5_A7E5_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CzhaoliangApp:
// See zhaoliang.cpp for the implementation of this class
//

class CzhaoliangApp : public CWinApp
{
public:
	CzhaoliangApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CzhaoliangApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	HMENU m_hMDIMenu;
	HACCEL m_hMDIAccel;

public:
	//{{AFX_MSG(CzhaoliangApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_zhaoliang_H__B78B08E5_A7E5_11D6_8649_0088CC174723__INCLUDED_)
