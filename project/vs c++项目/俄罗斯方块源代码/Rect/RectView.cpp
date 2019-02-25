#include "stdafx.h"
#include "Rect.h"
#include "Matrix.h"
#include "Diamond.h"

#include "RectDoc.h"
#include "RectView.h"

#include <Mmsystem.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRectView
//////////////////////////////////////////////////////////
Matrix win(15, 10);				//界面初始化 15*10 格	//													 	//
static Diamond nextblock;		//保存下一方块的类型	//
static Diamond *block = NULL;							//
static int oldrow = 0;									//
static int oldcol= 0;									//	
static int keyCode = 0;									//			
//////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CRectView, CView)
BEGIN_MESSAGE_MAP(CRectView, CView)
	//{{AFX_MSG_MAP(CRectView)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_GAME_BIGRN, OnMganBigne)
	ON_COMMAND(ID_GAME_EXIT, OnGameExit)
	ON_UPDATE_COMMAND_UI(ID_GAME_BIGRN, OnUpdateGameBigrn)
	ON_COMMAND(ID_GAME_STOP, OnGameStop)
	ON_UPDATE_COMMAND_UI(ID_GAME_STOP, OnUpdateGameStop)
	ON_UPDATE_COMMAND_UI(ID_GAME_EXIT, OnUpdateGameExit)
	ON_COMMAND(ID_GAME_END, OnGameEnd)
	ON_UPDATE_COMMAND_UI(ID_GAME_END, OnUpdateGameEnd)
	ON_COMMAND(ID_SET_GRADE_1, OnSetGrade1)
	ON_UPDATE_COMMAND_UI(ID_SET_GRADE_1, OnUpdateSetGrade1)
	ON_COMMAND(ID_SET_GRADE_2, OnSetGrade2)
	ON_UPDATE_COMMAND_UI(ID_SET_GRADE_2, OnUpdateSetGrade2)
	ON_COMMAND(ID_SET_GRADE_3, OnSetGrade3)
	ON_UPDATE_COMMAND_UI(ID_SET_GRADE_3, OnUpdateSetGrade3)
	ON_COMMAND(ID_SET_GRID, OnSetGrid)
	ON_UPDATE_COMMAND_UI(ID_SET_GRID, OnUpdateSetGrid)
	ON_UPDATE_COMMAND_UI(ID_HELP_MINYAN, OnUpdateHelpMinyan)
	ON_COMMAND(ID_SET_GRADE_0, OnSetGrade0)
	ON_UPDATE_COMMAND_UI(ID_SET_GRADE_0, OnUpdateSetGrade0)
	ON_COMMAND(ID_SET_GRADE_4, OnSetGrade4)
	ON_UPDATE_COMMAND_UI(ID_SET_GRADE_4, OnUpdateSetGrade4)
	ON_COMMAND(ID_SET_MUSIC, OnSetMusic)
	ON_UPDATE_COMMAND_UI(ID_SET_MUSIC, OnUpdateSetMusic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRectView construction/destruction

CRectView::CRectView()
{
	//初始化
	game_begin = false;
	game_end = true;
	game_stop = true;
	game_hasGrid = true;
	game_music = true;
	game_level = 0;
	game_speed = 13;

	OnSetMusic() ;
}

CRectView::~CRectView()
{
}

BOOL CRectView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CRectView drawing

void CRectView::OnDraw(CDC* pDC)
{
	CRectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int x = 2;
	int y = 2;
	int cx = 480;
	int cy = 375;
	win.Draw(pDC, x, y, cx, 431, RGB(0, 0, 0), false, false);
	win.Draw(pDC, x + 15, y + 15, 250, 375, RGB(0, 250, 140), true, true);
}

/////////////////////////////////////////////////////////////////////////////
// CRectView diagnostics

#ifdef _DEBUG
void CRectView::AssertValid() const
{
	CView::AssertValid();
}

void CRectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRectDoc* CRectView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRectDoc)));
	return (CRectDoc*)m_pDocument;
}
#endif //_DEBUG

