#include "stdafx.h"
#include "SnakeDoc.h"
#include "SnakeView.h"
#include "SnakeGame.h"

void maininit()
{
    CSnakeView *pView = (CSnakeView*) 
        ((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

    // TODO: modify CSnakeGame to be your own class
    CSnakeGame *snake = new CSnakeGame(pView);

    pView->SetActionHandler(snake); 
    // the ownership of snake is transferred
}