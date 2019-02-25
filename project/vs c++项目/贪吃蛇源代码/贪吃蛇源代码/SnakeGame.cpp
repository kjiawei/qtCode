// SnakeGame.cpp: implementation of the CSnakeGame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Snake.h"
#include "SnakeGame.h"
#include "IGraphicOut.h"
#include "time.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnakeGame::CSnakeGame(IGraphicOut * const pGO)
    : IActionHandler(pGO),
      m_xSize(15), m_ySize(15),
      m_xPos(m_xSize/2), m_yPos(m_ySize/2),
      m_xPosBody(m_xPos+1), m_yPosBody(m_yPos),
      m_curDir(left),
      m_score(12345),
      m_timerCount(0),
      m_mouseOpen(false),
      m_speed(5),
      m_xFood(-1), m_yFood(-1)
{
    srand(time(0L));
    pGO->setDisplaySize(m_xSize, m_ySize);
    m_xFood = rand() % m_xSize;
    m_yFood = rand() % m_ySize;
}

CSnakeGame::~CSnakeGame()
{
}

void CSnakeGame::leftMove()
{
    if (m_curDir != right)
        if (m_xPos>0)
            m_curDir = left;
}

void CSnakeGame::rightMove()
{
    if (m_curDir != left)
        if (m_xPos<m_xSize-1)
            m_curDir = right;
}

void CSnakeGame::upMove()
{
    if (m_curDir != down)
        if (m_yPos<m_ySize-1)
            m_curDir = up;
}

void CSnakeGame::downMove()
{
    if (m_curDir != up)
        if (m_yPos>0)
            m_curDir = down;
}

void CSnakeGame::timeUp()
{
    if (++m_timerCount >= 10*m_speed) // 10*m_speed*5ms
    {
        // In the following, no wall collision tested
        switch (m_curDir)
        {
            case left:
                if (m_xPos>0)
                {
                    m_xPos--;
                    m_xPosBody = m_xPos+1;
                    m_yPosBody = m_yPos;
                }
                break;
            case up:
                if (m_yPos<m_ySize-1) 
                {
                    m_yPos++;
                    m_yPosBody = m_yPos-1;
                    m_xPosBody = m_xPos;
                }
                break;
            case right:
                if (m_xPos<m_xSize-1) 
                {
                    m_xPos++;
                    m_xPosBody = m_xPos-1;
                    m_yPosBody = m_yPos;
                }
                break;
            case down:
                if (m_yPos>0) 
                {
                    m_yPos--;
                    m_yPosBody = m_yPos+1;
                    m_xPosBody = m_xPos;
                }
                break;
        }
        if ((m_xPos==m_xFood)&&
            (m_yPos==m_yFood))
        {
            m_score += 100;
            m_xFood = rand() % m_xSize;
            m_yFood = rand() % m_ySize;
            // no collision tested
        }
        m_mouseOpen = false;
        m_pGO->redraw();
        m_timerCount = 0;
    }
    else if (m_timerCount == 10/2*m_speed) // blinking
    {
        m_mouseOpen = true;
        m_pGO->redraw();
    }
}

void CSnakeGame::exit()
{
    m_pGO->scoreBoard("\t\tHighest Scores\n"
                      "1. John Snake\t\t12345678\n"
                      "2. Rob Epson\t\t98765\n"
                      "\n\t\tGood bye!!");
}

void CSnakeGame::draw()
{
    if ((m_xFood>=0)&&(m_yFood>=0))
        m_pGO->drawFood(IGraphicOut::flower, m_xFood, m_yFood);

    if (m_mouseOpen)
        m_pGO->drawHead(m_curDir+10, m_xPos, m_yPos);
    else
        m_pGO->drawHead(m_curDir, m_xPos, m_yPos);
    m_pGO->drawBody(m_xPosBody, m_yPosBody);
    m_pGO->drawScore(m_score);

    // demo only, no collision detetion
    m_pGO->drawHorzWall(3, 5, 2);
    m_pGO->drawVertWall(8, 0, 5);
}

void CSnakeGame::changeSpeed(int speed)
{
    m_speed = speed;
}

int CSnakeGame::getSpeed()
{
    return m_speed;
}