void CRectView::OnTimer(UINT nIDEvent) 
{

	static int DiamondType = rand() % 11; //得到方快随机类型
	static int col = 0;
	static int row = 0;
	static int con = 0;
	static int key = 0;
	
	win.pDC = GetDC();

	con++, key++;
	if (block == NULL)
	{
		block = new Diamond;
		block->SetDiamond(DiamondType);
		
		win.DrawDiamon(win.pDC, 12 , 2, nextblock, RGB(0, 0, 0));//抹掉nextblock旧方块

		//>>下一方块
		DiamondType = rand() % 11;
		nextblock.SetDiamond(DiamondType);
		win.DrawDiamon(win.pDC, 12, 2, nextblock, block->DiamondColor);//画nextblock方块	
		//<<下一方块

		Print(game_level); //显示级别信息
		col = win.cols / 2; //设置方块默认从中间掉下
		row = 0;
	}
	
	oldcol = col;
	oldrow = row;	
	if (!win.CanDown(*block, col, row) && keyCode != VK_LEFT &&  keyCode != VK_RIGHT && key % 2 == 0)
	{
		win.DrawDiamon(win.pDC, oldcol, oldrow , *block, win.matrixColor);//抹掉旧方块
		win.DrawDiamon(win.pDC, col , row , *block, block->DiamondColor);//画新方块
		
		win.Add (*block, col, row);
		if (win.Tidy()) //整理
		{
			for (int t = 0; t < win.rows; t++)
			{
				for (int j = 0; j < win.cols; j++)
				{
					if (win.gridData[t*win.cols + j] == 1)
						win.Draw(win.pDC, win.winX + (j*win.cellWidth) + 1, win.winY + (t*win.cellHeight) + 1, win.cellWidth - 2, win.cellHeight - 2, block->DiamondColor, false, false);
					else
						win.Draw(win.pDC, win.winX + (j*win.cellWidth) + 1, win.winY + (t*win.cellHeight) + 1, win.cellWidth - 2, win.cellHeight - 2, win.matrixColor, false, false);
				}
			}
			SetLevel(win.newScore ); //设置级别
		}
		
		delete block;
		block = NULL;
		keyCode = 0;
	}
	else
	{
		switch (keyCode)//键盘事件处理
		{
			case VK_SPACE://下落键
				{
					if (win.CanDown(*block, col, row))
						row = row + 1;
					else 	
						keyCode = 0;
					if (win.CanDown(*block, col, row))
							row = row + 1;
					else 	
						keyCode = 0;
					break;
				}
				
			case VK_UP://翻转键
				{
					if (win.CanTrun(*block, col, row))
					{
						win.DrawDiamon(win.pDC, oldcol, oldrow , *block, RGB(0, 250, 140));//抹掉旧方块
						block->Trun();
						keyCode = 99;
					}
					else
						keyCode = 0;
					break;
				}
				
			case VK_LEFT://向左键
				{
					if (win.CanLeft(*block, col, row))
					{
						col = col - 1;
					}
					
					keyCode = 0;
					key = 0;
					break;
				}
				
			case VK_RIGHT://向右键
				{
					if (win.CanRight(*block, col, row))
					{
						col = col + 1;
					}
					keyCode = 0;
					key = 0;
					break;
				}
			case VK_DOWN://向下键
				{
					if (win.CanDown(*block, col, row))
						row = row + 1;
					keyCode = 0;
					break;
				}
		}
		
		//下底
		if (win.CanDown(*block, col, row) &&(con % game_speed == 0))
		{
			row = row + 1;
			if (con == 5000)
				con = 0;
		}
		if (oldcol!=col || oldrow != row || row <= 0 || keyCode ==99)
		{
			win.DrawDiamon(win.pDC, oldcol , oldrow , *block, RGB(0, 250, 140));//抹掉旧方块
			win.DrawDiamon(win.pDC, col  , row , *block, RGB(0, 0, 255));//画新方块
		}
	}
	if (con % 5 == 0)
	{
		for (int i = 0; i < win.cols; i++)  //判断方块是否叠到顶
		{
			if (win.gridData[i])
			{
				KillTimer(1);
				AfxMessageBox("游戏已结束！");
				win.Draw(win.pDC, win.winX , win.winY , win.winWidth , win.winHeight, RGB(0, 250, 140), true, win.hasGrid);
				
				game_begin = false;
				game_end = true;
				game_stop = true;
				stop = false;
				win.Init ();
				break;
			}
		}
	}	
	CView::OnTimer(nIDEvent);
}

void CRectView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	keyCode = nChar;
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CRectView::OnMganBigne() 
{
	if (!game_begin)
	{
		srand((unsigned)time(NULL));	//设置随机种子
		SetTimer(1, 60, NULL);			//设置定时器
		game_begin = true;
		game_stop = false;
		game_end = false;
	}
	else
	{
		game_stop = true;
		game_end = true;
	}

}


