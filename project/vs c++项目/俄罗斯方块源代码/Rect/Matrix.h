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
	int cols;					//��
	int rows;					//��

	int* gridData;
	COLORREF matrixColor;		//������ɫ

	CDC* pDC;
	int	winX,winY;				//�����������
	int winWidth, winHeight;	//���ڿ����߶�
	int cellWidth, cellHeight;	//��ԭ������߶�

	int newScore;				//��¼���ڳɼ�
	int oldScore;				//�����ϴγɼ�

	bool hasGrid;				//��¼�Ƿ�����
	
	void Draw(CDC *pDC,int x,int y,int cx,int cy,COLORREF diamonColor, bool update, bool hasGrid);
	void DrawDiamon(CDC *pDC,int x,int y,Diamond const &m,COLORREF diamonColor); //������

	void SetMatrix(int x,int y,int cx,int cy,COLORREF diamonColor); //����Matrix���������

	bool CanTrun (Diamond const& m, int col, int row) const; //�ж��ܷ�ת
	bool CanDown (Diamond const& m, int col, int row) const; //�ж��ܷ�����
	bool CanRight (Diamond const&m, int col, int row) const; //�ж��ܷ���
	bool CanLeft (Diamond const&m, int col, int row) const; //�ж��ܷ���

	Matrix& Add (Diamond const& m, int x, int y);			//���������ۼ�

	bool IsFullLine(int line) const;						//�ж�ָ�����Ƿ���
	void DeleteLine(int line) const;						//ɾ��ָ����
	bool Tidy ();											//����

	void Init ();//��ʼ������
	Matrix(int rows ,int cols);
	~Matrix();


};

#endif // !defined(AFX_MATRIX_H__05EC1871_E972_11D5_9B6C_AD7148B27E00__INCLUDED_)
