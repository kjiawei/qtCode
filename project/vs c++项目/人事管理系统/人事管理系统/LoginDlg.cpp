// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "zhaoliang.h"
#include "LoginDlg.h"
#include "crypt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDatabase db;
/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	m_strDSN = _T("DD");
	m_strUser = _T("AA");
	m_strPasswd = _T("");
	//}}AFX_DATA_INIT
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_CBString(pDX, IDC_CMD_DSN, m_strDSN);
	DDX_Text(pDX, IDC_EDT_USER, m_strUser);
	DDX_Text(pDX, IDC_EDT_PASSWD, m_strPasswd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

BOOL CLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// 改变"登录人事管理系统"字体大小
	LOGFONT LogFont;
	GetFont()->GetLogFont(&LogFont);
	LogFont.lfHeight+=LogFont.lfHeight/2;
	LogFont.lfWidth+=LogFont.lfWidth/2;
	m_font.CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_STATIC_LOGINTEXT)->SetFont(&m_font);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLoginDlg::OnOK() 
{
	BOOL bLogin=FALSE;
	CString strPasswd, strAuthority;

	UpdateData(); // 更新数据变量
//	if(!db.Open(m_strDSN)) return; // 连接数据库
//	CRecordset rs(&db);
//	rs.Open(CRecordset::forwardOnly,
//		"select PASSWD, AUTHORITY from PERSON where ID='"+m_strUser+"'");
	/*if(!rs.IsEOF())
	{
		rs.GetFieldValue("PASSWD", strPasswd);
		rs.GetFieldValue("AUTHORITY", strAuthority);
		if(//strPasswd == CCrypt::Encrypt(m_strPasswd, 123) &&
		   strAuthority == "1")
		{
			bLogin=TRUE; // 已连接
		}
		else
			MessageBox("请重新输入密码。\n注意大小写!","密码错误");
	}
	else
	{
		MessageBox("请确认用户名大小是否写正确!","无此用户");
	}*/
//	bLogin=TRUE;
//	rs.Close();
//	if(bLogin) EndDialog(IDOK);
//	else db.Close(); // 关闭数据库
     CString xyy;

	  if(m_strUser=xyy)
	  {
         
	  }
}
