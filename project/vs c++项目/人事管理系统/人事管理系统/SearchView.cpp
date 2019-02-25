// SearchView.cpp : implementation file
//

#include "stdafx.h"
#include "zhaoliang.h"
#include "SearchView.h"
#include "MainFrm.h"
#include "Crypt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDatabase db;
/////////////////////////////////////////////////////////////////////////////
// CSearchView

IMPLEMENT_DYNCREATE(CSearchView, CFormView)

CSearchView::CSearchView()
	: CFormView(CSearchView::IDD)
{
	//{{AFX_DATA_INIT(CSearchView)
	m_strID = _T("");
	m_strSpecialty = _T("");
	m_strMemo = _T("");
	m_strPasswd = _T("");
	m_strName = _T("");
	m_strBirthday = _T("");
	m_strAddress = _T("");
	m_strTel = _T("");
	m_strEmail = _T("");
	//}}AFX_DATA_INIT
}

CSearchView::~CSearchView()
{
}

void CSearchView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchView)
	DDX_Control(pDX, IDC_SEARCH_LIST, m_cList);
	DDX_Control(pDX, IDC_SEARCH_CMB_JOB, m_cJob);
	DDX_Control(pDX, IDC_SEARCH_CMB_EDULEVEL, m_cEdulevel);
	DDX_Control(pDX, IDC_SEARCH_CMB_DEPARTMENT, m_cDepartment);
	DDX_Text(pDX, IDC_SEARCH_EDT_ID, m_strID);
	DDX_Text(pDX, IDC_SEARCH_EDT_SPECIALTY, m_strSpecialty);
	DDX_Text(pDX, IDC_SEARCH_EDT_MEMO, m_strMemo);
	DDX_Text(pDX, IDC_SEARCH_EDT_PASSWD, m_strPasswd);
	DDX_Text(pDX, IDC_SEARCH_EDT_NAME, m_strName);
	DDX_Text(pDX, IDC_SEARCH_EDT_BIRTHDAY, m_strBirthday);
	DDX_Text(pDX, IDC_SEARCH_EDT_ADDRESS, m_strAddress);
	DDX_Text(pDX, IDC_SEARCH_EDT_TEL, m_strTel);
	DDX_Text(pDX, IDC_SEARCH_EDT_EMAIL, m_strEmail);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchView, CFormView)
	//{{AFX_MSG_MAP(CSearchView)
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_SEARCH_EDT_ID, OnChangeSearchEdtId)
	ON_BN_CLICKED(IDC_SEARCH_BTN_CHANGE, OnSearchBtnChange)
	ON_BN_CLICKED(IDC_SEARCH_BTN_CHGPASSWD, OnSearchBtnChgpasswd)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchView diagnostics

#ifdef _DEBUG
void CSearchView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSearchView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSearchView message handlers

void CSearchView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// 给m_cList加入网格
	DWORD style=m_cList.GetExtendedStyle();
	m_cList.SetExtendedStyle(style|LVS_EX_GRIDLINES);
	// 使框架窗口大小与视图匹配
	GetParentFrame()->RecalcLayout();
    ResizeParentToFit(FALSE);

	GetParentFrame()->SetWindowText("员工信息查询修改"); // 设置标题

	CRecordset rs(&db); // 数据集
	CString str;
	// 设置部门下拉框所取的值为DEPARTMENT表中的值
	rs.Open(CRecordset::forwardOnly, "select NAME from DEPARTMENT");
	while(!rs.IsEOF())
	{
		rs.GetFieldValue("NAME", str);
		m_cDepartment.AddString(str);
		rs.MoveNext();
	}
	rs.Close();

	// 设置职务下拉框所取的值为JOB表中的值
	rs.Open(CRecordset::forwardOnly, "select DESCRIPTION from JOB");
	while(!rs.IsEOF())
	{
		rs.GetFieldValue("DESCRIPTION", str);
		m_cJob.AddString(str);
		rs.MoveNext();
	}
	rs.Close();

	// 设置受教育水平下拉框所取的值为EDU_LEVEL表中的值
	rs.Open(CRecordset::forwardOnly, "select DESCRIPTION from EDU_LEVEL");
	while(!rs.IsEOF())
	{
		rs.GetFieldValue("DESCRIPTION", str);
		m_cEdulevel.AddString(str);
		rs.MoveNext();
	}
	rs.Close();

	// 添加List控件的列
	m_cList.InsertColumn(0, "记录编号", LVCFMT_LEFT, 100);
	m_cList.InsertColumn(1, "记录时间", LVCFMT_LEFT, 100);
	m_cList.InsertColumn(2, "具体描述", LVCFMT_LEFT, 215);
    m_brush.CreateSolidBrush(RGB(0,150,200));
	Init(); // 调用初始化函数
}

