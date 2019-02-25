// IGraphicOut.h: interface for the IGraphicOut class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IGRAPHICOUT_H__2EBD7F1F_452B_11D7_B6CA_0050BAE90E03__INCLUDED_)
#define AFX_IGRAPHICOUT_H__2EBD7F1F_452B_11D7_B6CA_0050BAE90E03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class IGraphicOut  
{
public:
    enum FoodType {fruit=0, flower=1};
    virtual void scoreBoard(char *scoreMessages)=0;
    virtual void redraw()=0;
    virtual void drawHead(int type, int x, int y)=0;
    virtual void drawBody(int x, int y)=0;
    virtual void drawFood(int type, int x, int y)=0;
    virtual void drawHorzWall(int x1, int x2, int y)=0;
    virtual void drawVertWall(int x, int y1, int y2)=0;
    virtual void drawScore(int score)=0;
    virtual void setDisplaySize(int width, int height)=0;
    virtual void close()=0;
    IGraphicOut() : m_pDC(0) {}
    virtual ~IGraphicOut() {}

protected:
    CDC  *m_pDC;
};

#endif // !defined(AFX_IGRAPHICOUT_H__2EBD7F1F_452B_11D7_B6CA_0050BAE90E03__INCLUDED_)
