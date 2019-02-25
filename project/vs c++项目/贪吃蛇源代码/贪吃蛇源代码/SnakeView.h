// SnakeView.h : interface of the CSnakeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAKEVIEW_H__2EBD7F0C_452B_11D7_B6CA_0050BAE90E03__INCLUDED_)
#define AFX_SNAKEVIEW_H__2EBD7F0C_452B_11D7_B6CA_0050BAE90E03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IGraphicOut.h"
#include "IActionHandler.h"

class CSnakeView : public CView, public IGraphicOut
{
protected: // create from serialization only
    CSnakeView();
    DECLARE_DYNCREATE(CSnakeView)

// Attributes
public:
    CSnakeDoc* GetDocument();

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSnakeView)
    public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void OnInitialUpdate();
    protected:
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
    //}}AFX_VIRTUAL

// Implementation
public:
    void scoreBoard(char *scoreMessages);
	void close();
	void redraw();
    void SetActionHandler(IActionHandler *pHandler);

    void setDisplaySize(int width, int height);
    void drawScore(int score);
    void drawVertWall(int x, int y1, int y2);
    void drawHorzWall(int x1, int x2, int y);
    void drawFood(int type, int x, int y);
    void drawBody(int x, int y);
    void drawHead(int type, int x, int y);

    virtual ~CSnakeView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

private:
	void closeWindow();

// Generated message map functions
protected:
    //{{AFX_MSG(CSnakeView)
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnPaint();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChangeLevel();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
	UINT m_wTimerRes;
	int m_timerID;
    IActionHandler * m_pActionHandler;
    void drawSprite(CDC *pDC, int resID, int ix, int iy);
    CSize m_sizeDB;
    CBitmap * m_pBmpDB;
    CDC * m_pDCMemDB;
    int m_numCellsY;
    int m_numCellsX;

    friend void CALLBACK myTimerCallback(UINT wTimerID, 
                                         UINT msg, 
                                         DWORD dwUser, 
                                         DWORD dw1, 
                                         DWORD dw2);
};

#ifndef _DEBUG  // debug version in SnakeView.cpp
inline CSnakeDoc* CSnakeView::GetDocument()
   { return (CSnakeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SNAKEVIEW_H__2EBD7F0C_452B_11D7_B6CA_0050BAE90E03__INCLUDED_)
