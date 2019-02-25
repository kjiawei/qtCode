// ChangeView.cpp : implementation file
//

#include "stdafx.h"
#include "zhaoliang.h"
#include "ChangeView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDatabase db;
/////////////////////////////////////////////////////////////////////////////
// CChangeView

IMPLEMENT_DYNCREATE(CChangeView, CFormView)

CChangeView::CChangeView()
	: CFormView(CChangeView::IDD)
{
	//{{AFX_DATA_INIT(CChangeView)
	m_strID = _T("");
	m_Time = CTime::GetCurrentTime();
	m_strName = _T("");
	m_strDescription = _T("");
	//}}AFX_DATA_INIT
}

CChangeView::~CChangeView()
{
}

void CChangeView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangeView)
	DDX_Control(pDX, IDC_CHANGE_CMB_JOB, m_cJob);
	DDX_Control(pDX, IDC_CHANGE_CMB_DEPARTMENT, m_cDepartment);
	DDX_Text(pDX, IDC_CHANGE_EDT_ID, m_strID);
	DDX_DateTimeCtrl(pDX, IDC_CHANGE_DATETIMEPICKER, m_Time);
	DDX_Text(pDX, IDC_CHANGE_EDT_NAME, m_strName);
	DDX_Text(pDX, IDC_CHANGE_EDT_DESCRIPTION, m_strDescription);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangeView, CFormView)
	//{{AFX_MSG_MAP(CChangeView)
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_CHANGE_EDT_ID, OnChangeChangeEdtId)
	ON_BN_CLICKED(IDC_CHANGE_BTN_CHANGE, OnChangeBtnChange)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeView diagnostics

#ifdef _DEBUG
void CChangeView::AssertValid() const
{
	CFormView::AssertValid();
}

void CChangeView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChangeView message handlers

void CChangeView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// 使框架窗口大小与视图匹配
	GetParentFrame()->RecalcLayout();
    ResizeParentToFit(FALSE);

	GetParentFrame()->SetWindowText("人事变动"); // 设置标题

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
    m_brush.CreateSolidBrush(RGB(0,150,200));
	Init(); // 调用初始化函数
}

void CChangeView::OnDestroy() 
{
	CFormView::OnDestroy();
	
	((CMainFrame*)AfxGetMainWnd())->m_bItemChange=TRUE; // 开放"人事变动"功能"
	((CMainFrame*)AfxGetMainWnd())->m_pChange=NULL; // 清空窗口指针
}

void CChangeView::Init()
{
	// 初始化成员变量
	m_strID = _T("");
	m_Time = CTime::GetCurrentTime();
	m_strName = _T("");
	m_strDescription = _T("");
	m_cDepartment.SetCurSel(-1);
	m_cJob.SetCurSel(-1);

	// 设置缺省变动情况为职务变更
	((CButton*)GetDlgItem(IDC_CHANGE_RADIO_JOB))->SetCheck(TRUE);

	UpdateData(FALSE); // 更新界面数据
}

void CChangeView::OnChangeChangeEdtId() 
{
	UpdateData(); // 更新数据

	CRecordset rs(&db);
	CString strDep,strJob;

	rs.Open(CRecordset::forwardOnly,
		"select NAME,DEPARTMENT,JOB from PERSON where ID='" + m_strID + "'");
	if(!rs.IsEOF()) // 非空则获取员工信息
	{
		rs.GetFieldValue("NAME", m_strName); // 名字
		rs.GetFieldValue("DEPARTMENT", strDep); // 部门编号
		rs.GetFieldValue("JOB", strJob); // 职务代码
		rs.Close();
		if(!strDep.IsEmpty())
		{
			rs.Open(CRecordset::forwardOnly,
				"select NAME from DEPARTMENT where ID='" + strDep + "'");
			rs.GetFieldValue("NAME", strDep); // 部门名称
			rs.Close();
		}
		if(!strJob.IsEmpty())
		{
			rs.Open(CRecordset::forwardOnly,
				"select DESCRIPTION from JOB where CODE='" + strJob + "'");
			rs.GetFieldValue("DESCRIPTION", strJob); // 职务名称
			rs.Close();
		}
		UpdateData(FALSE); // 更新数据

		m_cDepartment.SelectString(-1,strDep);
		m_cJob.SelectString(-1,strJob);

		m_bExist=TRUE; // 该员工存在
	}
	else // 否则清空员工信息
	{
		rs.Close();
		m_strName.Empty();
		m_cDepartment.SetCurSel(-1);
		m_cJob.SetCurSel(-1);
		UpdateData(FALSE); // 更新数据

		m_bExist=FALSE; // 该员工不存在
	}
}

void CChangeView::OnChangeBtnChange() 
{
	CRecordset rs(&db);
	CString str,strSQL;
	int counter;

	if(!m_bExist) // 该员工号不存在
	{
		MessageBox("请确认员工号!","输入错误");
		return;
	}
	UpdateData(); // 更新数据

// 获取人事变动记录号并累加
	rs.Open(CRecordset::forwardOnly,
		"select COUNTER_VALUE from COUNTER where ID='C'");
	rs.GetFieldValue("COUNTER_VALUE", str);
	sscanf(str, "%d", &counter); // 获取计数值
	rs.Close(); // 关闭数据集
	counter++;  // 计数器加1
	str.Format("%d", counter); // 转换为字符串
	strSQL="update COUNTER set COUNTER_VALUE=" + str + " where  ID='C'"; // 设置SQL语句
	db.ExecuteSQL(strSQL); // 执行
// 更新员工信息
	CString strDepID,strJobID,strState,strChange;

	// 得到部门ID
	m_cDepartment.GetWindowText(str);
	rs.Open(CRecordset::forwardOnly,
		"select ID from DEPARTMENT where NAME='" + str +"'");
	rs.GetFieldValue("ID", strDepID);
	rs.Close();
	// 得到职务代码
	m_cJob.GetWindowText(str);
	rs.Open(CRecordset::forwardOnly,
		"select CODE from JOB where DESCRIPTION='" + str +"'");
	rs.GetFieldValue("CODE", strJobID);
	rs.Close();
	
	if(((CButton*)GetDlgItem(IDC_CHANGE_RADIO_FIRE))->GetCheck())
	{
		strState="F";
		strChange="2"; // 辞退
	}
	else
	{
		strState="T";
		strChange="1"; // 职务变动
	}
	strSQL="update PERSON set STATE='" + strState + "',"
		+ "DEPARTMENT='" + strDepID + "',"
		+ "JOB='" + strJobID + "'";
	db.ExecuteSQL(strSQL); // 执行
// 追加人事变动记录
	str.Format("%d",counter); // 计数值转换为字符串
	CString strNow=m_Time.Format("%Y-%m-%d %H:%M:%S");
	// 写SQL语句
	strSQL="insert into zhaoliang(ID,PERSON,CHANGE,RECORD_TIME,DESCRIPTION)\
		values("
		+ str + ",'" // ID
		+ m_strID + "','" // PERSON
		+ strChange + "','" // CHANGE
		+ strNow + "','" // RECORD_TIME
		+ m_strDescription + "')"; // DESCRIPTION
	db.ExecuteSQL(strSQL);

// 重新初始化窗口
	Init();
}

HBRUSH CChangeView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
