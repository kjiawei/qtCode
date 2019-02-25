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
	
	// ��m_cList��������
	DWORD style=m_cList.GetExtendedStyle();
	m_cList.SetExtendedStyle(style|LVS_EX_GRIDLINES);
	// ʹ��ܴ��ڴ�С����ͼƥ��
	GetParentFrame()->RecalcLayout();
    ResizeParentToFit(FALSE);

	GetParentFrame()->SetWindowText("Ա����Ϣ��ѯ�޸�"); // ���ñ���

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

	// ���List�ؼ�����
	m_cList.InsertColumn(0, "��¼���", LVCFMT_LEFT, 100);
	m_cList.InsertColumn(1, "��¼ʱ��", LVCFMT_LEFT, 100);
	m_cList.InsertColumn(2, "��������", LVCFMT_LEFT, 215);
    m_brush.CreateSolidBrush(RGB(0,150,200));
	Init(); // ���ó�ʼ������
}

void CSearchView::OnDestroy() 
{
	CFormView::OnDestroy();
	
	((CMainFrame*)AfxGetMainWnd())->m_bItemSearch=TRUE; // ����"��ѯ�޸�"����"
	((CMainFrame*)AfxGetMainWnd())->m_pSearch=NULL; // ��մ���ָ��
}

void CSearchView::Init()
{
	// ��ճ�Ա����
	m_strID = _T("");
	m_strSpecialty = _T("");
	m_strMemo = _T("");
	m_strPasswd = _T("");
	m_strName = _T("");
	m_strBirthday = _T("");
	m_strAddress = _T("");
	m_strTel = _T("");
	m_strEmail = _T("");

	UpdateData(FALSE); // ���½�������
}

void CSearchView::OnChangeSearchEdtId() 
{
	UpdateData(); // ��������
	m_cList.DeleteAllItems(); // ����б��

	CRecordset rs(&db);
	CString strDep,strJob,strEdulevel,strSex;

	rs.Open(CRecordset::forwardOnly,
		"select NAME,DEPARTMENT,JOB,EDU_LEVEL,SPECIALTY,REMARK,BIRTHDAY,ADDRESS,TEL,EMAIL,SEX from PERSON where ID='" + m_strID + "'");
	if(!rs.IsEOF()) // �ǿ����ȡԱ����Ϣ
	{
		rs.GetFieldValue("NAME", m_strName); // ����
		rs.GetFieldValue("DEPARTMENT", strDep); // ���ű��
		rs.GetFieldValue("JOB", strJob); // ְ�����
		rs.GetFieldValue("EDU_LEVEL", strEdulevel); // �ܽ���ˮƽ
		rs.GetFieldValue("SPECIALTY", m_strSpecialty); // רҵ
		rs.GetFieldValue("REMARK", m_strMemo); // ��ע
		rs.GetFieldValue("BIRTHDAY", m_strBirthday); // ����
		m_strBirthday=m_strBirthday.Left(10); // ȡ���ڲ���
		rs.GetFieldValue("ADDRESS", m_strAddress); // סַ
		rs.GetFieldValue("TEL", m_strTel); // �绰
		rs.GetFieldValue("EMAIL", m_strEmail); // Email
		rs.GetFieldValue("SEX", strSex); // �Ա�
		rs.Close();

		// �õ���������
		if(!strDep.IsEmpty())
		{
			rs.Open(CRecordset::forwardOnly,
				"select NAME from DEPARTMENT where ID='" + strDep + "'");
			rs.GetFieldValue("NAME", strDep); // ��������
			rs.Close();
		}
		// �õ�ְ������
		if(!strJob.IsEmpty())
		{
			rs.Open(CRecordset::forwardOnly,
				"select DESCRIPTION from JOB where CODE='" + strJob + "'");
			rs.GetFieldValue("DESCRIPTION", strJob); // ְ������
			rs.Close();
		}
		// �õ�����ˮƽ����
		if(!strEdulevel.IsEmpty())
		{
			rs.Open(CRecordset::forwardOnly,
				"select DESCRIPTION from EDU_LEVEL where CODE='"
				+ strEdulevel + "'");
			rs.GetFieldValue("DESCRIPTION", strEdulevel); // ����ˮƽ����
			rs.Close();
		}
		// �����Ա�ѡ��
		if(strSex=="M") ((CButton*)GetDlgItem(IDC_SEARCH_RADIO_MALE))->SetCheck(TRUE);
		else ((CButton*)GetDlgItem(IDC_SEARCH_RADIO_FEMALE))
			->SetCheck(TRUE);
		UpdateData(FALSE); // ��������

		m_cDepartment.SelectString(-1,strDep);
		m_cJob.SelectString(-1,strJob);
		m_cEdulevel.SelectString(-1,strEdulevel);

		// �����б������
		int i=0;
		CString str1,str2,str3;
		rs.Open(CRecordset::forwardOnly,
			"select ID,RECORD_TIME,DESCRIPTION from zhaoliang\
			where PERSON='" + m_strID + "'");
		while(!rs.IsEOF())
		{
			// �õ�����
			rs.GetFieldValue("ID", str1);
			rs.GetFieldValue("RECORD_TIME", str2);
			str2=str2.Left(10); // ֻȡ����
			rs.GetFieldValue("DESCRIPTION", str3);
			// ����List
			m_cList.InsertItem(i,"");
			m_cList.SetItemText(i, 0, str1);
			m_cList.SetItemText(i, 1, str2);
			m_cList.SetItemText(i, 2, str3);
			i++;
			rs.MoveNext(); // �ƶ���¼
		}
		rs.Close();

		m_bExist=TRUE; // ��Ա������
	}
	else // �������Ա����Ϣ
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
		UpdateData(FALSE); // ��������
		((CButton*)GetDlgItem(IDC_SEARCH_RADIO_MALE))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_SEARCH_RADIO_FEMALE))->SetCheck(FALSE);

		m_bExist=FALSE; // ��Ա��������
	}
}

