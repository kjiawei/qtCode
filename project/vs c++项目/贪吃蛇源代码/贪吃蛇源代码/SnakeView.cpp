// SnakeView.cpp : implementation of the CSnakeView class
//

#include "stdafx.h"
#include "Snake.h"

#include "MainFrm.h"
#include "SnakeDoc.h"
#include "SnakeView.h"

#include "ScoreBoardDlg.h"
#include "ChangeSpeedDlg.h"

#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDT_TIMER 1000
/////////////////////////////////////////////////////////////////////////////
// CSnakeView

IMPLEMENT_DYNCREATE(CSnakeView, CView)

BEGIN_MESSAGE_MAP(CSnakeView, CView)
    //{{AFX_MSG_MAP(CSnakeView)
    ON_WM_SIZE()
    ON_WM_PAINT()
	ON_WM_CONTEXTMENU()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_CLOSE()
	ON_COMMAND(IDM_CHANGELEVEL, OnChangeLevel)
	//}}AFX_MSG_MAP
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSnakeView construction/destruction

CSnakeView::CSnakeView()
    : m_pDCMemDB(0),
      m_pBmpDB(0),
      m_pActionHandler(0),
      m_numCellsX(10),
      m_numCellsY(10),
      m_timerID(0)
{
}

CSnakeView::~CSnakeView()
{
    if (m_pDCMemDB)
        delete m_pDCMemDB;
    if (m_pBmpDB)
        delete m_pBmpDB;
    if (m_pActionHandler)
        delete m_pActionHandler;
}

BOOL CSnakeView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSnakeView drawing

void CSnakeView::OnDraw(CDC* pDC)
{
    CSnakeDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    m_pDC = pDC;

    CRect rect;
    GetClientRect(&rect);

//  draw boundary

    CBitmap bmpBrick;
    bmpBrick.LoadBitmap(IDB_BRICK);
    CBrush brBrick;
    brBrick.CreatePatternBrush(&bmpBrick);
    CBrush *pBrOld = pDC->SelectObject(&brBrick);
    pDC->PatBlt(rect.left, rect.top,
                rect.Width(), rect.Height(),
                PATCOPY);
    pDC->SelectObject(pBrOld);

//  draw interior field

    CBitmap bmpCell;
    bmpCell.LoadBitmap(IDB_CELL);
    CBrush brCell;
    brCell.CreatePatternBrush(&bmpCell);
    pBrOld = pDC->SelectObject(&brCell);
    pDC->PatBlt(rect.left+32, rect.top+32+32,
                rect.Width()-64, rect.Height()-64-32,
                PATCOPY);
    pDC->SelectObject(pBrOld);

//  draw scoreboard

    drawSprite(pDC, IDB_SCOREBOARD, 
               (int)((m_numCellsX-9)/2.0+1)*32, 5);

    pDC->SetBkMode(TRANSPARENT);
    pDC->TextOut((int)((m_numCellsX-9)/2.0+2)*32, 16, 
                 "Scores:");

//  draw all game components

    if (m_pActionHandler)
        m_pActionHandler->draw();

    m_pDC = 0;
}

/////////////////////////////////////////////////////////////////////////////
// CSnakeView printing

BOOL CSnakeView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

void CSnakeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CSnakeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSnakeView diagnostics

#ifdef _DEBUG
void CSnakeView::AssertValid() const
{
    CView::AssertValid();
}

