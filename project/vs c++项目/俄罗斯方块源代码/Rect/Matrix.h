// Matrix.h: interface for the Matrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIX_H__05EC1871_E972_11D5_9B6C_AD7148B27E00__INCLUDED_)
#define AFX_MATRIX_H__05EC1871_E972_11D5_9B6C_AD7148B27E00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
# include  "Diamond.h"
class Matrix  
{
public:
	int cols;					//列
	int rows;					//行

	int* gridData;
	COLORREF matrixColor;		//窗口颜色

	CDC* pDC;
	int	winX,winY;				//窗口起点坐标
	int winWidth, winHeight;	//窗口宽度与高度
	int cellWidth, cellHeight;	//单原格宽度与高度

	int newScore;				//计录现在成绩
	int oldScore;				//保存上次成绩

	bool hasGrid;				//计录是否画网格
	
	void Draw(CDC *pDC,int x,int y,int cx,int cy,COLORREF diamonColor, bool update, bool hasGrid);
	void DrawDiamon(CDC *pDC,int x,int y,Diamond const &m,COLORREF diamonColor); //画方块

	void SetMatrix(int x,int y,int cx,int cy,COLORREF diamonColor); //设置Matrix对象的数据

	bool CanTrun (Diamond const& m, int col, int row) const; //判断能否翻转
	bool CanDown (Diamond const& m, int col, int row) const; //判断能否向下
	bool CanRight (Diamond const&m, int col, int row) const; //判断能否右
	bool CanLeft (Diamond const&m, int col, int row) const; //判断能否左

	Matrix& Add (Diamond const& m, int x, int y);			//方块数据累加

	bool IsFullLine(int line) const;						//判断指定行是否满
	void DeleteLine(int line) const;						//删除指定行
	bool Tidy ();											//整理

	void Init ();//初始化数据
	Matrix(int rows ,int cols);
	~Matrix();


};

#endif // !defined(AFX_MATRIX_H__05EC1871_E972_11D5_9B6C_AD7148B27E00__INCLUDED_)
