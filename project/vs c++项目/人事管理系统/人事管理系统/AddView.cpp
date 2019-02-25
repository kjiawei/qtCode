// AddView.cpp : implementation file
//

#include "stdafx.h"
#include "zhaoliang.h"
#include "AddView.h"
#include "Crypt.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDatabase db;
/////////////////////////////////////////////////////////////////////////////
// CAddView

IMPLEMENT_DYNCREATE(CAddView, CFormView)

CAddView::CAddView()
	: CFormView(CAddView::IDD)
{
	//{{AFX_DATA_INIT(CAddView)
	m_strID = _T("");
	m_strPasswd = _T("");
	m_strName = _T("");
	m_strBirthday = _T("");
	m_strDepartment = _T("");
	m_strJob = _T("");
	m_strEdulevel = _T("");
	m_strSpecialty = _T("");
	m_strAddress = _T("");
	m_strTel = _T("");
	m_strEmail = _T("");
	m_strMemo = _T("");
	//}}AFX_DATA_INIT
}

CAddView::~CAddView()
{
}

void CAddView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddView)
	DDX_Control(pDX, IDC_ADD_CMB_EDULEVEL, m_cEdulevel);
	DDX_Control(pDX, IDC_ADD_CMB_JOB, m_cJob);
	DDX_Control(pDX, IDC_ADD_CMB_DEPARTMENT, m_cDepartment);
	DDX_Text(pDX, IDC_ADD_EDT_ID, m_strID);
	DDX_Text(pDX, IDC_ADD_EDT_PASSWD, m_strPasswd);
	DDX_Text(pDX, IDC_ADD_EDT_NAME, m_strName);
	DDX_Text(pDX, IDC_ADD_EDT_BIRTHDAY, m_strBirthday);
	DDX_CBString(pDX, IDC_ADD_CMB_DEPARTMENT, m_strDepartment);
	DDX_CBString(pDX, IDC_ADD_CMB_JOB, m_strJob);
	DDX_CBString(pDX, IDC_ADD_CMB_EDULEVEL, m_strEdulevel);
	DDX_Text(pDX, IDC_ADD_EDT_SPECIALTY, m_strSpecialty);
	DDX_Text(pDX, IDC_ADD_EDT_ADDRESS, m_strAddress);
	DDX_Text(pDX, IDC_ADD_EDT_TEL, m_strTel);
	DDX_Text(pDX, IDC_ADD_EDT_EMAIL, m_strEmail);
	DDX_Text(pDX, IDC_ADD_EDT_MEMO, m_strMemo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddView, CFormView)
	//{{AFX_MSG_MAP(CAddView)
	ON_BN_CLICKED(IDC_ADD_BTN_ADD, OnAddBtnAdd)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddView diagnostics

#ifdef _DEBUG
void CAddView::AssertValid() const
{
	CFormView::AssertValid();
}

void CAddView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAddView message handlers

void CAddView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	// 使框架窗口大小与视图匹配
	GetParentFrame()->RecalcLayout();
    ResizeParentToFit(FALSE);

	GetParentFrame()->SetWindowText("增加新员工"); // 设置标题

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
    m_brush.CreateSolidBrush(RGB(0,150,200));
	Init(); // 调用初始化函数
}

