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
	int rows;							//方块行
	int cols;							//方块列

	int* CellData;						//方块数据
	int DiamondType;					//方块类型
	COLORREF DiamondColor;				//方块颜色
	void SetDiamond(int DiamondType);	//按方块类型构造方块
	Diamond & operator =(const Diamond &D);
	Diamond	& Trun();					//方块翻转时转置数据
	Diamond();
	 ~Diamond();
};

#endif // !defined(AFX_DIAMOND_H__4CFEC221_EB46_11D5_9B6C_B76B078EBA1C__INCLUDED_)
