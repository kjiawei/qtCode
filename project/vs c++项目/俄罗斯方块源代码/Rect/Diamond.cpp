// Diamond.cpp: implementation of the Diamond class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RECT.h"
#include "Diamond.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

Diamond::Diamond()
{
	///初始化数据///
	rows = 4;
	cols = 2;
	DiamondColor = RGB(0, 0, 255); ///初始颜色为蓝色
	DiamondType = 1; //初始类型为1
	CellData = NULL;
	
	CellData = new int[rows * cols];
	for (int i = 0; i < rows * cols; i++)
	{
		CellData[i] = 0;
	}
}

//按类型设置方块数据
void Diamond::SetDiamond(int DiamondType)
{
	switch (DiamondType)
	{
		case 0:// I
			CellData[0] = 1;	
			CellData[1] = 1;
			CellData[2] = 1;
			CellData[3] = 1;
			rows = 4;
			cols = 1;
			break;
		case 1:// L
			CellData[0] = 1;
			CellData[1] = 0;
			CellData[2] = 1;
			CellData[3] = 0;
			CellData[4] = 1;
			CellData[5] = 1;
			CellData[6] = 0;
			CellData[7] = 0;
			rows = 3;
			cols = 2;
			break;
		case 2:// L
			CellData[0] = 0;
			CellData[1] = 1;
			CellData[2] = 0;
			CellData[3] = 1;
			CellData[4] = 1;
			CellData[5] = 1;
			CellData[6] = 0;
			CellData[7] = 0;
			rows = 3;
			cols = 2;
			break;
		case 3:// Z
			CellData[0] = 1;
			CellData[1] = 0;
			CellData[2] = 1;
			CellData[3] = 1;
			CellData[4] = 0;
			CellData[5] = 1;
			CellData[6] = 0;
			CellData[7] = 0;
			rows = 3;
			cols = 2;
			break;
		case 4:// Z
			CellData[0] = 0;
			CellData[1] = 1;
			CellData[2] = 1;
			CellData[3] = 1;
			CellData[4] = 1;
			CellData[5] = 0;
			CellData[6] = 0;
			CellData[7] = 0;
			rows = 3;
			cols = 2;
			break;
		case 5:// T
			CellData[0] = 1;
			CellData[1] = 0;
			CellData[2] = 1;
			CellData[3] = 1;
			CellData[4] = 1;
			CellData[5] = 0;
			CellData[6] = 0;
			CellData[7] = 0;
			rows = 3;
			cols = 2;
			break;
		case 6:// O
			CellData[0] = 1;
			CellData[1] = 1;
			CellData[2] = 1;
			CellData[3] = 1;
			CellData[4] = 0;
			CellData[5] = 0;
			CellData[6] = 0;
			CellData[7] = 0;
			rows = 2;
			cols = 2;
			break;
		case 7:// T
			CellData[0] = 1;
			CellData[1] = 0;
			CellData[2] = 1;
			CellData[3] = 1;
			CellData[4] = 1;
			CellData[5] = 0;
			CellData[6] = 0;
			CellData[7] = 0;
			rows = 3;
			cols = 2;
			break;
		case 8:// I
			CellData[0] = 1;	
			CellData[1] = 1;
			CellData[2] = 0;
			CellData[3] = 0;
			rows = 2;
			cols = 1;
			break;
		case 9:// I
			CellData[0] = 1;	
			CellData[1] = 1;
			CellData[2] = 1;
			CellData[3] = 1;
			rows = 4;
			cols = 1;
			break;	
		case 10:// 1
			CellData[0] = 1;	
			CellData[1] = 0;
			CellData[2] = 0;
			CellData[3] = 0;
			rows = 1;
			cols = 1;
			break;	
	}
}

Diamond& Diamond::operator=(const Diamond &D)
{
	if (this == &D)
		return *this;
	
	rows = D.rows;
	cols = D.cols;
	DiamondColor = D.DiamondColor;
	DiamondType = D.DiamondType;
	
	for (int i = 0; i < D.rows * D.cols; i++)
	{
		this->CellData[i] = D.CellData[i]; 
	}
	
	return *this;
}

Diamond & Diamond::Trun() 
{
	Diamond oldm;
	oldm = *this; 
	
	this->rows = oldm.cols;
	this->cols = oldm.rows;
	
	if (CellData != NULL)
		delete[] CellData;
	CellData = new int[rows * cols];
	
	for (int i = 0; i < oldm.rows; i ++)
	{
		for (int j = 0; j < oldm.cols; j ++)
		{
			CellData[j * cols + cols - i - 1] = oldm.CellData[i * oldm.cols + j]; 
		}
	}
	
	return *this;
}

Diamond::~Diamond()
{
	if (CellData != NULL)
		delete[] CellData;

	CellData = NULL;
}