void CSearchView::OnSearchBtnChgpasswd() 
{
	if(!m_bExist) // ��Ա���Ų�����
	{
		AfxMessageBox("��Ա���Ų�����");
		return;
	}
	UpdateData(); // ��������

	CString str,strSQL;

	str=CCrypt::Encrypt(m_strPasswd, 123); // ����
	strSQL="update PERSON set PASSWD='" + str + "'"; // дSQL���
	db.ExecuteSQL(strSQL); // ִ��
}

void CSearchView::OnSearchBtnChange() 
{
	if(!m_bExist) // ��Ա���Ų�����
	{
		AfxMessageBox("��Ա���Ų�����");
		return;
	}
	UpdateData(); // ��������

// �޸�Ա��������Ϣ��¼
	CString str,strSex,strDepID,strJobID,strEduID,strSQL;
	CRecordset rs(&db);

	// �ж��Ա�
	if(((CButton*)GetDlgItem(IDC_SEARCH_RADIO_MALE))->GetCheck()) strSex="M";
	else strSex="F";
	// �õ�����ID
	m_cDepartment.GetWindowText(str);
	if(!str.IsEmpty()) // ����
	{
		rs.Open(CRecordset::forwardOnly,
			"select ID from DEPARTMENT where NAME='" + str +"'");
		rs.GetFieldValue("ID", strDepID);
		rs.Close();
	}	
	// �õ�ְ�����
	m_cJob.GetWindowText(str);
	if(!str.IsEmpty()) // ����
	{
		rs.Open(CRecordset::forwardOnly,
			"select CODE from JOB where DESCRIPTION='" + str +"'");
		rs.GetFieldValue("CODE", strJobID);
		rs.Close();
	}
	// �õ��ܽ���ˮƽ����
	m_cEdulevel.GetWindowText(str);
	if(!str.IsEmpty()) // ����
	{
		rs.Open(CRecordset::forwardOnly,
			"select CODE from EDU_LEVEL where DESCRIPTION='" + str +"'");
		rs.GetFieldValue("CODE", strEduID);
		rs.Close();
	}
	// дSQL���
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
		+ "' where ID='" + m_strID + "'"; // ����
	db.ExecuteSQL(strSQL); // ִ��
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