void CSnakeView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CSnakeDoc* CSnakeView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSnakeDoc)));
    return (CSnakeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSnakeView message handlers

void CSnakeView::OnInitialUpdate() 
{
    CView::OnInitialUpdate();
    
    CClientDC dcClient(this);
    OnPrepareDC(&dcClient);

    m_pDCMemDB = new CDC;
    m_pDCMemDB->CreateCompatibleDC(&dcClient);
    m_pDCMemDB->SetMapMode(dcClient.GetMapMode());
}

void CSnakeView::OnSize(UINT nType, int cx, int cy) 
{
    CView::OnSize(nType, cx, cy);
    
    CRect rect;
    GetClientRect(&rect); // device coordinates
                          // API without DC as arguments, 
                          // always use device coordinates

    if ((rect.right <= m_sizeDB.cx) &&
        (rect.bottom <= m_sizeDB.cy)) return;

    if (rect.right > m_sizeDB.cx)
        m_sizeDB.cx = rect.right;

    if (rect.bottom > m_sizeDB.cy)
        m_sizeDB.cy = rect.bottom;

    CClientDC dcClient(this);
    OnPrepareDC(&dcClient); // order dependency: after adjustScrollSizes()

    if (m_pBmpDB) delete m_pBmpDB;
    m_pBmpDB = new CBitmap;
    m_pBmpDB->CreateCompatibleBitmap(&dcClient, m_sizeDB.cx, m_sizeDB.cy);
}

void CSnakeView::OnPaint() 
{
    CPaintDC dc(this); // device context for painting
    
    OnPrepareDC(&dc);

    CBitmap *pBmpOld = m_pDCMemDB->SelectObject(m_pBmpDB);

    CRect rectInvalid;
    dc.GetClipBox(&rectInvalid); // logical coordinate

    m_pDCMemDB->SelectClipRgn(NULL);
    m_pDCMemDB->IntersectClipRect(&rectInvalid);

/*
    CBrush brBackground((COLORREF)::GetSysColor(COLOR_WINDOW));
    CBrush *pBrOld = m_pDCMemDB->SelectObject(&brBackground);
    m_pDCMemDB->PatBlt(rectInvalid.left, rectInvalid.top,
                       rectInvalid.Width(), rectInvalid.Height(),
                       PATCOPY);
    m_pDCMemDB->SelectObject(pBrOld);
*/

    OnDraw(m_pDCMemDB);

    dc.BitBlt(rectInvalid.left, rectInvalid.top,
              rectInvalid.Width(), rectInvalid.Height(),
              m_pDCMemDB, // MM_TEXT mode
              rectInvalid.left, rectInvalid.top,
              SRCCOPY);

    m_pDCMemDB->SelectObject(pBmpOld);
}

void CSnakeView::drawSprite(CDC *pDC, int resID, 
                            int ix, int iy)
{
    BITMAP bmpInfo;
    CSize  sizeBmp;
    CDC dcMem1, dcMem2;

    dcMem1.CreateCompatibleDC(pDC);
    dcMem2.CreateCompatibleDC(pDC);

    //  Step 1
//  create mask step 1: XOR the specified color

    CBitmap bmpSprite;
    bmpSprite.LoadBitmap(resID);
    bmpSprite.GetBitmap(&bmpInfo);
    sizeBmp = CSize(bmpInfo.bmWidth, bmpInfo.bmHeight);

    CBitmap bmpMask1;
    bmpMask1.CreateCompatibleBitmap(pDC, bmpInfo.bmWidth, bmpInfo.bmHeight);

    CBitmap *pOldBmp1 = (CBitmap *)dcMem1.SelectObject(&bmpMask1);

    CPen *pPen = (CPen *) dcMem1.SelectStockObject(NULL_PEN);
    CBrush br(RGB(131,0,0));
    CBrush *pBr = (CBrush *)dcMem1.SelectObject(&br);
    dcMem1.Rectangle(0,0,bmpInfo.bmWidth+1, bmpInfo.bmHeight+1);
    dcMem1.SelectObject(pBr);
    dcMem1.SelectObject(pPen);

    CBitmap *pOldBmp2 = (CBitmap *)dcMem2.SelectObject(&bmpSprite);

// transparent color will now be black

    dcMem1.SetMapMode(MM_TEXT); dcMem2.SetMapMode(MM_TEXT);
    dcMem1.BitBlt(0, 0,
                  bmpInfo.bmWidth, bmpInfo.bmHeight,
                  &dcMem2,
                  0, 0, SRCINVERT);
    dcMem1.SelectObject(pOldBmp1);
    dcMem2.SelectObject(pOldBmp2);

//  Step 2
//  create mask step 2: make transparent color region white

    CBitmap bmpMask2;
    bmpMask2.CreateCompatibleBitmap(pDC, bmpInfo.bmWidth, bmpInfo.bmHeight);
    pOldBmp2 = (CBitmap *)dcMem2.SelectObject(&bmpMask2);

    pOldBmp1 = (CBitmap *)dcMem1.SelectObject(&bmpMask1);
    dcMem1.SetMapMode(MM_TEXT); dcMem2.SetMapMode(MM_TEXT);
    dcMem2.BitBlt(0, 0,
                  bmpInfo.bmWidth, bmpInfo.bmHeight,
                  &dcMem1,
                  0, 0, NOTSRCCOPY);
    dcMem1.SelectObject(pOldBmp1);
    dcMem2.SelectObject(pOldBmp2);

//  Step 3
//  create mask step 3: copy to Black-white bitmap so that
//                      nontransparent color region is black

    CBitmap bmpBW1;
    bmpBW1.CreateBitmap(bmpInfo.bmWidth, bmpInfo.bmHeight,1,1,0);
    pOldBmp1 = (CBitmap *)dcMem1.SelectObject(&bmpBW1);
    pOldBmp2 = (CBitmap *)dcMem2.SelectObject(&bmpMask2);
    dcMem1.SetMapMode(MM_TEXT); dcMem2.SetMapMode(MM_TEXT);
    dcMem1.BitBlt(0, 0,
                  bmpInfo.bmWidth, bmpInfo.bmHeight,
                  &dcMem2,
                  0, 0, SRCCOPY);
    dcMem1.SelectObject(pOldBmp1);
    dcMem2.SelectObject(pOldBmp2);

/*
// view the mask
    dcMemMaskBW.SetMapMode(MM_LOENGLISH);
    pOldBmp1 = (CBitmap *)dcMem1.SelectObject(&bmpBW1);
    pDC->BitBlt(m_ptMouse.x-sizeBmp.cx/2, m_ptMouse.y-sizeBmp.cy/2, 
                sizeBmp.cx, sizeBmp.cy, 
                &dcMem1, // MM_LOENGLISH mode
                0, 0, SRCCOPY);
    dcMem1.SelectObject(pOldBmp1);
*/

//  Step 4
//  cut off the sprite from the background

    bmpBW1.GetBitmap(&bmpInfo);
    sizeBmp = CSize(bmpInfo.bmWidth, bmpInfo.bmHeight);

    // both DC must be in the same mapping mode
//    dcMem1.SetMapMode(MM_LOENGLISH);
    pOldBmp1 = (CBitmap *)dcMem1.SelectObject(&bmpBW1);
    pDC->BitBlt(ix, iy, 
                sizeBmp.cx, sizeBmp.cy, 
                &dcMem1, // MM_LOENGLISH mode
                0, 0, SRCAND);
    dcMem1.SelectObject(pOldBmp1);

//  Step 5
// invert the bit mask

    CBitmap bmpBW2;
    bmpBW2.CreateBitmap(bmpInfo.bmWidth, bmpInfo.bmHeight,1,1,0);
    pOldBmp1 = (CBitmap *)dcMem1.SelectObject(&bmpBW1);
    pOldBmp2 = (CBitmap *)dcMem2.SelectObject(&bmpBW2);
    dcMem1.SetMapMode(MM_TEXT); dcMem2.SetMapMode(MM_TEXT);
    dcMem2.BitBlt(0, 0,
                  bmpInfo.bmWidth, bmpInfo.bmHeight,
                  &dcMem1,
                  0, 0, NOTSRCCOPY);
    dcMem1.SelectObject(pOldBmp1);
    dcMem2.SelectObject(pOldBmp2);

//  Step 6
//  COPY with original then AND with mask

    bmpSprite.GetBitmap(&bmpInfo);
    pOldBmp1 = (CBitmap *)dcMem1.SelectObject(&bmpMask1);
    pOldBmp2 = (CBitmap *)dcMem2.SelectObject(&bmpSprite);
    dcMem1.SetMapMode(MM_TEXT); dcMem2.SetMapMode(MM_TEXT);
    dcMem1.BitBlt(0, 0,
                  bmpInfo.bmWidth, bmpInfo.bmHeight,
                  &dcMem2,
                  0, 0, SRCCOPY);
    dcMem1.SelectObject(pOldBmp1);
    dcMem2.SelectObject(pOldBmp2);

    pOldBmp1 = (CBitmap *)dcMem1.SelectObject(&bmpBW2);
    pOldBmp2 = (CBitmap *)dcMem2.SelectObject(&bmpMask1);
    dcMem1.SetMapMode(MM_TEXT); dcMem2.SetMapMode(MM_TEXT);
    dcMem2.BitBlt(0, 0,
                  bmpInfo.bmWidth, bmpInfo.bmHeight,
                  &dcMem1,
                  0, 0, SRCAND);
    dcMem1.SelectObject(pOldBmp1);
    dcMem2.SelectObject(pOldBmp2);

//  Step 7
//  BitBlt the sprite

    bmpMask1.GetBitmap(&bmpInfo);
    sizeBmp = CSize(bmpInfo.bmWidth, bmpInfo.bmHeight);
//    pDC->DPtoLP(&sizeBmp);

//    dcMem1.SetMapMode(MM_LOENGLISH);
    pOldBmp1 = (CBitmap *)dcMem1.SelectObject(&bmpMask1);
    pDC->BitBlt(ix, iy,
                sizeBmp.cx, sizeBmp.cy, 
                &dcMem1, // MM_LOENGLISH mode
                0, 0, SRCPAINT);
    dcMem1.SelectObject(pOldBmp1);
}

// type IActionHandler::left=0 up=1 right=2 down=3
// leftOpen=10, upOpen=11, rightOpen=12, downOpen=13
void CSnakeView::drawHead(int type, int x, int y)
{
    int xCoord=(x+1)*32;
    int yCoord=(m_numCellsY-y+1)*32;

//    TRACE("type=%d (x=%d,y=%d) pDC=%p\n", type,xCoord,yCoord, m_pDC);
    if (m_pDC)
    {
        switch (type)
        {
        case IActionHandler::left:
            drawSprite(m_pDC, IDB_HEADLEFTCLOSE, xCoord, yCoord);
            break;
        case IActionHandler::leftOpen:
            drawSprite(m_pDC, IDB_HEADLEFTOPEN, xCoord, yCoord);
            break;
        case IActionHandler::up:
            drawSprite(m_pDC, IDB_HEADUPCLOSE, xCoord, yCoord);
            break;
        case IActionHandler::upOpen:
            drawSprite(m_pDC, IDB_HEADUPOPEN, xCoord, yCoord);
            break;
        case IActionHandler::right:
            drawSprite(m_pDC, IDB_HEADRIGHTCLOSE, xCoord, yCoord);
            break;
        case IActionHandler::rightOpen:
            drawSprite(m_pDC, IDB_HEADRIGHTOPEN, xCoord, yCoord);
            break;
        case IActionHandler::down:
            drawSprite(m_pDC, IDB_HEADDOWNCLOSE, xCoord, yCoord);
            break;
        case IActionHandler::downOpen:
            drawSprite(m_pDC, IDB_HEADDOWNOPEN, xCoord, yCoord);
            break;
        }
    }
}

void CSnakeView::drawBody(int x, int y)
{
    if (m_pDC)
        drawSprite(m_pDC, IDB_BODY, 
                   (x+1)*32, (m_numCellsY-y+1)*32);
}

// type: IGraphicOut::fruit=0 flower=1
void CSnakeView::drawFood(int type, int x, int y)
{
    if (m_pDC)
        switch (type)
        {
            case fruit:
                drawSprite(m_pDC, IDB_FRUIT, 
                           (x+1)*32, (m_numCellsY-y+1)*32);
                break;
            case flower:
                drawSprite(m_pDC, IDB_FLOWER, 
                           (x+1)*32, (m_numCellsY-y+1)*32);
                break;
        }
}

void CSnakeView::drawHorzWall(int x1, int x2, int y)
{
    int x1Coord=(x1+1)*32;
    int x2Coord=(x2+1)*32;
    int yCoord=(m_numCellsY-y+1)*32;
    CRect rect(x1Coord, yCoord, x2Coord+32, yCoord+32);
    if (m_pDC)
    {
        CBitmap bmpBrick;
        bmpBrick.LoadBitmap(IDB_BRICK);
        CBrush brBrick;
        brBrick.CreatePatternBrush(&bmpBrick);
        CBrush *pBrOld = m_pDC->SelectObject(&brBrick);
        m_pDC->PatBlt(rect.left, rect.top,
                      rect.Width(), rect.Height(),
                      PATCOPY);
        m_pDC->SelectObject(pBrOld);
    }
}

void CSnakeView::drawVertWall(int x, int y1, int y2)
{
    int xCoord=(x+1)*32;
    int y1Coord=(m_numCellsY-y1+1)*32;
    int y2Coord=(m_numCellsY-y2+1)*32;
    CRect rect(xCoord, y2Coord, xCoord+32, y1Coord+32);
    if (m_pDC)
    {
        CBitmap bmpBrick;
        bmpBrick.LoadBitmap(IDB_BRICK);
        CBrush brBrick;
        brBrick.CreatePatternBrush(&bmpBrick);
        CBrush *pBrOld = m_pDC->SelectObject(&brBrick);
        m_pDC->PatBlt(rect.left, rect.top,
                      rect.Width(), rect.Height(),
                      PATCOPY);
        m_pDC->SelectObject(pBrOld);
    }
}

void CSnakeView::drawScore(int score)
{
    char scoreBuf[100];
    if (m_pDC)
    {
        wsprintf(scoreBuf, "%d", score);
        m_pDC->TextOut((int)((m_numCellsX-9)/2.0+2)*32+70, 16, 
                       scoreBuf);
    }
}

void CSnakeView::setDisplaySize(int width, int height)
{
    m_numCellsX = width;
    m_numCellsY = height;
    ((CMainFrame*)AfxGetMainWnd())->adjustDisplaySize(width, height);
}

void CSnakeView::SetActionHandler(IActionHandler *pHandler)
{
    m_pActionHandler = pHandler;
}

void CSnakeView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
   CMenu menu;
   menu.LoadMenu(IDR_MAINFRAME);
   ASSERT(menu);
   CMenu* menu1 = menu.GetSubMenu(0);    
   ASSERT(menu1);

   menu1->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, 
       point.x, point.y, AfxGetMainWnd());
}

int CSnakeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
//    if (m_timerID == 0)
//        m_timerID = SetTimer(IDT_TIMER, 55, 0);

#define TARGET_RESOLUTION 1         // 1-millisecond target resolution

    TIMECAPS tc;

    if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) 
    {
        // Error; application can't continue.
    }

    m_wTimerRes = min(max(tc.wPeriodMin, TARGET_RESOLUTION), tc.wPeriodMax);
//   TRACE("wTimerRes=%d tc.wPeriodMin=%d tc.wPeriodMax=%d\n", 
//          m_wTimerRes, tc.wPeriodMin, tc.wPeriodMax);
    timeBeginPeriod(m_wTimerRes);

    m_timerID = 
        timeSetEvent(4,                 // delay (ms)
                     m_wTimerRes,       // resolution (global variable)
                     myTimerCallback,   // callback function
                     (DWORD)this,       // user data
                     TIME_PERIODIC );   // single timer event

	return 0;
}

void CALLBACK myTimerCallback(UINT wTimerID, 
                              UINT msg, 
                              DWORD dwUser, 
                              DWORD dw1,
                              DWORD dw2) 
{
    CSnakeView *pView = (CSnakeView *) dwUser;
    if ((UINT)pView->m_timerID == wTimerID)
    {
        if (pView->m_pActionHandler)
            (pView->m_pActionHandler)->timeUp();
    }
} 

