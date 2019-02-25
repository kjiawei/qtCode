// Rect.h : main header file for the RECT application
//

#if !defined(AFX_RECT_H__54F67C85_EFFA_11D5_9B6C_959406F6741C__INCLUDED_)
#define AFX_RECT_H__54F67C85_EFFA_11D5_9B6C_959406F6741C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRectApp:
// See Rect.cpp for the implementation of this class
//

class CRectApp : public CWinApp
{
public:
	CRectApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRectApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CRectApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECT_H__54F67C85_EFFA_11D5_9B6C_959406F6741C__INCLUDED_)