void CSearchView::OnDestroy() 
{
	CFormView::OnDestroy();
	
	((CMainFrame*)AfxGetMainWnd())->m_bItemSearch=TRUE; // 开放"查询修改"功能"
	((CMainFrame*)AfxGetMainWnd())->m_pSearch=NULL; // 清空窗口指针
}

void CSearchView::Init()
{
	// 清空成员变量
	m_strID = _T("");
	m_strSpecialty = _T("");
	m_strMemo = _T("");
	m_strPasswd = _T("");
	m_strName = _T("");
	m_strBirthday = _T("");
	m_strAddress = _T("");
	m_strTel = _T("");
	m_strEmail = _T("");

	UpdateData(FALSE); // 更新界面数据
}

void CSearchView::OnChangeSearchEdtId() 
{
	UpdateData(); // 更新数据
	m_cList.DeleteAllItems(); // 清空列表框

	CRecordset rs(&db);
	CString strDep,strJob,strEdulevel,strSex;

	rs.Open(CRecordset::forwardOnly,
		"select NAME,DEPARTMENT,JOB,EDU_LEVEL,SPECIALTY,REMARK,BIRTHDAY,ADDRESS,TEL,EMAIL,SEX from PERSON where ID='" + m_strID + "'");
	if(!rs.IsEOF()) // 非空则获取员工信息
	{
		rs.GetFieldValue("NAME", m_strName); // 名字
		rs.GetFieldValue("DEPARTMENT", strDep); // 部门编号
		rs.GetFieldValue("JOB", strJob); // 职务代码
		rs.GetFieldValue("EDU_LEVEL", strEdulevel); // 受教育水平
		rs.GetFieldValue("SPECIALTY", m_strSpecialty); // 专业
		rs.GetFieldValue("REMARK", m_strMemo); // 备注
		rs.GetFieldValue("BIRTHDAY", m_strBirthday); // 生日
		m_strBirthday=m_strBirthday.Left(10); // 取日期部分
		rs.GetFieldValue("ADDRESS", m_strAddress); // 住址
		rs.GetFieldValue("TEL", m_strTel); // 电话
		rs.GetFieldValue("EMAIL", m_strEmail); // Email
		rs.GetFieldValue("SEX", strSex); // 性别
		rs.Close();

		// 得到部门名称
		if(!strDep.IsEmpty())
		{
			rs.Open(CRecordset::forwardOnly,
				"select NAME from DEPARTMENT where ID='" + strDep + "'");
			rs.GetFieldValue("NAME", strDep); // 部门名称
			rs.Close();
		}
		// 得到职务名称
		if(!strJob.IsEmpty())
		{
			rs.Open(CRecordset::forwardOnly,
				"select DESCRIPTION from JOB where CODE='" + strJob + "'");
			rs.GetFieldValue("DESCRIPTION", strJob); // 职务名称
			rs.Close();
		}
		// 得到教育水平描述
		if(!strEdulevel.IsEmpty())
		{
			rs.Open(CRecordset::forwardOnly,
				"select DESCRIPTION from EDU_LEVEL where CODE='"
				+ strEdulevel + "'");
			rs.GetFieldValue("DESCRIPTION", strEdulevel); // 教育水平描述
			rs.Close();
		}
		// 设置性别选框
		if(strSex=="M") ((CButton*)GetDlgItem(IDC_SEARCH_RADIO_MALE))->SetCheck(TRUE);
		else ((CButton*)GetDlgItem(IDC_SEARCH_RADIO_FEMALE))
			->SetCheck(TRUE);
		UpdateData(FALSE); // 更新数据

		m_cDepartment.SelectString(-1,strDep);
		m_cJob.SelectString(-1,strJob);
		m_cEdulevel.SelectString(-1,strEdulevel);

		// 更新列表框数据
		int i=0;
		CString str1,str2,str3;
		rs.Open(CRecordset::forwardOnly,
			"select ID,RECORD_TIME,DESCRIPTION from zhaoliang\
			where PERSON='" + m_strID + "'");
		while(!rs.IsEOF())
		{
			// 得到数据
			rs.GetFieldValue("ID", str1);
			rs.GetFieldValue("RECORD_TIME", str2);
			str2=str2.Left(10); // 只取日期
			rs.GetFieldValue("DESCRIPTION", str3);
			// 加入List
			m_cList.InsertItem(i,"");
			m_cList.SetItemText(i, 0, str1);
			m_cList.SetItemText(i, 1, str2);
			m_cList.SetItemText(i, 2, str3);
			i++;
			rs.MoveNext(); // 移动记录
		}
		rs.Close();

		m_bExist=TRUE; // 该员工存在
	}
	else // 否则清空员工信息
	{
		rs.Close();
		m_strSpecialty = _T("");
		m_strMemo = _T("");
		m_strPasswd = _T("");
		m_strName = _T("");
		m_strBirthday = _T("");
		m_strAddress = _T("");
		m_strTel = _T("");
		m_strEmail = _T("");
		m_cDepartment.SetCurSel(-1);
		m_cJob.SetCurSel(-1);
		m_cEdulevel.SetCurSel(-1);
		UpdateData(FALSE); // 更新数据
		((CButton*)GetDlgItem(IDC_SEARCH_RADIO_MALE))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_SEARCH_RADIO_FEMALE))->SetCheck(FALSE);

		m_bExist=FALSE; // 该员工不存在
	}
}

