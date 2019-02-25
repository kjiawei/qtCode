// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Snake.h"
#include "SnakeDoc.h"
#include "SnakeView.h"

#include "MainFrm.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    //{{AFX_MSG_MAP(CMainFrame)
    ON_WM_CREATE()
    ON_WM_SYSCOMMAND()
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
    ID_SEPARATOR,           // status line indicator
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
    // TODO: add member initialization code here
    
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
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

    m_wndToolBar.ShowWindow(SW_HIDE);
    m_wndStatusBar.ShowWindow(SW_HIDE);
    this->SetMenu(0);

    ASSERT((ID_APP_ABOUT & 0xFFF0) == ID_APP_ABOUT);
    ASSERT(ID_APP_ABOUT < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu("程式說明");
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, ID_APP_ABOUT, strAboutMenu);
        }
    }

    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    if( !CFrameWnd::PreCreateWindow(cs) )
        return FALSE;

    cs.style = WS_SYSMENU | WS_MINIMIZEBOX | WS_DLGFRAME;
    cs.cx = (18+2)*32 +
            GetSystemMetrics(SM_CYDLGFRAME)*2 +
            GetSystemMetrics(SM_CYEDGE)*2; // 650
    cs.cy = (13+3)*32 +
            GetSystemMetrics(SM_CYCAPTION) +
            GetSystemMetrics(SM_CYDLGFRAME)*2 +
            GetSystemMetrics(SM_CYEDGE)*2; //511+32;
//TRACE("caption=%d\n", GetSystemMetrics(SM_CYCAPTION));
//TRACE("3D border=%d\n", GetSystemMetrics(SM_CYEDGE));
//TRACE("sizing frame=%d\n", GetSystemMetrics(SM_CYDLGFRAME));
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::adjustDisplaySize(int width, int height)
{
    int cx, cy;
    //TRACE("%d %d\n", cx, cy);
    cx = (width+2)*32 +
         GetSystemMetrics(SM_CYDLGFRAME)*2 +
         GetSystemMetrics(SM_CYEDGE)*2; // 650
    cy = (height+3)*32 +
         GetSystemMetrics(SM_CYCAPTION) +
         GetSystemMetrics(SM_CYDLGFRAME)*2 +
         GetSystemMetrics(SM_CYEDGE)*2; //511+32;
//    TRACE("%d %d\n", cx, cy);
    SetWindowPos(NULL, 0, 0, cx, cy, 
        SWP_NOMOVE | SWP_NOZORDER);
    //RecalcLayout();
}

void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam) 
{
    if ((nID & 0xFFF0) == ID_APP_ABOUT)
    {
        CAboutDlg aboutDlg;
        aboutDlg.DoModal();
    }
    else
        CFrameWnd::OnSysCommand(nID, lParam);
}

void CMainFrame::OnAppExit() 
{
    PostMessage(WM_CLOSE);
}

void CMainFrame::OnAppAbout() 
{
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}

void CMainFrame::OnClose() 
{
    ((CSnakeView *)GetActiveView())->close();
    
//  FrameWnd::OnClose();
}
