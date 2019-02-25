// ScoreBoardDlg.cpp : implementation file
//

#include "stdafx.h"
#include "snake.h"
#include "ScoreBoardDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScoreBoardDlg dialog


CScoreBoardDlg::CScoreBoardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScoreBoardDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScoreBoardDlg)
	m_scoreBoardMessages = _T("");
	//}}AFX_DATA_INIT
}


void CScoreBoardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScoreBoardDlg)
	DDX_Text(pDX, IDC_EDIT_SCORES, m_scoreBoardMessages);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScoreBoardDlg, CDialog)
	//{{AFX_MSG_MAP(CScoreBoardDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScoreBoardDlg message handlers
