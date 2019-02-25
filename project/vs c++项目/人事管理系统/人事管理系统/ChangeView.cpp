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
	
	// ʹ��ܴ��ڴ�С����ͼƥ��
	GetParentFrame()->RecalcLayout();
    ResizeParentToFit(FALSE);

	GetParentFrame()->SetWindowText("���±䶯"); // ���ñ���

	CRecordset rs(&db); // ���ݼ�
	CString str;
	// ���ò�����������ȡ��ֵΪDEPARTMENT���е�ֵ
	rs.Open(CRecordset::forwardOnly, "select NAME from DEPARTMENT");
	while(!rs.IsEOF())
	{
		rs.GetFieldValue("NAME", str);
		m_cDepartment.AddString(str);
		rs.MoveNext();
	}
	rs.Close();

	// ����ְ����������ȡ��ֵΪJOB���е�ֵ
	rs.Open(CRecordset::forwardOnly, "select DESCRIPTION from JOB");
	while(!rs.IsEOF())
	{
		rs.GetFieldValue("DESCRIPTION", str);
		m_cJob.AddString(str);
		rs.MoveNext();
	}
	rs.Close();
    m_brush.CreateSolidBrush(RGB(0,150,200));
	Init(); // ���ó�ʼ������
}

void CChangeView::OnDestroy() 
{
	CFormView::OnDestroy();
	
	((CMainFrame*)AfxGetMainWnd())->m_bItemChange=TRUE; // ����"���±䶯"����"
	((CMainFrame*)AfxGetMainWnd())->m_pChange=NULL; // ��մ���ָ��
}

void CChangeView::Init()
{
	// ��ʼ����Ա����
	m_strID = _T("");
	m_Time = CTime::GetCurrentTime();
	m_strName = _T("");
	m_strDescription = _T("");
	m_cDepartment.SetCurSel(-1);
	m_cJob.SetCurSel(-1);

	// ����ȱʡ�䶯���Ϊְ����
	((CButton*)GetDlgItem(IDC_CHANGE_RADIO_JOB))->SetCheck(TRUE);

	UpdateData(FALSE); // ���½�������
}

void CChangeView::OnChangeChangeEdtId() 
{
	UpdateData(); // ��������

	CRecordset rs(&db);
	CString strDep,strJob;

	rs.Open(CRecordset::forwardOnly,
		"select NAME,DEPARTMENT,JOB from PERSON where ID='" + m_strID + "'");
	if(!rs.IsEOF()) // �ǿ����ȡԱ����Ϣ
	{
		rs.GetFieldValue("NAME", m_strName); // ����
		rs.GetFieldValue("DEPARTMENT", strDep); // ���ű��
		rs.GetFieldValue("JOB", strJob); // ְ�����
		rs.Close();
		if(!strDep.IsEmpty())
		{
			rs.Open(CRecordset::forwardOnly,
				"select NAME from DEPARTMENT where ID='" + strDep + "'");
			rs.GetFieldValue("NAME", strDep); // ��������
			rs.Close();
		}
		if(!strJob.IsEmpty())
		{
			rs.Open(CRecordset::forwardOnly,
				"select DESCRIPTION from JOB where CODE='" + strJob + "'");
			rs.GetFieldValue("DESCRIPTION", strJob); // ְ������
			rs.Close();
		}
		UpdateData(FALSE); // ��������

		m_cDepartment.SelectString(-1,strDep);
		m_cJob.SelectString(-1,strJob);

		m_bExist=TRUE; // ��Ա������
	}
	else // �������Ա����Ϣ
	{
		rs.Close();
		m_strName.Empty();
		m_cDepartment.SetCurSel(-1);
		m_cJob.SetCurSel(-1);
		UpdateData(FALSE); // ��������

		m_bExist=FALSE; // ��Ա��������
	}
}

void CChangeView::OnChangeBtnChange() 
{
	CRecordset rs(&db);
	CString str,strSQL;
	int counter;

	if(!m_bExist) // ��Ա���Ų�����
	{
		MessageBox("��ȷ��Ա����!","�������");
		return;
	}
	UpdateData(); // ��������

// ��ȡ���±䶯��¼�Ų��ۼ�
	rs.Open(CRecordset::forwardOnly,
		"select COUNTER_VALUE from COUNTER where ID='C'");
	rs.GetFieldValue("COUNTER_VALUE", str);
	sscanf(str, "%d", &counter); // ��ȡ����ֵ
	rs.Close(); // �ر����ݼ�
	counter++;  // ��������1
	str.Format("%d", counter); // ת��Ϊ�ַ���
	strSQL="update COUNTER set COUNTER_VALUE=" + str + " where  ID='C'"; // ����SQL���
	db.ExecuteSQL(strSQL); // ִ��
// ����Ա����Ϣ
	CString strDepID,strJobID,strState,strChange;

	// �õ�����ID
	m_cDepartment.GetWindowText(str);
	rs.Open(CRecordset::forwardOnly,
		"select ID from DEPARTMENT where NAME='" + str +"'");
	rs.GetFieldValue("ID", strDepID);
	rs.Close();
	// �õ�ְ�����
	m_cJob.GetWindowText(str);
	rs.Open(CRecordset::forwardOnly,
		"select CODE from JOB where DESCRIPTION='" + str +"'");
	rs.GetFieldValue("CODE", strJobID);
	rs.Close();
	
	if(((CButton*)GetDlgItem(IDC_CHANGE_RADIO_FIRE))->GetCheck())
	{
		strState="F";
		strChange="2"; // ����
	}
	else
	{
		strState="T";
		strChange="1"; // ְ��䶯
	}
	strSQL="update PERSON set STATE='" + strState + "',"
		+ "DEPARTMENT='" + strDepID + "',"
		+ "JOB='" + strJobID + "'";
	db.ExecuteSQL(strSQL); // ִ��
// ׷�����±䶯��¼
	str.Format("%d",counter); // ����ֵת��Ϊ�ַ���
	CString strNow=m_Time.Format("%Y-%m-%d %H:%M:%S");
	// дSQL���
	strSQL="insert into zhaoliang(ID,PERSON,CHANGE,RECORD_TIME,DESCRIPTION)\
		values("
		+ str + ",'" // ID
		+ m_strID + "','" // PERSON
		+ strChange + "','" // CHANGE
		+ strNow + "','" // RECORD_TIME
		+ m_strDescription + "')"; // DESCRIPTION
	db.ExecuteSQL(strSQL);

// ���³�ʼ������
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