void CRectView::OnUpdateGameBigrn(CCmdUI* pCmdUI) 
{
	if (game_begin)
	{
		pCmdUI->Enable(false);
	}
	else 
	{
		pCmdUI->Enable(true);
	}
}

void CRectView::OnGameStop() //停止命令
{
	if (!game_stop)
	{
		KillTimer(1);
		stop = true;
		game_stop = true;
		game_begin = false;
	}
	else
	{
		stop = false;
		game_begin = false;
	}
}

void CRectView::OnUpdateGameStop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!game_stop);
}

void CRectView::OnGameExit() 
{
	exit(1);
}

void CRectView::OnUpdateGameExit(CCmdUI* pCmdUI) 
{
}

void CRectView::OnGameEnd() //结束命令
{
	if (!game_end)
	{
		KillTimer(1); 
		stop = false;
		if (block != NULL)
			delete block;
		block = NULL;
		
		win.pDC = GetDC();
		win.Draw (win.pDC, win.winX , win.winY , win.winWidth , win.winHeight, RGB(0, 250, 140), true, win.hasGrid); //窗口重画
		win.Init ();
		game_stop = true;
		game_end = true;
		game_begin = false;
	}
	else
	{
		game_begin = false;
	}
}

void CRectView::OnUpdateGameEnd(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!game_end);
}

//>>设置游戏级别 0,1,2,3,4
void CRectView::OnSetGrade0() 
{
	game_speed = 11;
	game_level = 0;
}

void CRectView::OnUpdateSetGrade0(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(game_level == 0);
	pCmdUI->Enable(!game_begin);	
}

void CRectView::OnSetGrade1() 
{
	game_speed = 7;
	game_level = 1;
}

void CRectView::OnUpdateSetGrade1(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(game_level == 1);
	pCmdUI->Enable(!game_begin);
}

void CRectView::OnSetGrade2() 
{
	game_speed = 5;
	game_level = 2;
}

void CRectView::OnUpdateSetGrade2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(game_level == 2);
	pCmdUI->Enable(!game_begin);
}

void CRectView::OnSetGrade3() 
{
	game_speed = 3;
	game_level = 3;
}

void CRectView::OnUpdateSetGrade3(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(game_level == 3);
	pCmdUI->Enable(!game_begin);
}

void CRectView::OnSetGrade4() 
{
	game_speed = 2;
	game_level = 4;
}

void CRectView::OnUpdateSetGrade4(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(game_level == 4);
	pCmdUI->Enable(!game_begin);	
}
//<<设置游戏级别


void CRectView::OnSetGrid() //设置网格
{
	if (game_hasGrid)
	{
		win.hasGrid =false;
		game_hasGrid = false;
	}
	else
	{
		win.hasGrid =true;
		game_hasGrid = true;
	}
	CDC  *pDC = GetDC();
	win.Draw(pDC, win.winX , win.winY , win.winWidth , win.winHeight, RGB(0, 250, 140), true, win.hasGrid);
}

void CRectView::OnUpdateSetGrid(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!game_begin);
	pCmdUI->SetCheck(game_hasGrid);
}


void CRectView::OnUpdateHelpMinyan(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(true);
}


