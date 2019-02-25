#include "stdafx.h"
#include "RECT.h"
#include "Matrix.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Matrix::Matrix(int rows, int cols)
{
	/////初始化数据///
	this->rows = rows;
	this->cols = cols;
	
	winX = 0;
	winY = 0;
	winWidth = 0;
	winHeight = 0;
	cellWidth = 0; 
	cellHeight = 0;
	pDC = NULL;
	matrixColor = RGB(0, 0, 0);
	newScore = 0; //成绩	
	oldScore = 0; //成绩	
	
	hasGrid = true;
	gridData = new int[rows * cols];
	for (int i = 0; i <= rows; i++)
	{
		for (int j = 0; j <= cols; j++)
		{
			gridData[i*cols + j] = 0;
		}
	}
}
void Matrix::Init()//初始化数据
{
	newScore = 0;//成绩清零
	oldScore = 0;//成绩清零

	//>>重画窗口
	pDC->FillSolidRect(winWidth + winX + 8, winY + 180, 160, 240, RGB(0, 0, 0));
	pDC->FillSolidRect(winWidth + 9 + winX, winY + 350, 160, 20, RGB(100, 255, 100));
	
	pDC -> SetBkColor(RGB(0, 0, 0)); 
	pDC -> SetTextColor(RGB(255, 200, 200));
	pDC -> TextOut(winWidth + 19 + winX, winY + 330, "你的体力还有:  0");
	pDC -> TextOut(winWidth + 19 + winX, winY + 270, "你的功力为: 0 ");		
	pDC -> FillSolidRect(winWidth + 9 + winX, winY + 290, 160, 20, RGB(30, 155, 100));
	//<<重画窗

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			gridData[i*cols + j] = 0;
		}
	}
}


//判断能否左
bool Matrix::CanLeft(Diamond const&m, int col, int row) const
{
	if (col <= 0)
		return false;
	
	for (int i = 0; i  <  m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			if (m.CellData[i * m.cols + j]  ==  1)
			{
				if (gridData[(row + i) * cols +(col + j - 1)] ==  1)
					return false;
			}
		}
	}
	
	return true;
}

//判断能否右
bool Matrix::CanRight(Diamond const&m, int col, int row) const
{
	if (col + m.cols >= cols)
		return false;
	for (int i = 0; i  <  m.rows; i++)
	{
		for (int j = m.cols - 1; j >= 0; j--)
		{
			if (m.CellData[i*m.cols + j] == 1)
			{
				if (gridData[(row + i) * cols +(col + j + 1)] == 1)
					return false;
			}
		}
	}
	return true;
}

//判断能否向下
bool Matrix::CanDown(Diamond const&m, int col, int row) const
{	

	if (row + m.rows >=  rows)
		return false;
	for (int i = 0; i < m.cols; i ++)
	{
		for (int j = m.rows - 1; j >= 0; j--)
		{
			if (m.CellData[j * m. cols + i] == 1)
			{
				if (gridData[(row + j + 1) * cols +(col + i)] == 1)
					return false;
			}
		}
	}
	
	return true;
}

//判断能否翻转
bool Matrix::CanTrun(Diamond const&m, int col, int row) const
{
	if (m.rows > m.cols)
		if (col + m.rows > cols)
			return false;
		return true;
}

//判断指定行是否满
bool Matrix::IsFullLine(int row) const
{
	for (int i = 0; i < cols; i++)
	{
		if (gridData[row * cols + i] == 0)
			return  false;
	}
	return true;
}

//删除指定行
void Matrix::DeleteLine(int row) const
{
	for (int i = row - 1; i >= 0; i--)
	{
		for (int j = 0; j < cols; j++)
		{
			gridData[(i + 1) * cols + j] = gridData[(i * cols + j)];
		}
	}
}

//整理
bool Matrix::Tidy()
{
	bool ret = false;
	for (int i = rows; i >= 0; i--)
	{
		while (IsFullLine(i))
		{
			DeleteLine(i);
			newScore += 100; //成绩加上一百分
			ret = true;
		}
	}
	
	return ret;
}

