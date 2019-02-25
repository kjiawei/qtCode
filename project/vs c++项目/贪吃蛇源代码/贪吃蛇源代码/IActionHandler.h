// IActionHandler.h: interface for the IActionHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IACTIONHANDLER_H__2EBD7F20_452B_11D7_B6CA_0050BAE90E03__INCLUDED_)
#define AFX_IACTIONHANDLER_H__2EBD7F20_452B_11D7_B6CA_0050BAE90E03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IGraphicOut.h"

class IActionHandler  
{
public:
    enum Direction {left=0, up=1, right=2, down=3,
    leftOpen=10, upOpen=11, rightOpen=12, downOpen=13};
    IActionHandler(IGraphicOut *const pGO) : m_pGO(pGO) {}
    virtual ~IActionHandler() {}
    virtual int getSpeed() { return 1; }
    virtual void changeSpeed(int speed)=0;
    virtual void leftMove()=0;
    virtual void rightMove()=0;
    virtual void upMove()=0;
    virtual void downMove()=0;
    virtual void timeUp()=0;
    virtual void exit()=0;
    virtual void draw()=0;
protected:
    IGraphicOut * const m_pGO;
};

#endif // !defined(AFX_IACTIONHANDLER_H__2EBD7F20_452B_11D7_B6CA_0050BAE90E03__INCLUDED_)
