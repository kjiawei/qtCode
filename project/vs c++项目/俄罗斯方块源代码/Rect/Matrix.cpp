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
	/////��ʼ������///
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
	newScore = 0; //�ɼ�	
	oldScore = 0; //�ɼ�	
	
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
void Matrix::Init()//��ʼ������
{
	newScore = 0;//�ɼ�����
	oldScore = 0;//�ɼ�����

	//>>�ػ�����
	pDC->FillSolidRect(winWidth + winX + 8, winY + 180, 160, 240, RGB(0, 0, 0));
	pDC->FillSolidRect(winWidth + 9 + winX, winY + 350, 160, 20, RGB(100, 255, 100));
	
	pDC -> SetBkColor(RGB(0, 0, 0)); 
	pDC -> SetTextColor(RGB(255, 200, 200));
	pDC -> TextOut(winWidth + 19 + winX, winY + 330, "�����������:  0");
	pDC -> TextOut(winWidth + 19 + winX, winY + 270, "��Ĺ���Ϊ: 0 ");		
	pDC -> FillSolidRect(winWidth + 9 + winX, winY + 290, 160, 20, RGB(30, 155, 100));
	//<<�ػ���

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			gridData[i*cols + j] = 0;
		}
	}
}


//�ж��ܷ���
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

//�ж��ܷ���
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

//�ж��ܷ�����
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

//�ж��ܷ�ת
bool Matrix::CanTrun(Diamond const&m, int col, int row) const
{
	if (m.rows > m.cols)
		if (col + m.rows > cols)
			return false;
		return true;
}

//�ж�ָ�����Ƿ���
bool Matrix::IsFullLine(int row) const
{
	for (int i = 0; i < cols; i++)
	{
		if (gridData[row * cols + i] == 0)
			return  false;
	}
	return true;
}

//ɾ��ָ����
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

//����
bool Matrix::Tidy()
{
	bool ret = false;
	for (int i = rows; i >= 0; i--)
	{
		while (IsFullLine(i))
		{
			DeleteLine(i);
			newScore += 100; //�ɼ�����һ�ٷ�
			ret = true;
		}
	}
	
	return ret;
}

//��������
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
	if (updata)//�Ƿ�Ҫ��������
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
		pDC->TextOut(winWidth + 30 + winX, winY + 20, "��һ����");
	}
	
	//////////////////////////��������������/////////////////////////
	if (hasGrid)
	{
		int i;
		CPen pen1;
		CPen pen2;
		pen1.CreatePen(PS_SOLID, 1, RGB(250, 0, 250));//���û���1
		pen2.CreatePen(PS_SOLID, 5, RGB(255, 255, 255));//���û���2
		pDC->SelectObject(&pen1);//װ�뻭��1
		///////////////������////////////////
		//���������
		
		for (i = 0; i < rows; i++)
		{
			pDC->MoveTo(winX, winY + cellHeight * i);
			pDC->LineTo(winX + winWidth, winY + cellHeight * i);
		}	
		
		//����������
		for (i = 0; i < cols; i++)
		{
			pDC->MoveTo(winX + cellWidth * i, winY);
			pDC->LineTo(winX + cellWidth * i, winY + winHeight);
		}
		
		pDC->SelectObject(&pen2);//װ�뻭��2
		/////////////////////�������Ӵֱ�///////////////
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
	//////////������//////////////////////
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			if (m.CellData[i*m.cols +j] == 1)
			{
				////�ж���ɫ�Ƿ��Ǳ���ɫ�����ñ���ɫĨ���ɷ���,�����·���
				if (diamonColor == RGB(0, 250, 140) ||  diamonColor == RGB(0, 0, 0)) //Ĩ���ɷ���
					pDC->FillSolidRect((col + j) *	cellWidth + 1+winX, (row +i)*cellHeight + 1+winY, cellWidth - 2 , cellHeight - 2, diamonColor);
				else //���·���
				{
								//����Ч������һ�󷽿�(��ɫ)��һС����(��ɫ)���ײ���
					pDC->FillSolidRect((col + j) *	cellWidth + 1+winX, (row + i)*cellHeight + 1+winY, cellWidth - 2 , cellHeight - 2, RGB(255, 255, 255)); //���
					pDC->FillSolidRect((col + j) *	cellWidth + 2+winX, (row + i)*cellHeight + 2+winY, cellWidth - 4 , cellHeight - 4, diamonColor); //С��
				}
			}
		}
	}
}

//���������ۼ�
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
