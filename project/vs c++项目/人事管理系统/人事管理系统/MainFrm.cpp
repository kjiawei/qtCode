// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "zhaoliang.h"
#include "LoginDlg.h"
#include "AddView.h"
#include "ChangeView.h"
#include "SearchView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDatabase db;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_SYSTEM_CONNECT, OnSystemConnect)
	ON_WM_DESTROY()
	ON_COMMAND(ID_SYSTEM_DISCONNECT, OnSystemDisconnect)
	ON_UPDATE_COMMAND_UI(ID_SYSTEM_DISCONNECT, OnUpdateSystemDisconnect)
	ON_COMMAND(ID_MANAGE_ADD, OnManageAdd)
	ON_COMMAND(ID_MANAGER_CHANGE, OnManagerChange)
	ON_UPDATE_COMMAND_UI(ID_MANAGE_ADD, OnUpdateManageAdd)
	ON_UPDATE_COMMAND_UI(ID_MANAGER_CHANGE, OnUpdateManagerChange)
	ON_UPDATE_COMMAND_UI(ID_MANAGER_SEARCH, OnUpdateManagerSearch)
	ON_UPDATE_COMMAND_UI(ID_SYSTEM_CONNECT, OnUpdateSystemConnect)
	ON_COMMAND(ID_MANAGER_SEARCH, OnManagerSearch)
	ON_COMMAND(ID_WINDOW_MINIALL, OnWindowMiniall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_LOGIN,		// 登录状态
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bLogin=FALSE; // 缺省未登录
	m_bItemAdd=FALSE; // "增加新员工"功能缺省为不可用
	m_bItemChange=FALSE; // "人事变动"功能缺省为不可用
	m_bItemSearch=FALSE; // "查询修改"功能缺省为不可用

	m_pAdd=m_pChange=m_pSearch=NULL; // 初始化为空
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnDestroy()
{
	CMDIFrameWnd::OnDestroy();
	
	if(db.IsOpen()) db.Close(); // 如数据库未关闭则关闭
}

void CMainFrame::OnSystemConnect() 
{
	CLoginDlg dlg;

	if(dlg.DoModal()==IDOK)
	{
		m_bLogin=TRUE; // 已登录
		m_bItemAdd=TRUE; // 开放"增加新员工"功能
		m_bItemChange=TRUE; // 开放"人事变动"功能
		m_bItemSearch=TRUE; // 开放"查询修改"功能
		// 改变状态栏
		m_wndStatusBar.SetPaneText(1, "已登录到数据库："+dlg.m_strDSN);
	}
}

void CMainFrame::OnSystemDisconnect() 
{
	db.Close(); // 关闭数据库
	// 关闭所有子框架窗口
	if(m_pAdd) m_pAdd->DestroyWindow();
	if(m_pChange) m_pChange->DestroyWindow();
	if(m_pSearch) m_pSearch->DestroyWindow();

	m_bLogin=FALSE; // 未登录
	m_bItemAdd=FALSE; // 禁止"增加新员工"功能
	m_bItemChange=FALSE; // 禁止"人事变动"功能
	m_bItemSearch=FALSE; // 禁止"查询修改"功能
	// 改变状态栏
	m_wndStatusBar.SetPaneText(1, "尚未登录数据库!请按F2登录");
}

void CMainFrame::OnUpdateSystemConnect(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_bLogin); // 根据登录状态改变菜单项和工具栏相应按钮状态
}

void CMainFrame::OnUpdateSystemDisconnect(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bLogin); // 根据登录状态改变菜单项和工具栏相应按钮状态
}

void CMainFrame::OnUpdateManageAdd(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bItemAdd); // 根据m_bItemAdd改变菜单项和工具栏相应按钮状态
}

void CMainFrame::OnUpdateManagerSearch(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bItemSearch); // 根据m_bItemSearch改变菜单项和工具栏相应按钮状态
}

void CMainFrame::OnUpdateManagerChange(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bItemChange); // 根据m_bItemChange改变菜单项和工具栏相应按钮状态
}

void CMainFrame::OnManageAdd() 
{
	// 创建新子框架和视
	m_pAdd = new CTheChildFrame();
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CAddView);
	if(!m_pAdd->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_PREFIXTITLE ,this, &context )) return;
	m_pAdd->InitialUpdateFrame(NULL,TRUE);

	m_bItemAdd=FALSE; // 禁止"增加新员工"功能
}

void CMainFrame::OnManagerChange() 
{
	// 创建新子框架和视
	m_pChange = new CTheChildFrame();
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CChangeView);
	if(!m_pChange->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_PREFIXTITLE ,this, &context )) return;
	m_pChange->InitialUpdateFrame(NULL,TRUE);

	m_bItemChange=FALSE; // 禁止"人事变动"功能
}

void CMainFrame::OnManagerSearch() 
{
	// 创建新子框架和视
	m_pSearch = new CTheChildFrame();
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CSearchView);
	if(!m_pSearch->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_PREFIXTITLE ,this, &context )) return;
	m_pSearch->InitialUpdateFrame(NULL,TRUE);

	m_bItemSearch=FALSE; // 禁止"查询修改"功能
}

void CMainFrame::OnWindowMiniall() 
{
	// 最小化所有窗口
	if(m_pAdd) m_pAdd->ShowWindow(SW_MINIMIZE);
	if(m_pChange) m_pChange->ShowWindow(SW_MINIMIZE);
	if(m_pSearch) m_pSearch->ShowWindow(SW_MINIMIZE);
}