void CRectView::Print(int level) //显示级别信息
{
	win.pDC->FillSolidRect(win.winWidth + win.winX + 8, win.winY + 230, 160, 120, RGB(0, 0, 0));
	win.pDC->FillSolidRect(win.winWidth + 9 + win.winX, win.winY + 350, 160, 20, RGB(255, 0, 0));	

	CString live;
	CString gonli;
	win.pDC->FillSolidRect(win.winWidth + 9 + win.winX, win.winY + 350, oldrow * 10 , 20, RGB(100, 255, 100));
	win.pDC -> SetBkColor(RGB(0, 0, 0));
	win.pDC -> SetTextColor(RGB(255, 200, 200));
	live.Format("    体力还有:  %d ",(oldrow)  * 8);
	gonli.Format("    功力为: %d  ",win .newScore + win.oldScore);
	win.pDC -> TextOut(win.winWidth + 19 + win.winX, win.winY + 330, live);
	win.pDC -> TextOut(win.winWidth + 19 + win.winX, win.winY + 270, gonli);

	switch (level)
		{
			case 0:
				win.pDC -> TextOut(win.winWidth + 9 + win.winX, win.winY + 200, "       身份: 小叫化 !");
				break;
			case 1:
				win.pDC -> TextOut(win.winWidth + 9 + win.winX, win.winY + 200, "    身份: 小乞丐 !");
				break;
			case 2:
				win.pDC -> TextOut(win.winWidth + 9 + win.winX, win.winY + 200, "     身份: 护法长老 !");
				break;
			case 3:
				win.pDC -> TextOut(win.winWidth + 9 + win.winX, win.winY + 200, "     身份: 执法长老 !");
				break;
			case 4:
				win.pDC -> TextOut(win.winWidth + 9 + win.winX, win.winY + 200, "     身份: 帮主 !");
				break;
		}
		
		switch (level)
		{
			case 0:
				win.pDC->FillSolidRect(win.winWidth + 9 + win.winX, win.winY + 290, 160, 20, RGB(30, 155, 100));
				win.pDC->FillSolidRect(win.winWidth + 9 + win.winX, win.winY + 290, win.newScore/25, 20, RGB(255, 255, 0));
				break;
			case 1:
				win.pDC->FillSolidRect(win.winWidth + 9 + win.winX, win.winY + 290, 160, 20, RGB(255, 255, 0));
				win.pDC->FillSolidRect(win.winWidth + 9 + win.winX, win.winY + 290, (win.newScore)/25, 20, RGB(150, 255, 255));
				break;
			case 2:
				win.pDC->FillSolidRect(win.winWidth + 9 + win.winX, win.winY + 290, 160, 20, RGB(150, 255, 255));
				win.pDC->FillSolidRect(win.winWidth + 9 + win.winX, win.winY + 290, (win.newScore)/25, 20, RGB(255, 255, 0));
				break;
			case 3:
				win.pDC->FillSolidRect(win.winWidth + 9 + win.winX, win.winY + 290, 160, 20, RGB(255, 255, 0));
				win.pDC->FillSolidRect(win.winWidth + 9 + win.winX, win.winY + 290, (win.newScore)/25, 20, RGB(150, 255, 255));
				break;
			case 4:
				win.pDC->FillSolidRect(win.winWidth + 9 + win.winX, win.winY + 290, 160, 20, RGB(150, 255, 255));
				win.pDC->FillSolidRect(win.winWidth + 9 + win.winX, win.winY + 290, (win.newScore)/20, 20, RGB(255, 255, 0));
				break;
		}
}

void CRectView::SetLevel(int  Score) //设置级别
{
	if ( Score >=  4000)
	{
		switch (game_level)
		{
			case 0:
				win.oldScore =win.oldScore + 4000;
				win.newScore = win.newScore - 4000;
				KillTimer(1);
				AfxMessageBox("恭喜升为小乞丐!!");
				OnSetGrade1();
				SetTimer(1, 60, NULL);
				break;
			case 1:
				win.oldScore =win.oldScore + 4000;
				win.newScore = win.newScore - 4000;
				KillTimer(1);
				AfxMessageBox("恭喜升为护法长老!!");
				OnSetGrade2();
				SetTimer(1, 60, NULL);
				break;
			case 2:
				win.oldScore =win.oldScore + 4000;
				win.newScore = win.newScore - 4000;
				KillTimer(1);
				AfxMessageBox("恭喜升为执法长老!!");
				OnSetGrade3();
				SetTimer(1, 60, NULL);
				break;
			case 3:
				win.oldScore =win.oldScore + 4000;
				win.newScore = win.newScore - 4000;
				KillTimer(1);
				AfxMessageBox("恭喜升为帮主!!");
				OnSetGrade4();
				SetTimer(1, 60, NULL);
				break;
		}
	}
}

void CRectView::OnSetMusic() //播放音乐
{  
	if(game_music)
	{
		game_music =false;
		HWND hWnd;
		hWnd = GetSafeHwnd();

		char inBuf[300],outBuf[60],fileName[255];
		MCIERROR mciError;

		strcpy(fileName,"music.mid"); 
		wsprintf( inBuf,"open %s type sequencer alias myseq",fileName);
		mciError = mciSendString( inBuf, outBuf, sizeof(outBuf), NULL);
		if (mciError == 0)
		{
			mciError = mciSendString("play myseq notify",NULL,0, hWnd);
			if (mciError != 0)
				mciSendString("close myseq",NULL,0,NULL);
		}
	}
	else
	{
		game_music = true;
		mciSendString("close myseq",NULL,0,NULL);
	}	
}

void CRectView::OnUpdateSetMusic(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!game_music);
}
