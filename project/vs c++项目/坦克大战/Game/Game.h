// Game.h: interface for the CGame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAME_H__18287D61_DB36_11D3_B12A_F67D0FBE8D25__INCLUDED_)
#define AFX_GAME_H__18287D61_DB36_11D3_B12A_F67D0FBE8D25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ddraw.h>
#include "Plane.h"
#include "Sprite.h"
#include "Input.h"
#include "Sound.h"

#define NUM_BITMAPS		15
#define NUM_EXPLODES	20
#define NUM_ENEMYS		6


enum GAMESTATE
{
	GS_SPLASH,
	GS_ACTIVE,
	GS_WIN,
	GS_OVER,
};


class CGame  
{
public:
	CGame();
	virtual ~CGame();

	BOOL	Initialize( HINSTANCE hInst );
	BOOL	InitApplication();
	BOOL	DDInit();
	void	DDTerm();
	void	ResetPlayer( CPlayer& player );
	BOOL	InitLevel();
	BOOL	InitGame();
	BOOL	ResetGame();
	void	CleanUpGame();
	void	DDClear( RECT* prc, DWORD dwFillColor );
	void	FlipScreen();
	void	ProcessInput();
	void	UpdateFrame();
	int		Run();
	void	Explode( CSprite& sprite, BOOL bExplode=FALSE );
	void	PlayerBeenHit( CPlayer& player );
	BOOL	BoreBonus();
	BOOL	BoreEnemy();
	void	EatBonus( CPlayer& player );
	void	EatBonus( CEnemy& enemy );	
	void	GameOver();
	BOOL	LoadBitmaps();
	void	RestoreSurfaces();
	void	OutputText( int x, int y, LPCTSTR string );

	void	DoSplash();
	void	DrawWorld();
	void	BltNumber( int x, int y, int n );

	LPDIRECTDRAWSURFACE DDLoadBitmap( LPCSTR szBitmap, int dx=0, int dy=0 );
	LPDIRECTDRAWSURFACE DDCreateSurface( int width, int height );
	LRESULT MsgProc( HWND hWnd, UINT uMsg, WPARAM, LPARAM );

private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	BOOL		m_bActive;
	BOOL		m_bShowStats;
	BOOL		m_bFullScreen;
	BOOL		m_bSingle;
	RECT		m_rcWindow;
	DWORD		m_dwFillColor;

	LPDIRECTDRAW			m_pDD;
	LPDIRECTDRAWSURFACE		m_pddsFrontBuffer;
	LPDIRECTDRAWSURFACE		m_pddsBackBuffer;
	LPDIRECTDRAWSURFACE		m_pBmpList[NUM_BITMAPS];

	CDirectInput	m_DirectInput;
	CDirectSound	m_DirectSound;

	CPlane		m_plane;
	CPlayer		m_player[2];
	CEnemy		m_enemy[NUM_ENEMYS];
	int			m_nMaxEnemys;
	CExplode	m_explode[NUM_EXPLODES];
	CBonus		m_bonus;

	GAMESTATE	m_gameState;
	DWORD		m_lastTime;
	int			m_nLevel;
	int			m_nEnemysLeft;
	int			m_nEnemys;
	BOOL		m_bEnemyLocked;
	DWORD		m_lockTime;
};


HRESULT DDCopyBitmap( LPDIRECTDRAWSURFACE, HBITMAP hbm, int x, int y, int dx, int dy);
HRESULT DDReLoadBitmap(LPDIRECTDRAWSURFACE, LPCSTR szBitmap);
HRESULT DDSetColorKey(LPDIRECTDRAWSURFACE, COLORREF);
DWORD DDColorMatch(LPDIRECTDRAWSURFACE, COLORREF);

#endif // !defined(AFX_GAME_H__18287D61_DB36_11D3_B12A_F67D0FBE8D25__INCLUDED_)