void CAddView::OnAddBtnAdd() 
{
	CString str,strSQL;
	int counter; // 用于计数
	CRecordset rs(&db); // 数据集

	UpdateData(); // 更新数据
	if(m_strName.IsEmpty()) // 姓名为空则返回
	{
		AfxMessageBox("姓名不能为空!");
		return;
	}

// 累加员工编号计数器
	rs.Open(CRecordset::forwardOnly,
		"select COUNTER_VALUE from COUNTER where ID='P'");
	rs.GetFieldValue("COUNTER_VALUE", str);
	sscanf(str, "%d", &counter); // 获取计数值
	rs.Close(); // 关闭数据集
	counter++;	// 计数值加1
	str.Format("%d", counter); // 转换为字符串
	strSQL="update COUNTER set COUNTER_VALUE=" + str + " where  ID='P'"; // 设置SQL语句
	db.ExecuteSQL(strSQL); // 执行
// 增加员工个人信息记录
	CString strPasswd,strSex,strDepID,strJobID,strEduID;
	// 判断生日是否为空
	if(m_strBirthday.IsEmpty()) m_strBirthday="1900-1-1"; // 缺省值
	// 加密密码
	strPasswd=CCrypt::Encrypt(m_strPasswd, 123);
	// 判断性别
	if(((CButton*)GetDlgItem(IDC_ADD_RADIO_MALE))->GetCheck()) strSex="M";
	else strSex="F";
	// 得到部门ID
	rs.Open(CRecordset::forwardOnly,
		"select ID from DEPARTMENT where NAME='" + m_strDepartment +"'");
	rs.GetFieldValue("ID", strDepID);
	rs.Close();
	// 得到职务代码
	rs.Open(CRecordset::forwardOnly,
		"select CODE from JOB where DESCRIPTION='" + m_strJob +"'");
	rs.GetFieldValue("CODE", strJobID);
	rs.Close();
	// 得到受教育水平代码
	rs.Open(CRecordset::forwardOnly,
		"select CODE from EDU_LEVEL where DESCRIPTION='" + m_strEdulevel +"'");
	rs.GetFieldValue("CODE", strEduID);
	rs.Close();
	// 写SQL语句
	strSQL="insert into PERSON(ID,PASSWD,NAME,SEX,\
		BIRTHDAY,DEPARTMENT,JOB,EDU_LEVEL,SPECIALTY,\
		ADDRESS,TEL,EMAIL,REMARK) \
		values('"
		+ m_strID + "','" // ID
		+ strPasswd + "','" // PASSWD
		+ m_strName + "','" // NAME
		+ strSex + "','" // SEX
		+ m_strBirthday + "','" // BIRTHDAY
		+ strDepID + "','" // DEPARTMENT
		+ strJobID + "','" // JOB
		+ strEduID + "','" // EDU_LEVEL
		+ m_strSpecialty + "','" // SPECIALTY
		+ m_strAddress + "','" // ADDRESS
		+ m_strTel + "','" // TEL
		+ m_strEmail + "','" // EMAIL
		+ m_strMemo + "')"; // REMARK
	db.ExecuteSQL(strSQL); // 执行
// 获取人事变动记录号并累加
	rs.Open(CRecordset::forwardOnly,
		"select COUNTER_VALUE from COUNTER where ID='C'");
	rs.GetFieldValue("COUNTER_VALUE", str);
	sscanf(str, "%d", &counter); // 获取计数值
	rs.Close(); // 关闭数据集
	counter++;	//计数值加1
	str.Format("%d", counter); // 转换为字符串
	strSQL="update COUNTER set COUNTER_VALUE=" + str + " where  ID='C'"; // 设置SQL语句
	db.ExecuteSQL(strSQL); // 执行
// 追加人事变动记录
	str.Format("%d",counter); // 计数值转换为字符串
	CTime time=CTime::GetCurrentTime();
	CString strNow=time.Format("%Y-%m-%d %H:%M:%S");
	// 写SQL语句
	strSQL="insert into zhaoliang(ID,PERSON,CHANGE,\
		RECORD_TIME,DESCRIPTION)\
		values("
		+ str + ",'" // ID
		+ m_strID + "','" // PERSON
		+ "0" + "','" // CHANGE - 加入公司代码
		+ strNow + "','" // RECORD_TIME
		+ "加入公司')"; // DESCRIPTION
	db.ExecuteSQL(strSQL);

// 重新初始化窗口
	Init();
}

void CAddView::Init()
{
	// 清空成员变量
	m_strID = _T("");
	m_strPasswd = _T("");
	m_strName = _T("");
	m_strBirthday = _T("");
	m_strDepartment = _T("");
	m_cDepartment.SetCurSel(-1);
	m_strJob = _T("");
	m_cJob.SetCurSel(-1);
	m_strEdulevel = _T("");
	m_cEdulevel.SetCurSel(-1);
	m_strSpecialty = _T("");
	m_strAddress = _T("");
	m_strTel = _T("");
	m_strEmail = _T("");
	m_strMemo = _T("");

	// 生成员工号
	CString str;
	int counter; // 用于计数
	CRecordset rs(&db); // 数据集
	rs.Open(CRecordset::forwardOnly,
		"select COUNTER_VALUE from COUNTER where ID='P'");
	rs.GetFieldValue("COUNTER_VALUE", str);
	sscanf(str, "%d", &counter); // 获取计数值
	rs.Close();
	str.Format("P%05d", counter); // 产生标准格式的编号
	m_strID=str; // 自动产生员工号
	m_strPasswd=str; // 默认密码为员工号

	// 设置缺省性别为男
	((CButton*)GetDlgItem(IDC_ADD_RADIO_MALE))->SetCheck(TRUE);

	UpdateData(FALSE); // 更新界面数据
}

void CAddView::OnDestroy() 
{
	CFormView::OnDestroy();
	
	((CMainFrame*)AfxGetMainWnd())->m_bItemAdd=TRUE; // 开放"增加新员工"功能
	((CMainFrame*)AfxGetMainWnd())->m_pAdd=NULL; // 清空窗口指针
}

HBRUSH CAddView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
