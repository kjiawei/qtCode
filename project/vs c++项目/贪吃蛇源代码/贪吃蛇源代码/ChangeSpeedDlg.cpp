// ChangeSpeedDlg.cpp : implementation file
//

#include "stdafx.h"
#include "snake.h"
#include "ChangeSpeedDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangeSpeedDlg dialog


CChangeSpeedDlg::CChangeSpeedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeSpeedDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangeSpeedDlg)
	m_speed = 0;
	//}}AFX_DATA_INIT
}


void CChangeSpeedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangeSpeedDlg)
	DDX_Text(pDX, IDC_EDIT_SPEED, m_speed);
	DDV_MinMaxInt(pDX, m_speed, 1, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangeSpeedDlg, CDialog)
	//{{AFX_MSG_MAP(CChangeSpeedDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeSpeedDlg message handlers

BOOL CChangeSpeedDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    CSpinButtonCtrl *pSpin = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN);
    pSpin->SetRange(1, 10);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
