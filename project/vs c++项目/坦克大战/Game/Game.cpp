// Game.cpp: implementation of the CGame class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "Game.h"
#include "resource.h"


#define SCREEN_W		640
#define SCREEN_H		480
#define OFFSETX			100
#define OFFSETY			48
#define PLAYER1_STARTX	130
#define PLAYER1_STARTY	386
#define PLAYER2_STARTX	258
#define PLAYER2_STARTY	386


#define SAFE_RELEASE(x)		if(x){ x->Release(); x = NULL; }

CGame*	g_pGame;


inline int random( int min, int max )
{
	return (min + rand() % (max - min + 1));
}


void TRACE( LPCTSTR format, ... )
{
    char    buf[128];
    va_list vl;

    va_start(vl, format);
    sprintf(buf, format, vl);
    OutputDebugString( buf );
	va_end(vl);
}


void CGame::OutputText( int x, int y, LPCTSTR string )
{
	HDC hdc;
	if( m_pddsBackBuffer && 
		m_pddsBackBuffer->GetDC(&hdc) == DD_OK )
	{
		SetBkMode( hdc, TRANSPARENT );
		SetTextColor( hdc, RGB(255,255,0) );
		TextOut( hdc, x, y, string, lstrlen(string) );
		m_pddsBackBuffer->ReleaseDC( hdc );
	}
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CGame::CGame()
{
	m_hInst = NULL;
	m_hWnd = NULL;
	m_bActive = FALSE;
	m_bShowStats = FALSE;
	m_bFullScreen = TRUE;
	m_bSingle = TRUE;

	m_pDD = NULL;
	m_pddsFrontBuffer = NULL;
	m_pddsBackBuffer = NULL;
	g_pGame = this;
}

CGame::~CGame()
{

}


LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( g_pGame )
		return g_pGame->MsgProc( hWnd, uMsg, wParam, lParam );
	
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}


LRESULT CGame::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
	case WM_ACTIVATEAPP:
		if( m_bActive = (BOOL)wParam )
			m_DirectInput.Acquire();
		return 0;

	case WM_SETCURSOR:
		if( m_bFullScreen )
		{
			SetCursor( NULL );
			return TRUE;
		}
		break;

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

	case WM_MOVE:
		m_bActive = TRUE;
		GetClientRect( hWnd, &m_rcWindow );
		ClientToScreen( hWnd, (LPPOINT)&m_rcWindow );
		ClientToScreen( hWnd, (LPPOINT)&m_rcWindow + 1 );
		return 0;
		
	case WM_MOVING:
		m_bActive = FALSE;
		break;

	case WM_KEYDOWN:
		switch( wParam )
		{
		case VK_ESCAPE:
			if( m_gameState == GS_ACTIVE )
				m_gameState = GS_SPLASH;
			else if( m_gameState == GS_SPLASH )
				PostQuitMessage(0);
			else if( m_gameState == GS_OVER )
				m_gameState = GS_SPLASH;
			break;

		case VK_F4:
			DDTerm();
			m_bFullScreen = !m_bFullScreen;
			DDInit();
			return 0;

		case VK_F5:
			m_bShowStats = !m_bShowStats;
			return 0;
			
		case VK_DOWN:
		case VK_UP:
			if( m_gameState == GS_SPLASH )
			{
				m_bSingle = !m_bSingle;
				return 0;
			}
			break;
		
		case VK_PRIOR:
			if( m_gameState == GS_ACTIVE && m_nLevel > 1 )
			{
				m_nLevel --;
				InitLevel();
			}
			break;
		case VK_NEXT:
			if( m_gameState == GS_ACTIVE )
			{
				m_nLevel ++;
				InitLevel();
			}
			break;

		case VK_RETURN:
			if( m_gameState == GS_SPLASH )
			{
				ResetGame();
				return 0;
			}
			else if( m_gameState == GS_ACTIVE && !m_bSingle )
			{
				if( m_player[0].m_nLife > 1 &&
					m_player[1].m_nLife <= 0 )
				{
					m_player[0].m_nLife --;
					m_player[1].m_nLife = 1;
					ResetPlayer( m_player[1] );
				}
				else if( m_player[1].m_nLife > 1 &&
						 m_player[0].m_nLife <= 0 )
				{
					m_player[1].m_nLife --;
					m_player[0].m_nLife = 1;
					ResetPlayer( m_player[0] );
				}
			}
			break;
		}
		break;
	}

	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}


BOOL CGame::Initialize( HINSTANCE hInst )
{
	m_hInst = hInst;

	if( !InitApplication() || 
		!DDInit() ||
		!InitGame() )
	{
		DDTerm();
		return FALSE;
	}

	return TRUE;
}


BOOL CGame::InitApplication()
{
	char szClassName[] = "BATTLECITY";
	char szTitle[] = "Battle City";

	WNDCLASS wc;
	wc.hInstance = m_hInst;
	wc.lpszClassName = szClassName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_DBLCLKS;
	wc.hIcon = LoadIcon( m_hInst, MAKEINTRESOURCE(IDI_TANK) );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );

	if( !RegisterClass( &wc ) )
	{
		TRACE( "Error In RegisterClassEx\n" );
		return FALSE;
	}

	m_hWnd = CreateWindow( szClassName,
				szTitle,
				WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				646, 505,
				NULL,
				NULL,
				m_hInst,
				NULL );
	if( !m_hWnd )
	{
		TRACE( "Error In CreateWindow\n" );
		return FALSE;
	}
				
	UpdateWindow( m_hWnd );
	ShowWindow( m_hWnd, SW_NORMAL );

	return TRUE;
}