void CSearchView::OnSearchBtnChgpasswd() 
{
	if(!m_bExist) // 该员工号不存在
	{
		AfxMessageBox("该员工号不存在");
		return;
	}
	UpdateData(); // 更新数据

	CString str,strSQL;

	str=CCrypt::Encrypt(m_strPasswd, 123); // 加密
	strSQL="update PERSON set PASSWD='" + str + "'"; // 写SQL语句
	db.ExecuteSQL(strSQL); // 执行
}

void CSearchView::OnSearchBtnChange() 
{
	if(!m_bExist) // 该员工号不存在
	{
		AfxMessageBox("该员工号不存在");
		return;
	}
	UpdateData(); // 更新数据

// 修改员工个人信息记录
	CString str,strSex,strDepID,strJobID,strEduID,strSQL;
	CRecordset rs(&db);

	// 判断性别
	if(((CButton*)GetDlgItem(IDC_SEARCH_RADIO_MALE))->GetCheck()) strSex="M";
	else strSex="F";
	// 得到部门ID
	m_cDepartment.GetWindowText(str);
	if(!str.IsEmpty()) // 不空
	{
		rs.Open(CRecordset::forwardOnly,
			"select ID from DEPARTMENT where NAME='" + str +"'");
		rs.GetFieldValue("ID", strDepID);
		rs.Close();
	}	
	// 得到职务代码
	m_cJob.GetWindowText(str);
	if(!str.IsEmpty()) // 不空
	{
		rs.Open(CRecordset::forwardOnly,
			"select CODE from JOB where DESCRIPTION='" + str +"'");
		rs.GetFieldValue("CODE", strJobID);
		rs.Close();
	}
	// 得到受教育水平代码
	m_cEdulevel.GetWindowText(str);
	if(!str.IsEmpty()) // 不空
	{
		rs.Open(CRecordset::forwardOnly,
			"select CODE from EDU_LEVEL where DESCRIPTION='" + str +"'");
		rs.GetFieldValue("CODE", strEduID);
		rs.Close();
	}
	// 写SQL语句
	strSQL="update PERSON set\
		NAME='" + m_strName  //NAME
		+ "',SEX='" + strSex // SEX
		+ "',BIRTHDAY='" + m_strBirthday // BIRTHDAY
		+ "',DEPARTMENT='" + strDepID // DEPARTMENT
		+ "',JOB='" + strJobID // JOB
		+ "',EDU_LEVEL='" + strEduID // EDU_LEVEL
		+ "',SPECIALTY='" + m_strSpecialty // SPECIALTY
		+ "',ADDRESS='" + m_strAddress // ADDRESS
		+ "',TEL='" + m_strTel // TEL
		+ "',EMAIL='" + m_strEmail // EMAIL
		+ "',REMARK='" + m_strMemo // REMARK
		+ "' where ID='" + m_strID + "'"; // 条件
	db.ExecuteSQL(strSQL); // 执行
}

HBRUSH CSearchView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
		HBRUSH hbr = (HBRUSH)m_brush;
   
	if(nCtlColor==CTLCOLOR_STATIC)
	{   pDC->SetBkMode(TRANSPARENT);
		return hbr;
	}
	if(nCtlColor==CTLCOLOR_EDIT)
	{  
		return NULL;
	}

	return hbr;
}