//更新数据
void Matrix::SetMatrix(int x, int y, int cx, int cy, COLORREF matrixColor)
{
	winX = x;
	winY = y;
	winWidth = cx;
	winHeight = cy;
	
	this->matrixColor = matrixColor;
	cellWidth = winWidth / cols;
	cellHeight =winHeight /rows;
}

void Matrix::Draw(CDC *pDC, int x, int y, int cx, int cy, COLORREF matrixColor, bool updata, bool hasGrid)
{
	if (updata)//是否要更新数据
		SetMatrix(x, y, cx, cy, matrixColor);
	if (matrixColor == RGB(0, 0, 255))
	{
		pDC->FillSolidRect(x, y, cx, cy, RGB(255, 255, 255));
		
		pDC->FillSolidRect(x + 1, y + 1, cx - 2, cy - 2, matrixColor);
	}
	else
	{
		pDC->FillSolidRect(x, y, cx, cy, matrixColor);
		pDC->SetTextColor(RGB(255, 200, 200));
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->TextOut(winWidth + 30 + winX, winY + 20, "下一方块");
	}
	
	//////////////////////////画网格与四条边/////////////////////////
	if (hasGrid)
	{
		int i;
		CPen pen1;
		CPen pen2;
		pen1.CreatePen(PS_SOLID, 1, RGB(250, 0, 250));//设置画笔1
		pen2.CreatePen(PS_SOLID, 5, RGB(255, 255, 255));//设置画笔2
		pDC->SelectObject(&pen1);//装入画笔1
		///////////////画网格////////////////
		//画网格横线
		
		for (i = 0; i < rows; i++)
		{
			pDC->MoveTo(winX, winY + cellHeight * i);
			pDC->LineTo(winX + winWidth, winY + cellHeight * i);
		}	
		
		//画网格竖线
		for (i = 0; i < cols; i++)
		{
			pDC->MoveTo(winX + cellWidth * i, winY);
			pDC->LineTo(winX + cellWidth * i, winY + winHeight);
		}
		
		pDC->SelectObject(&pen2);//装入画笔2
		/////////////////////画四条加粗边///////////////
		pDC->MoveTo(winX - 2, winY - 2);
		pDC->LineTo(winX - 2, winY + winHeight + 2);
		
		pDC->MoveTo(winX + winWidth + 2, winY - 2);
		pDC->LineTo(winX + winWidth + 2, winY + winHeight + 2);
		
		pDC->MoveTo(winX - 2, winY - 2);
		pDC->LineTo(winX + winWidth + 2, winY - 2);
		
		pDC->MoveTo(winX - 2, winY + winHeight + 2);
		pDC->LineTo(winX + winWidth + 2, winY + winHeight + 2);
	}
}

void Matrix::DrawDiamon(CDC *pDC, int col, int row, Diamond const&m, COLORREF diamonColor)
{
	//////////画方块//////////////////////
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			if (m.CellData[i*m.cols +j] == 1)
			{
				////判断颜色是否是背景色是则用背景色抹掉旧方块,否则画新方块
				if (diamonColor == RGB(0, 250, 140) ||  diamonColor == RGB(0, 0, 0)) //抹掉旧方块
					pDC->FillSolidRect((col + j) *	cellWidth + 1+winX, (row +i)*cellHeight + 1+winY, cellWidth - 2 , cellHeight - 2, diamonColor);
				else //画新方块
				{
								//立体效果是由一大方块(白色)和一小方块(蓝色)叠套产生
					pDC->FillSolidRect((col + j) *	cellWidth + 1+winX, (row + i)*cellHeight + 1+winY, cellWidth - 2 , cellHeight - 2, RGB(255, 255, 255)); //大格
					pDC->FillSolidRect((col + j) *	cellWidth + 2+winX, (row + i)*cellHeight + 2+winY, cellWidth - 4 , cellHeight - 4, diamonColor); //小格
				}
			}
		}
	}
}

//方块数据累加
Matrix& Matrix::Add(Diamond const& m, int col, int row)
{
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j <m.cols; j++)
		{
			if (gridData[(row + i) * cols +(col + j)] == 0)
				gridData[(row + i) * cols +(col + j)] = m.CellData[i * m.cols + j];
		}
	}
	return *this;
}

Matrix::~Matrix()
{
}
