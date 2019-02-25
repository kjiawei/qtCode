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

	// ʹ��ܴ��ڴ�С����ͼƥ��
	GetParentFrame()->RecalcLayout();
    ResizeParentToFit(FALSE);

	GetParentFrame()->SetWindowText("������Ա��"); // ���ñ���

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

	// �����ܽ���ˮƽ��������ȡ��ֵΪEDU_LEVEL���е�ֵ
	rs.Open(CRecordset::forwardOnly, "select DESCRIPTION from EDU_LEVEL");
	while(!rs.IsEOF())
	{
		rs.GetFieldValue("DESCRIPTION", str);
		m_cEdulevel.AddString(str);
		rs.MoveNext();
	}
	rs.Close();
    m_brush.CreateSolidBrush(RGB(0,150,200));
	Init(); // ���ó�ʼ������
}

void CAddView::OnAddBtnAdd() 
{
	CString str,strSQL;
	int counter; // ���ڼ���
	CRecordset rs(&db); // ���ݼ�

	UpdateData(); // ��������
	if(m_strName.IsEmpty()) // ����Ϊ���򷵻�
	{
		AfxMessageBox("��������Ϊ��!");
		return;
	}

// �ۼ�Ա����ż�����
	rs.Open(CRecordset::forwardOnly,
		"select COUNTER_VALUE from COUNTER where ID='P'");
	rs.GetFieldValue("COUNTER_VALUE", str);
	sscanf(str, "%d", &counter); // ��ȡ����ֵ
	rs.Close(); // �ر����ݼ�
	counter++;	// ����ֵ��1
	str.Format("%d", counter); // ת��Ϊ�ַ���
	strSQL="update COUNTER set COUNTER_VALUE=" + str + " where  ID='P'"; // ����SQL���
	db.ExecuteSQL(strSQL); // ִ��
// ����Ա��������Ϣ��¼
	CString strPasswd,strSex,strDepID,strJobID,strEduID;
	// �ж������Ƿ�Ϊ��
	if(m_strBirthday.IsEmpty()) m_strBirthday="1900-1-1"; // ȱʡֵ
	// ��������
	strPasswd=CCrypt::Encrypt(m_strPasswd, 123);
	// �ж��Ա�
	if(((CButton*)GetDlgItem(IDC_ADD_RADIO_MALE))->GetCheck()) strSex="M";
	else strSex="F";
	// �õ�����ID
	rs.Open(CRecordset::forwardOnly,
		"select ID from DEPARTMENT where NAME='" + m_strDepartment +"'");
	rs.GetFieldValue("ID", strDepID);
	rs.Close();
	// �õ�ְ�����
	rs.Open(CRecordset::forwardOnly,
		"select CODE from JOB where DESCRIPTION='" + m_strJob +"'");
	rs.GetFieldValue("CODE", strJobID);
	rs.Close();
	// �õ��ܽ���ˮƽ����
	rs.Open(CRecordset::forwardOnly,
		"select CODE from EDU_LEVEL where DESCRIPTION='" + m_strEdulevel +"'");
	rs.GetFieldValue("CODE", strEduID);
	rs.Close();
	// дSQL���
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
	db.ExecuteSQL(strSQL); // ִ��
// ��ȡ���±䶯��¼�Ų��ۼ�
	rs.Open(CRecordset::forwardOnly,
		"select COUNTER_VALUE from COUNTER where ID='C'");
	rs.GetFieldValue("COUNTER_VALUE", str);
	sscanf(str, "%d", &counter); // ��ȡ����ֵ
	rs.Close(); // �ر����ݼ�
	counter++;	//����ֵ��1
	str.Format("%d", counter); // ת��Ϊ�ַ���
	strSQL="update COUNTER set COUNTER_VALUE=" + str + " where  ID='C'"; // ����SQL���
	db.ExecuteSQL(strSQL); // ִ��
// ׷�����±䶯��¼
	str.Format("%d",counter); // ����ֵת��Ϊ�ַ���
	CTime time=CTime::GetCurrentTime();
	CString strNow=time.Format("%Y-%m-%d %H:%M:%S");
	// дSQL���
	strSQL="insert into zhaoliang(ID,PERSON,CHANGE,\
		RECORD_TIME,DESCRIPTION)\
		values("
		+ str + ",'" // ID
		+ m_strID + "','" // PERSON
		+ "0" + "','" // CHANGE - ���빫˾����
		+ strNow + "','" // RECORD_TIME
		+ "���빫˾')"; // DESCRIPTION
	db.ExecuteSQL(strSQL);

// ���³�ʼ������
	Init();
}

void CAddView::Init()
{
	// ��ճ�Ա����
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

	// ����Ա����
	CString str;
	int counter; // ���ڼ���
	CRecordset rs(&db); // ���ݼ�
	rs.Open(CRecordset::forwardOnly,
		"select COUNTER_VALUE from COUNTER where ID='P'");
	rs.GetFieldValue("COUNTER_VALUE", str);
	sscanf(str, "%d", &counter); // ��ȡ����ֵ
	rs.Close();
	str.Format("P%05d", counter); // ������׼��ʽ�ı��
	m_strID=str; // �Զ�����Ա����
	m_strPasswd=str; // Ĭ������ΪԱ����

	// ����ȱʡ�Ա�Ϊ��
	((CButton*)GetDlgItem(IDC_ADD_RADIO_MALE))->SetCheck(TRUE);

	UpdateData(FALSE); // ���½�������
}

void CAddView::OnDestroy() 
{
	CFormView::OnDestroy();
	
	((CMainFrame*)AfxGetMainWnd())->m_bItemAdd=TRUE; // ����"������Ա��"����
	((CMainFrame*)AfxGetMainWnd())->m_pAdd=NULL; // ��մ���ָ��
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
