// SnakeGame.h: interface for the CSnakeGame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAKEGAME_H__2EBD7F21_452B_11D7_B6CA_0050BAE90E03__INCLUDED_)
#define AFX_SNAKEGAME_H__2EBD7F21_452B_11D7_B6CA_0050BAE90E03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IActionHandler.h"
class IGraphicOut;

class CSnakeGame : public IActionHandler
{
public:
	int getSpeed();
	void changeSpeed(int speed);
    virtual void leftMove();
    virtual void rightMove();
    virtual void upMove();
    virtual void downMove();
    virtual void timeUp();
    virtual void exit();
    virtual void draw();

    CSnakeGame(IGraphicOut * const pGO);
    virtual ~CSnakeGame();

private:
	int m_yFood;
	int m_xFood;
	int m_speed;
	bool m_mouseOpen;
	int m_timerCount;
	int m_score;
    Direction m_curDir;
	int m_ySize;
	int m_xSize;
	int m_yPos;
	int m_xPos;
	int m_yPosBody;
	int m_xPosBody;
};

#endif // !defined(AFX_SNAKEGAME_H__2EBD7F21_452B_11D7_B6CA_0050BAE90E03__INCLUDED_)