void CSnakeView::OnDestroy() 
{
	CView::OnDestroy();

    if (m_timerID) // is timer event pending?
    {
        timeKillEvent(m_timerID);  // cancel the event
        timeEndPeriod(m_wTimerRes);
    }
	
//    if (m_timerID)
//        KillTimer(m_timerID);
}

void CSnakeView::OnTimer(UINT nIDEvent) 
{
//    if (nIDEvent == (UINT)m_timerID)
//        m_pActionHandler->timeUp();

	CView::OnTimer(nIDEvent);
}

void CSnakeView::redraw()
{
    Invalidate(FALSE); // do not clear screen
}

void CSnakeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    switch (nChar)
    {
    case VK_LEFT:
        if (m_pActionHandler)
            m_pActionHandler->leftMove();
        break;
    case VK_RIGHT:
        if (m_pActionHandler)
            m_pActionHandler->rightMove();
        break;
    case VK_UP:
        if (m_pActionHandler)
            m_pActionHandler->upMove();
        break;
    case VK_DOWN:
        if (m_pActionHandler)
            m_pActionHandler->downMove();
        break;
    case VK_ESCAPE:
        close(); // window could be destroyed
        return;
    }
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSnakeView::close() 
{
    if (m_pActionHandler)
    {
        if (m_timerID)
        {
            timeKillEvent(m_timerID);
            timeEndPeriod(m_wTimerRes);
            m_timerID = 0;
        }

        m_pActionHandler->exit();
    }
    closeWindow();
}

void CSnakeView::closeWindow()
{
    AfxGetMainWnd()->DestroyWindow();
}

void CSnakeView::scoreBoard(char *scoreMessages)
{
    CScoreBoardDlg dlg;
    CString messages(scoreMessages);
    messages.Replace("\n", "\r\n");
    dlg.m_scoreBoardMessages = messages;
    dlg.DoModal();
}

void CSnakeView::OnChangeLevel() 
{
    CChangeSpeedDlg dlg;
    dlg.m_speed = m_pActionHandler->getSpeed();
    if (dlg.m_speed<0)
        dlg.m_speed = 0;
    else if (dlg.m_speed > 10)
        dlg.m_speed = 10;
    if (dlg.DoModal()==IDOK)
    {
        m_pActionHandler->changeSpeed(11-dlg.m_speed);
    }
}
