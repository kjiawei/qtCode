// Diamond.h: interface for the Diamond class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIAMOND_H__4CFEC221_EB46_11D5_9B6C_B76B078EBA1C__INCLUDED_)
#define AFX_DIAMOND_H__4CFEC221_EB46_11D5_9B6C_B76B078EBA1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Diamond  
{
public:
	int rows;							//������
	int cols;							//������

	int* CellData;						//��������
	int DiamondType;					//��������
	COLORREF DiamondColor;				//������ɫ
	void SetDiamond(int DiamondType);	//���������͹��췽��
	Diamond & operator =(const Diamond &D);
	Diamond	& Trun();					//���鷭תʱת������
	Diamond();
	 ~Diamond();
};

#endif // !defined(AFX_DIAMOND_H__4CFEC221_EB46_11D5_9B6C_B76B078EBA1C__INCLUDED_)