int CGame::Run()
{
	MSG	msg;

    while( TRUE )
    {
        if (PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE))
        {
            if (!GetMessage( &msg, NULL, 0, 0))
                break;

            TranslateMessage(&msg); 
            DispatchMessage(&msg);
        }
        else if( m_bActive )
        {
			UpdateFrame();
        }
        else
            WaitMessage();
    }
	
	DDTerm();
	return msg.wParam;
}



BOOL CGame::DDInit()
{
	HRESULT hr;

	hr = DirectDrawCreate( NULL, &m_pDD, NULL );
	if( FAILED(hr) )
	{
		TRACE( "Error Create DirectDraw\n" );
		return FALSE;
	}

	if( m_bFullScreen )
		m_pDD->SetCooperativeLevel( m_hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
	else
		m_pDD->SetCooperativeLevel( m_hWnd, DDSCL_NORMAL );

	if( m_bFullScreen )
	{
		if( FAILED(m_pDD->SetDisplayMode( 640, 480, 16 )) )
		{
			TRACE( "Error SetDiaplayMode\n" );
			return FALSE;
		}
	}

	DDSURFACEDESC	ddsd;
	ZeroMemory( &ddsd, sizeof(ddsd) );
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	if( m_bFullScreen )
	{
		ddsd.dwFlags |= DDSD_BACKBUFFERCOUNT;
		ddsd.ddsCaps.dwCaps |= DDSCAPS_FLIP | DDSCAPS_COMPLEX;
		ddsd.dwBackBufferCount = 1;
	}
	hr = m_pDD->CreateSurface( &ddsd, &m_pddsFrontBuffer, NULL );
	if( FAILED(hr) )
	{
		TRACE( "Error Create Front Buffer\n" );
		return FALSE;
	}

	if( m_bFullScreen )
	{
		DDSCAPS ddscaps;
		ZeroMemory( &ddscaps, sizeof(ddscaps) );
		ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
		m_pddsFrontBuffer->GetAttachedSurface( &ddscaps, &m_pddsBackBuffer );
	}
	else
		m_pddsBackBuffer = DDCreateSurface( SCREEN_W, SCREEN_H );

	if( !LoadBitmaps() )
		return FALSE;

	m_plane.BitBlt( m_pBmpList[0] );
	m_player[0].BitBlt( m_pBmpList[1], m_pBmpList[2], m_pBmpList[14], m_pBmpList[7] );
	m_player[1].BitBlt( m_pBmpList[9], m_pBmpList[2], m_pBmpList[14], m_pBmpList[7] );
	for( int i = 0; i < NUM_ENEMYS; i ++ )
		m_enemy[i].BitBlt( m_pBmpList[5], m_pBmpList[2], m_pBmpList[14], m_pBmpList[7] );
	for( i = 0; i < NUM_EXPLODES;  i ++ )
		m_explode[i].BitBlt( m_pBmpList[3], m_pBmpList[4] );
	m_bonus.BitBlt( m_pBmpList[6] );

	m_dwFillColor = DDColorMatch( m_pddsBackBuffer, RGB(128,128,128) );

	if( !m_bFullScreen )
	{
		SetWindowPos( m_hWnd, 0, 0, 0, 646, 505, SWP_NOMOVE | SWP_NOZORDER );
		m_rcWindow.right = m_rcWindow.left + 640;
		m_rcWindow.bottom = m_rcWindow.top + 480;
	}

	return TRUE;
}


//-----------------------------------------------------------------------------
// Name: DDLoadBitmap()
// Desc: Create a DirectDrawSurface from a bitmap resource.
//-----------------------------------------------------------------------------
LPDIRECTDRAWSURFACE CGame::DDLoadBitmap( LPCSTR szBitmap, int dx, int dy)
{
    HBITMAP                 hbm;
    BITMAP                  bm;
    DDSURFACEDESC			ddsd;
    LPDIRECTDRAWSURFACE		pdds;

    //
    //  Try to load the bitmap as a resource, if that fails, try it as a file
    //
    hbm = (HBITMAP) LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, dx,
                              dy, LR_CREATEDIBSECTION);
    if (hbm == NULL)
        hbm = (HBITMAP) LoadImage(NULL, szBitmap, IMAGE_BITMAP, dx, dy,
                                  LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if (hbm == NULL)
        return NULL;
    //
    // Get size of the bitmap
    //
    GetObject(hbm, sizeof(bm), &bm);
    //
    // Create a DirectDrawSurface for this bitmap
    //
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth = bm.bmWidth;
    ddsd.dwHeight = bm.bmHeight;
    if (m_pDD->CreateSurface(&ddsd, &pdds, NULL) != DD_OK)
        return NULL;
    DDCopyBitmap(pdds, hbm, 0, 0, 0, 0);
    DeleteObject(hbm);
    return pdds;
}


HRESULT DDCopyBitmap( LPDIRECTDRAWSURFACE pdds, 
						HBITMAP hbm, int x, int y, 
						int dx, int dy)
{
    HDC                     hdcImage;
    HDC                     hdc;
    BITMAP                  bm;
    DDSURFACEDESC			ddsd;
    HRESULT                 hr;

    if (hbm == NULL || pdds == NULL)
        return E_FAIL;
    //
    // Make sure this surface is restored.
    //
    pdds->Restore();
    //
    // Select bitmap into a memoryDC so we can use it.
    //
    hdcImage = CreateCompatibleDC(NULL);
    if (!hdcImage)
        TRACE("createcompatible dc failed\n");
    SelectObject(hdcImage, hbm);
    //
    // Get size of the bitmap
    //
    GetObject(hbm, sizeof(bm), &bm);
    dx = dx == 0 ? bm.bmWidth : dx;     // Use the passed size, unless zero
    dy = dy == 0 ? bm.bmHeight : dy;
    //
    // Get size of surface.
    //
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
    pdds->GetSurfaceDesc(&ddsd);

    if ((hr = pdds->GetDC(&hdc)) == DD_OK)
    {
        StretchBlt(hdc, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcImage, x, y,
                   dx, dy, SRCCOPY);
        pdds->ReleaseDC(hdc);
    }
    DeleteDC(hdcImage);
    return hr;
}


//-----------------------------------------------------------------------------
// Name: DDReLoadBitmap()
// Desc: Load a bitmap from a file or resource into a directdraw surface.
//       normaly used to re-load a surface after a restore.
//-----------------------------------------------------------------------------
HRESULT
DDReLoadBitmap(LPDIRECTDRAWSURFACE pdds, LPCSTR szBitmap)
{
    HBITMAP                 hbm;
    HRESULT                 hr;

    //
    //  Try to load the bitmap as a resource, if that fails, try it as a file
    //
    hbm = (HBITMAP) LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, 0,
                              0, LR_CREATEDIBSECTION);
    if (hbm == NULL)
        hbm = (HBITMAP) LoadImage(NULL, szBitmap, IMAGE_BITMAP, 0, 0,
                                  LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if (hbm == NULL)
    {
        OutputDebugString("handle is null\n");
        return E_FAIL;
    }
    hr = DDCopyBitmap(pdds, hbm, 0, 0, 0, 0);
    if (hr != DD_OK)
    {
        OutputDebugString("ddcopybitmap failed\n");
    }
    DeleteObject(hbm);
    return hr;
}


void CGame::DDTerm()
{
	for( int i = 0; i < NUM_BITMAPS; i ++ )
		SAFE_RELEASE( m_pBmpList[i] );	
	if( !m_bFullScreen )
		SAFE_RELEASE( m_pddsBackBuffer );
	SAFE_RELEASE( m_pddsFrontBuffer );
	SAFE_RELEASE( m_pDD );
}



void CGame::FlipScreen()
{
	HRESULT hr;
	
	if( m_bFullScreen )
		hr = m_pddsFrontBuffer->Flip( NULL, DDFLIP_WAIT );
	else
	{
		hr = m_pddsFrontBuffer->Blt( &m_rcWindow, m_pddsBackBuffer,
				NULL, DDBLT_WAIT, NULL );
	}

	if( hr == DDERR_SURFACELOST )
		RestoreSurfaces();
}


LPDIRECTDRAWSURFACE CGame::DDCreateSurface( int width, int height )
{
	DDSURFACEDESC	ddsd;
	ZeroMemory( &ddsd, sizeof(ddsd) );
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwWidth = width;
	ddsd.dwHeight = height;

	LPDIRECTDRAWSURFACE pdds;
	if( FAILED(m_pDD->CreateSurface( &ddsd, &pdds, NULL )) )
		return NULL;

	return pdds;
}


void CGame::RestoreSurfaces()
{
	m_pddsBackBuffer->Restore();
	m_pddsFrontBuffer->Restore();

	for( int i = 0; i < NUM_BITMAPS; i ++ )
		m_pBmpList[i]->Restore();

	DDReLoadBitmap( m_pBmpList[0], "graphics\\tile.bmp" );
	DDReLoadBitmap( m_pBmpList[1], "graphics\\player1.bmp" );
	DDReLoadBitmap( m_pBmpList[2], "graphics\\bullet.bmp" );
	DDReLoadBitmap( m_pBmpList[3], "graphics\\explode1.bmp" );
	DDReLoadBitmap( m_pBmpList[4], "graphics\\explode2.bmp" );
	DDReLoadBitmap( m_pBmpList[5], "graphics\\enemy.bmp" );
	DDReLoadBitmap( m_pBmpList[6], "graphics\\bonus.bmp" );
	DDReLoadBitmap( m_pBmpList[7], "graphics\\bore.bmp" );
	DDReLoadBitmap( m_pBmpList[8], "graphics\\misc.bmp" );
	DDReLoadBitmap( m_pBmpList[9], "graphics\\player2.bmp" );
	DDReLoadBitmap( m_pBmpList[10], "graphics\\splash.bmp" );
	DDReLoadBitmap( m_pBmpList[11], "graphics\\gameover.bmp" );
	DDReLoadBitmap( m_pBmpList[12], "graphics\\flag.bmp" );
	DDReLoadBitmap( m_pBmpList[13], "graphics\\num.bmp" );
	DDReLoadBitmap( m_pBmpList[14], "graphics\\shield.bmp" );
}


void CGame::DDClear( RECT* prc, DWORD dwFillColor )
{
	DDBLTFX	ddbfx;
	ZeroMemory( &ddbfx, sizeof(ddbfx) );
	ddbfx.dwSize = sizeof(ddbfx);
	ddbfx.dwFillColor = dwFillColor;
	
	m_pddsBackBuffer->Blt( prc, NULL, NULL, 
		DDBLT_COLORFILL | DDBLT_WAIT, &ddbfx );
}


void CGame::ProcessInput()
{
	static DWORD lastTick = timeGetTime();
	DWORD time = timeGetTime() - lastTick;
	CBullet* bullet;
	float x, y;
	DIRECTION dir;
	int surface;
	int i, j, k;
	lastTick = timeGetTime();
	
	
	// process player's input
	
	WORD input[2];
	m_DirectInput.GetKey( input[0], input[1] );

	for( k = 0; k < 2; k ++ )
	{
		if( !m_player[k].m_active )
			continue;

		x = m_player[k].m_x;
		y = m_player[k].m_y;
		dir = m_player[k].m_dir;

		if( !m_player[k].m_bBoring && m_gameState != GS_OVER )
		{
			if( m_player[k].ProcessInput(input[k], time) )
				m_DirectSound.Play( EFFECT_FIRE );
		}
		surface = m_plane.GetSurface( m_player[k] );
		if( surface != OBJ_NULL &&
			surface != OBJ_TREE )
		{
			m_player[k].m_x = x;
			m_player[k].m_y = y;
			m_player[k].m_dir = dir;
		}
		if( m_player[k].HitTest( m_player[!k], (int)x, (int)y ) )
		{
			// two players hit together 
			m_player[k].m_x = x;
			m_player[k].m_y = y;
			m_player[k].m_dir = dir;
		}
		
		for( i = 0; i < m_nMaxEnemys; i ++ )
		{
			if( m_player[k].HitTest( m_enemy[i], (int)x, (int)y ) )
			{
				// we hit the enemy
				m_player[k].m_x = x;
				m_player[k].m_y = y;
				m_player[k].m_dir = dir;
				break;
			}
		}
	
		if( m_player[k].HitTest( m_bonus ) )
		{
			// we hit the bonus
			EatBonus( m_player[k] );
		}

		// bullet
		for( j = 0; j < 2; j ++ )
		{
			bullet = &m_player[k].m_bullet[j];
			if( !bullet->m_active )
				continue;

			if( !bullet->Move() )
			{
				bullet->m_active = FALSE;
				continue;
			}
			int surface = m_plane.HitSurface( *bullet, m_player[k].m_type>=3 );
			if( surface == OBJ_BRICK )
			{
				bullet->m_active = FALSE;
				Explode( *bullet );
			}
			else if( surface == OBJ_CONCRETE )
			{
				bullet->m_active = FALSE;
				Explode( *bullet );
				m_DirectSound.Play( EFFECT_HIT );
			}
			else if( surface == OBJ_HAWK )
			{
				bullet->m_active = FALSE;
				Explode( *bullet, TRUE );
				m_DirectSound.Play( EFFECT_EXPLODE );
				m_gameState = GS_OVER;
			}
			
			if( !m_bSingle &&
				bullet->HitTest( m_player[!k] ) )
				
			{
				// We hit the other player
				bullet->m_active = FALSE;
				if( !m_player[!k].m_bShield )
					m_player[!k].Lock();
			}
			
			for( i = 0; i < m_nMaxEnemys; i ++ )
			{
				if( !m_enemy[i].m_bShield && !m_enemy[i].m_bBoring &&
					bullet->HitTest( m_enemy[i] ) )
				{
					// our bullet hit the enemy
					bullet->m_active = FALSE;
					Explode( *bullet );					
					if( m_enemy[i].m_bBonus )
					{
						m_enemy[i].m_bBonus = FALSE;
						BoreBonus();
					}

					if( m_enemy[i].m_type == 2 )
					{
						if( --m_enemy[i].m_level < 0 )
							m_enemy[i].m_active = FALSE;
					}
					else
						m_enemy[i].m_active = FALSE;

					if( !m_enemy[i].m_active )
					{
						// the enemy is dead
						Explode( m_enemy[i], TRUE );
						m_DirectSound.Play( EFFECT_EXPLODE );
						m_nEnemys --;
						m_player[k].m_nScore += (m_enemy[i].m_type+1) * 100;
					}
					break;
				}
				else if( bullet->HitTest( m_enemy[i].m_bullet[0] ) )
				{
					// our bullet hit the enemy's
					bullet->m_active = FALSE;
					m_enemy[i].m_bullet[0].m_active = FALSE;
					break;
				}
			}
		}
	}

	if( !m_bSingle )
	{
		for( i = 0; i < 2; i ++ )
			for( j = 0; j < 2; j ++ )
			{
				if( m_player[0].m_bullet[i].HitTest(
					m_player[1].m_bullet[j] ) )
				{
					// two players' bullet hit together
					m_player[0].m_bullet[i].m_active = FALSE;
					m_player[1].m_bullet[j].m_active = FALSE;
				}
			}
	}
				


	
	// process enemys
	for( i = 0; i < m_nMaxEnemys; i ++ )
	{
		if( !m_bEnemyLocked && !m_enemy[i].m_bBoring &&
			m_enemy[i].m_active )
		{
			x = m_enemy[i].m_x;
			y = m_enemy[i].m_y;
			dir = m_enemy[i].m_dir;
			
			if( rand() % 200 == 0 ||
				!m_enemy[i].Move() )
			{
				m_enemy[i].ChangeDirection();
			}
			
			surface = m_plane.GetSurface( m_enemy[i] );
			if( surface == OBJ_BRICK )
			{
				if( rand() % 100 < 30 )
				{
					m_enemy[i].ChangeDirection();
					surface = m_plane.GetSurface( m_enemy[i] );
				}
				else
					m_enemy[i].Fire();
			}
			else if( surface == OBJ_CONCRETE ||
					surface == OBJ_RIVER )
			{
				m_enemy[i].ChangeDirection();
				surface = m_plane.GetSurface( m_enemy[i] );
			}
			if( m_enemy[i].HitTest( m_player[0], (int)x, (int)y ) ||
				m_enemy[i].HitTest( m_player[1], (int)x, (int)y ) )
			{
				m_enemy[i].m_x = x;
				m_enemy[i].m_y = y;
				m_enemy[i].m_dir = dir;
				m_enemy[i].Fire();
			}
			else if( surface != OBJ_NULL && surface != OBJ_TREE )
			{
				m_enemy[i].m_x = x;
				m_enemy[i].m_y = y;
				m_enemy[i].m_dir = dir;
			}
			for( int j = 0; j < m_nMaxEnemys; j ++ )
			{
				if( i != j &&
					m_enemy[i].HitTest( m_enemy[j], (int)x, (int)y ) )
				{
					// two enemys hit each other
					m_enemy[i].ChangeDirection();
					if( m_enemy[i].HitTest( m_enemy[j], (int)x, (int)y ) )
					{
						m_enemy[i].m_x = x;
						m_enemy[i].m_y = y;
						m_enemy[i].m_dir = dir;
					}
					break;
				}
			}
			
			// the enemy can also eat the bonus
			if( m_enemy[i].HitTest( m_bonus ) )
				EatBonus( m_enemy[i] );
						
			if( rand() % 100 == 0 )
				m_enemy[i].Fire();
		}

		bullet = &m_enemy[i].m_bullet[0];
		if( bullet->m_active )
		{
			if( !bullet->Move() )
				bullet->m_active = FALSE;
	
			surface = m_plane.HitSurface( *bullet );
			if( surface == OBJ_BRICK ||
				surface == OBJ_CONCRETE )
			{
				bullet->m_active = FALSE;
				Explode( *bullet );
			}
			else if( surface == OBJ_HAWK )
			{
				bullet->m_active = FALSE;
				Explode( *bullet, TRUE );
				m_DirectSound.Play( EFFECT_EXPLODE );
				m_gameState = GS_OVER;
			}

			for( k = 0; k < 2; k ++ )
			{
				if( bullet->HitTest( m_player[k] ) )
				{
					// enemy's bullet hit us
					bullet->m_active = FALSE;
					if( !m_player[k].m_bShield )
					{
						Explode( *bullet );
						PlayerBeenHit( m_player[k] );
						m_DirectSound.Play( EFFECT_EXPLODE );
					}
				}
			}
		}
	}

	// produce some enemys...
	static DWORD lastTime;
	DWORD thisTime = timeGetTime();

	if( thisTime - lastTime > 3000 )
	{
		lastTime = thisTime;
		BoreEnemy();
	}

	// It's time to unlock the enemys
	if( m_bEnemyLocked &&
		thisTime - m_lockTime > 10000 )
	{
		m_bEnemyLocked = FALSE;
	}

	if( m_nEnemys <= 0 && m_gameState == GS_ACTIVE )
	{
		m_gameState = GS_WIN;
		m_lastTime = timeGetTime();
	}

	if( !m_player[0].m_active && !m_player[1].m_active )
		m_gameState = GS_OVER;
}


void CGame::DrawWorld()
{
	RECT rc;
	rc.left = OFFSETX;
	rc.right = rc.left + 416;
	rc.top = OFFSETY;
	rc.bottom = rc.top + 416;
	DDClear( &rc, 0x0 );
	
	rc.left = 0;
	rc.right = SCREEN_W;
	rc.top = 0;
	rc.bottom = OFFSETY;
	DDClear( &rc, m_dwFillColor );
	
	rc.top = OFFSETY + 416;
	rc.bottom = SCREEN_H;
	DDClear( &rc, m_dwFillColor );
	
	rc.left = 0;
	rc.right = OFFSETX;
	rc.top = OFFSETY;
	rc.bottom = rc.top + 416;
	DDClear( &rc, m_dwFillColor );
	
	rc.left = OFFSETX + 416;
	rc.right = SCREEN_W;
	DDClear( &rc, m_dwFillColor );
	
	m_plane.Draw( m_pddsBackBuffer );
	for( int i = 0; i < m_nMaxEnemys; i ++ )
		m_enemy[i].Draw( m_pddsBackBuffer );
	m_player[0].Draw( m_pddsBackBuffer );
	m_player[1].Draw( m_pddsBackBuffer );	
	m_plane.DrawTree( m_pddsBackBuffer );
	for( i = 0; i < NUM_EXPLODES; i ++ )
		m_explode[i].Draw( m_pddsBackBuffer );
	m_bonus.Draw( m_pddsBackBuffer );
	
	rc.left = 0;
	rc.top = 0;
	rc.right = 14;
	rc.bottom = 14;
	for( i = 0; i < m_nEnemysLeft; i ++ )
	{
		int x = 550 + i % 2 * 15;
		int y = 68 + i / 2 * 15;
		
		m_pddsBackBuffer->BltFast( x, y, m_pBmpList[8], &rc,
			DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
	}

	rc.left = 28;
	rc.right = rc.left + 28;
	m_pddsBackBuffer->BltFast( 550, 300, m_pBmpList[8], &rc,
			DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );

	m_pddsBackBuffer->BltFast( 20, 20, m_pBmpList[8], &rc,
			DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
	BltNumber( 70, 20, m_player[0].m_nScore );

	rc.left = 14;
	rc.right = rc.left + 14;
	m_pddsBackBuffer->BltFast( 550, 317, m_pBmpList[8], &rc,
		DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );

	BltNumber( 570, 317, m_player[0].m_nLife );

	if( !m_bSingle )
	{
		rc.left = 56;
		rc.right = rc.left + 28;
		m_pddsBackBuffer->BltFast( 550, 350, m_pBmpList[8],
			&rc, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
	
		m_pddsBackBuffer->BltFast( 480, 20, m_pBmpList[8], &rc,
			DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
		BltNumber( 530, 20, m_player[1].m_nScore );

		rc.left = 14;
		rc.right = rc.left + 14;
		m_pddsBackBuffer->BltFast( 550, 367, m_pBmpList[8],
			&rc, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );

		BltNumber( 570, 367, m_player[1].m_nLife );
	}

	// draw level No.
	m_pddsBackBuffer->BltFast( 550, 400, m_pBmpList[12], NULL,
			DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
	BltNumber( 580, 420, m_nLevel );
}


void CGame::BltNumber( int x, int y, int n )
{
	char szNum[20];
	sprintf( szNum, "%d", n );
	int len = lstrlen( szNum );

	for( int i = 0; i < len; i ++ )
	{
		RECT rc;
		rc.left = (szNum[i] - '0') * 14;
		rc.right = rc.left + 14;
		rc.top = 0;
		rc.bottom = 14;
		m_pddsBackBuffer->BltFast( x, y, m_pBmpList[13], &rc,
			DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );

		x += 15;
	}
}



void CGame::DoSplash()
{
	HRESULT hr;
	
	DDClear( NULL, 0 );

	hr = m_pddsBackBuffer->BltFast( 135, 130, m_pBmpList[10], NULL,
			DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
	if( hr == DDERR_SURFACELOST )
		RestoreSurfaces();

	RECT rc;
	rc.left = 0;
	rc.right = 28;
	rc.top = 28;
	rc.bottom = 56;
	m_pddsBackBuffer->BltFast( 200, 300 + 30*(!m_bSingle),
		m_pBmpList[1], &rc, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
}



void CGame::UpdateFrame()
{
	static DWORD lastTick = timeGetTime();
	static int frameCount;
	static float fps;

	if( m_gameState == GS_OVER || m_gameState == GS_ACTIVE ||
		m_gameState == GS_WIN )
		ProcessInput();

	switch( m_gameState )
	{
	case GS_SPLASH:
		DoSplash();
		break;
	
	case GS_OVER:
		DrawWorld();
		m_pddsBackBuffer->BltFast( 200, 200, m_pBmpList[11],
			NULL, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
		break;

	case GS_ACTIVE:
		DrawWorld();
		break;
		
	case GS_WIN:
		DrawWorld();
		
		if( timeGetTime() - m_lastTime > 3000 ||
			timeGetTime() < m_lastTime )
		{
			m_gameState = GS_ACTIVE;
			m_nLevel ++;
			InitLevel();
		}
		break;
	}

	frameCount ++;
	DWORD thisTick = timeGetTime();
	if( thisTick - lastTick > 1000 )
	{
		fps = (float)frameCount / (thisTick - lastTick) * 1000;
		frameCount = 0;
		lastTick = thisTick;
	}
	
	if( m_bShowStats )
	{
		// Show FPS
		char buf[255];
		sprintf( buf, "FPS: %.2f", fps );
		OutputText( 10, 10, buf );
	}
	
	FlipScreen();
}


void CGame::Explode( CSprite& sprite, BOOL bExplode )
{
	for( int i = 0; i < NUM_EXPLODES; i ++ )
		if( !m_explode[i].m_active )
		{
			int x = (int)sprite.m_x + sprite.m_width/2;
			int y = (int)sprite.m_y + sprite.m_height/2;
			m_explode[i].m_active = TRUE;
			m_explode[i].m_x = (float)(x - m_explode[i].m_width/2);
			m_explode[i].m_y = (float)(y - m_explode[i].m_height/2);
			m_explode[i].m_time = timeGetTime();
			m_explode[i].m_bExplode = bExplode;
			break;
		}
}


void CGame::EatBonus( CPlayer& player )
{
	m_DirectSound.Play( EFFECT_PICK );

	int i;
	switch( m_bonus.m_type )
	{
	case BONUS_LIFE:
		player.m_nLife ++;
		m_DirectSound.Play( EFFECT_LIFE );
		break;
	case BONUS_CLOCK:
		m_bEnemyLocked = TRUE;
		m_lockTime = timeGetTime();
		break;
	case BONUS_SHOVEL:
		m_plane.Protect();
		break;
	case BONUS_BOMB:
		for( i = 0; i < m_nMaxEnemys; i ++ )
			if( m_enemy[i].m_active &&
				!m_enemy[i].m_bBoring )
			{
				Explode( m_enemy[i], TRUE );
				m_enemy[i].m_active = FALSE;
				m_nEnemys --;
			}
		m_DirectSound.Play( EFFECT_EXPLODE );
		break;
	case BONUS_STAR:
		if( ++player.m_type > 3 )
			player.m_type = 3;
		break;
	case BONUS_HELMET:
		player.Shield( 10000 );
		break;
	}
	m_bonus.m_active = FALSE;
}


void CGame::PlayerBeenHit( CPlayer& player )
{
	if( !player.m_active )
		return;

	Explode( player, TRUE );
	if( --player.m_nLife <= 0 )
	{
		player.m_active = FALSE;
		return;
	}

	ResetPlayer( player );
	player.m_type = 0;
}


void CGame::EatBonus( CEnemy& enemy )
{
	switch( m_bonus.m_type )
	{
	case BONUS_LIFE:
		m_nEnemys += 5;
		m_nEnemysLeft += 5;
		break;

	case BONUS_CLOCK:
		m_player[0].Lock();
		m_player[1].Lock();
		break;

	case BONUS_SHOVEL:
		m_plane.Bare();
		break;

	case BONUS_BOMB:
		PlayerBeenHit( m_player[0] );
		PlayerBeenHit( m_player[1] );
		m_DirectSound.Play( EFFECT_EXPLODE );
		break;

	case BONUS_STAR:
		enemy.m_type = 2;
		enemy.m_level = 2;
		break;

	case BONUS_HELMET:
		enemy.Shield( 10000 );
		break;
	}
	m_bonus.m_active = FALSE;
}


BOOL CGame::BoreBonus()
{
	m_bonus.m_active = TRUE;
	int temp = rand() % 100;
	if( temp < 10 )
		m_bonus.m_type = BONUS_LIFE;
	else if( temp < 30 )
		m_bonus.m_type = BONUS_CLOCK;
	else if( temp < 50 )
		m_bonus.m_type = BONUS_SHOVEL;
	else if( temp < 65 )
		m_bonus.m_type = BONUS_BOMB;
	else if( temp < 85 )
		m_bonus.m_type = BONUS_STAR;
	else
		m_bonus.m_type = BONUS_HELMET;

	m_bonus.m_x = (float)random( 0, 416 - m_bonus.m_width );
	m_bonus.m_y = (float)random( 0, 416 - m_bonus.m_height );
	m_bonus.m_lastTime = 
	m_bonus.m_flickerTime = timeGetTime();

	return TRUE;
}


BOOL CGame::BoreEnemy()
{
	if( m_nEnemysLeft <= 0 )
		return FALSE;
	
	int which = random( 0, 4 );
	int x, y;

	for( int i = 0; i < m_nMaxEnemys; i ++ )
		if( !m_enemy[i].m_active )
		{
			switch( which )
			{
			case 0:
				x = 2; y = 2;
				break;
			case 1:
				x = 194; y = 2;
				break;
			case 2:
				x = 386; y = 2;
				break;
			case 3:
				x = 2; y = 160;
				break;
			case 4:
				x = 386; y = 160;
				break;
			}
			int temp = rand() % 100;
			if( temp < 50 )
			{
				m_enemy[i].m_type = 0;
				m_enemy[i].m_speed = 0.7f;
			}
			else if( temp < 80 )
			{
				m_enemy[i].m_type = 1;
				m_enemy[i].m_speed = 1.2f;
			}
			else
			{
				m_enemy[i].m_type = 2;
				m_enemy[i].m_speed = 0.5f;
			}
			m_enemy[i].m_x = (float)x;
			m_enemy[i].m_y = (float)y;
			m_enemy[i].m_dir = DIR_DOWN;
			if( m_nEnemysLeft == 4 ||
				m_nEnemysLeft == 11 ||
				m_nEnemysLeft == 18 )
			{
				m_enemy[i].m_bBonus = TRUE;
				m_enemy[i].m_redTime = 0;
			}
			else
				m_enemy[i].m_bBonus = FALSE;

			if( m_enemy[i].m_type == 2 )
				m_enemy[i].m_level = 2;

			m_enemy[i].Reborn();

			m_nEnemysLeft --;
			if( ++which > 2 )
				which = 0;
			return TRUE;
		}
	return FALSE;
}


BOOL CGame::LoadBitmaps()
{
	// Loading bitmaps...
	
	m_pBmpList[0] = DDLoadBitmap( "graphics\\tile.bmp" );
	DDSetColorKey( m_pBmpList[0], 0 );

	m_pBmpList[1] = DDLoadBitmap( "graphics\\player1.bmp" );
	DDSetColorKey( m_pBmpList[1], 0 );

	m_pBmpList[2] = DDLoadBitmap( "graphics\\bullet.bmp" );
	DDSetColorKey( m_pBmpList[2], 0 );
	
	m_pBmpList[3] = DDLoadBitmap( "graphics\\explode1.bmp" );
	DDSetColorKey( m_pBmpList[3], 0 );

	m_pBmpList[4] = DDLoadBitmap( "graphics\\explode2.bmp" );
	DDSetColorKey( m_pBmpList[4], 0 );

	m_pBmpList[5] = DDLoadBitmap( "graphics\\enemy.bmp" );
	DDSetColorKey( m_pBmpList[5], 0 );

	m_pBmpList[6] = DDLoadBitmap( "graphics\\bonus.bmp" );
	DDSetColorKey( m_pBmpList[6], 0 );

	m_pBmpList[7] = DDLoadBitmap( "graphics\\bore.bmp" );
	DDSetColorKey( m_pBmpList[7], 0 );
	
	m_pBmpList[8] = DDLoadBitmap( "graphics\\misc.bmp" );
	DDSetColorKey( m_pBmpList[8], RGB(255,255,255) );

	m_pBmpList[9] = DDLoadBitmap( "graphics\\player2.bmp" );
	DDSetColorKey( m_pBmpList[9], 0 );

	m_pBmpList[10] = DDLoadBitmap( "graphics\\splash.bmp" );
	DDSetColorKey( m_pBmpList[10], 0 );

	m_pBmpList[11] = DDLoadBitmap( "graphics\\gameover.bmp" );
	DDSetColorKey( m_pBmpList[11], 0 );

	m_pBmpList[12] = DDLoadBitmap( "graphics\\flag.bmp" );
	DDSetColorKey( m_pBmpList[12], RGB(255,255,255) );

	m_pBmpList[13] = DDLoadBitmap( "graphics\\num.bmp" );
	DDSetColorKey( m_pBmpList[13], RGB(255,255,255) );

	m_pBmpList[14] = DDLoadBitmap( "graphics\\shield.bmp" );
	DDSetColorKey( m_pBmpList[14], 0 );

	return TRUE;
}


//-----------------------------------------------------------------------------
// Name: DDColorMatch()
// Desc: Convert a RGB color to a pysical color.
//       We do this by leting GDI SetPixel() do the color matching
//       then we lock the memory and see what it got mapped to.
//-----------------------------------------------------------------------------
DWORD DDColorMatch(LPDIRECTDRAWSURFACE pdds, COLORREF rgb)
{
    COLORREF                rgbT;
    HDC                     hdc;
    DWORD                   dw = CLR_INVALID;
    DDSURFACEDESC			ddsd;
    HRESULT                 hres;

    //
    //  Use GDI SetPixel to color match for us
    //
    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
        rgbT = GetPixel(hdc, 0, 0);     // Save current pixel value
        SetPixel(hdc, 0, 0, rgb);       // Set our value
        pdds->ReleaseDC(hdc);
    }
    //
    // Now lock the surface so we can read back the converted color
    //
    ddsd.dwSize = sizeof(ddsd);
    while ((hres = pdds->Lock(NULL, &ddsd, 0, NULL)) == DDERR_WASSTILLDRAWING)
        ;
    if (hres == DD_OK)
    {
        dw = *(DWORD *) ddsd.lpSurface;                 // Get DWORD
        if (ddsd.ddpfPixelFormat.dwRGBBitCount < 32)
            dw &= (1 << ddsd.ddpfPixelFormat.dwRGBBitCount) - 1;  // Mask it to bpp
        pdds->Unlock(NULL);
    }
    //
    //  Now put the color that was there back.
    //
    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
        SetPixel(hdc, 0, 0, rgbT);
        pdds->ReleaseDC(hdc);
    }
    return dw;
}


//-----------------------------------------------------------------------------
// Name: DDSetColorKey()
// Desc: Set a color key for a surface, given a RGB.
//       If you pass CLR_INVALID as the color key, the pixel
//       in the upper-left corner will be used.
//-----------------------------------------------------------------------------
HRESULT DDSetColorKey(LPDIRECTDRAWSURFACE pdds, COLORREF rgb)
{
    DDCOLORKEY              ddck;

    ddck.dwColorSpaceLowValue = DDColorMatch(pdds, rgb);
    ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;
    return pdds->SetColorKey(DDCKEY_SRCBLT, &ddck);
}


void CGame::ResetPlayer( CPlayer& player )
{
	if( &player == &m_player[0] )
	{
		player.m_x = PLAYER1_STARTX;
		player.m_y = PLAYER1_STARTY;
	}
	else
	{
		player.m_x = PLAYER2_STARTX;
		player.m_y = PLAYER2_STARTY;
	}
	player.Reborn();
}



BOOL CGame::InitGame()
{
	srand( timeGetTime() );
	
	// initialize input devices
	m_DirectInput.Create( m_hInst, m_hWnd );
	
	// initizlize sound effects
	m_DirectSound.Init( m_hWnd );

	m_player[0].Create( 28, 28, TRUE );
	m_player[1].Create( 28, 28, TRUE );

	for( int i = 0; i < NUM_ENEMYS; i ++ )
		m_enemy[i].Create( 28, 28, FALSE );

	for( i = 0; i < NUM_EXPLODES;  i ++ )
		m_explode[i].Create( 28, 28, FALSE );

	m_bonus.Create( 30, 28, FALSE );

	m_gameState = GS_SPLASH;

	return TRUE;
}


void CGame::CleanUpGame()
{

}


BOOL CGame::InitLevel()
{
	char map[255];
	sprintf( map, "map\\level%d.map", m_nLevel );
	if( !m_plane.Create( map ) )
	{
		m_nLevel = 1;
		sprintf( map, "map\\level%d.map", m_nLevel );
		if( !m_plane.Create( map ) )
			return FALSE;
	}

	if( m_player[0].m_nLife > 0 )
		ResetPlayer( m_player[0] );
	if( m_bSingle )
		m_player[1].m_active = FALSE;
	else if( m_player[1].m_nLife > 0 )
		ResetPlayer( m_player[1] );

	m_player[0].m_bullet[0].m_active = FALSE;
	m_player[0].m_bullet[1].m_active = FALSE;
	m_player[1].m_bullet[0].m_active = FALSE;
	m_player[1].m_bullet[1].m_active = FALSE;


	for( int i = 0; i < NUM_ENEMYS; i ++ )
	{
		m_enemy[i].m_active = FALSE;
		m_enemy[i].m_bullet[0].m_active = FALSE;
	}
	for( i = 0; i < NUM_EXPLODES; i ++ )
		m_explode[i].m_active = FALSE;
	m_bonus.m_active = FALSE;

	m_bEnemyLocked = FALSE;
	m_nEnemysLeft = m_nEnemys = 20;

	return TRUE;
}


BOOL CGame::ResetGame()
{
	m_player[0].m_nLife = 3;
	m_player[0].m_type = 0;
	m_player[0].m_nScore = 0;

	if( !m_bSingle )
	{
		m_player[1].m_nLife = 3;
		m_player[1].m_type = 0;
		m_player[1].m_nScore = 0;
		m_nMaxEnemys = 6;
	}
	else
		m_nMaxEnemys = 4;

	m_gameState = GS_ACTIVE;

	m_nLevel = 1;
	return InitLevel();
}



///////////////////////////////////////////////////////
//		Main entry point for win32 application
///////////////////////////////////////////////////////

int WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR lpCmdLine,
				   int nCmdShow )
{
	CGame	game;
	
	game.Initialize( hInst );
	return game.Run();
}
