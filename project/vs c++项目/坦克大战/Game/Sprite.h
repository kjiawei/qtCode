// Sprite.h: interface for the CSprite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPRITE_H__6DC846C1_DC07_11D3_B12A_831AB3E93B25__INCLUDED_)
#define AFX_SPRITE_H__6DC846C1_DC07_11D3_B12A_831AB3E93B25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ddraw.h>

class CSprite  
{
public:
	CSprite();
	void Create( int w, int h, BOOL active )
	{
		m_width = w;
		m_height = h; 
		m_active = active;
	}
	void BitBlt( LPDIRECTDRAWSURFACE bmp ){ m_bmp = bmp; }
	BOOL HitTest( CSprite& sprite );	
	void Draw( LPDIRECTDRAWSURFACE pdds );

public:
	LPDIRECTDRAWSURFACE m_bmp;
	BOOL	m_active;
	float	m_x;
	float	m_y;
	int		m_width;
	int		m_height;
};


enum BONUS
{
	BONUS_LIFE,
	BONUS_CLOCK,
	BONUS_SHOVEL,
	BONUS_BOMB,
	BONUS_STAR,
	BONUS_HELMET
};


class CBonus : public CSprite
{
public:
	void Draw( LPDIRECTDRAWSURFACE pdds );

	BONUS	m_type;
	DWORD	m_lastTime;
	DWORD	m_flickerTime;
};

class CExplode: public CSprite
{
public:
	void BitBlt( LPDIRECTDRAWSURFACE bmp1, LPDIRECTDRAWSURFACE bmp2 )
	{
		m_bmp = bmp1;
		m_explode = bmp2;
	}
	void Draw( LPDIRECTDRAWSURFACE pdds );
	
	LPDIRECTDRAWSURFACE m_explode;
	BOOL	m_bExplode;
	DWORD	m_time;
};


class CBore : public CSprite
{
public:
	void Draw( LPDIRECTDRAWSURFACE pdds );
	void Bore()
	{
		m_active = TRUE;
		m_bAdvance = TRUE;
		m_frame = 0;
		m_time = timeGetTime();
	}

	int	  m_frame;
	DWORD m_time;
	BOOL  m_bAdvance;
};


enum DIRECTION
{
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT
};

class CBullet: public CSprite
{
public:
	CBullet();
	BOOL Move();
	void Draw( LPDIRECTDRAWSURFACE pdds );

	DIRECTION	m_dir;
	float		m_speed;
};



class CTank: public CBullet
{
public:
	CTank();
	void Create( int w, int h, BOOL active )
	{
		CBullet::Create( w, h, active );
		m_bore.Create( 32, 32, TRUE );
	}	
	void BitBlt( LPDIRECTDRAWSURFACE tank, LPDIRECTDRAWSURFACE bullet,
				LPDIRECTDRAWSURFACE shield, LPDIRECTDRAWSURFACE bore )
	{
		m_bmp = tank;
		m_bmpShield = shield;
		m_bullet[0].BitBlt( bullet );
		m_bullet[1].BitBlt( bullet );
		m_bore.BitBlt( bore );
	}
	void ChangeDirection( DIRECTION dir );
	BOOL Move(){ m_frame = !m_frame; return CBullet::Move(); }
	BOOL HitTest( CTank& sprite, int oldx, int oldy );
	BOOL HitTest( CSprite& sprite ){ return CSprite::HitTest(sprite); }
	void DrawShield( LPDIRECTDRAWSURFACE pdds );
	void Draw( LPDIRECTDRAWSURFACE pdds );
	void Shield( DWORD time )
	{
		m_bShield1 = TRUE;
		m_bShield = TRUE;
		m_maxTime = time;
		m_shieldTime = m_flickerTime = timeGetTime();
	}

	LPDIRECTDRAWSURFACE m_bmpShield;
	CBullet m_bullet[2];
	DWORD	m_time;
	int		m_frame;
	int		m_type;
	BOOL	m_bShield;
	BOOL	m_bShield1;
	DWORD	m_maxTime;
	DWORD	m_shieldTime;
	DWORD	m_flickerTime;
	BOOL	m_bBoring;
	CBore	m_bore;
};


class CEnemy : public CTank
{
public:
	void ChangeDirection();
	BOOL Fire();
	void Reborn();
	void Draw( LPDIRECTDRAWSURFACE pdds );

	BOOL	m_bBonus;
	BOOL	m_bShowRed;
	DWORD	m_redTime;
	int		m_level;
};



class CPlayer : public CTank
{
public:
	BOOL ProcessInput( WORD input, DWORD time );
	BOOL Fire();
	void Draw( LPDIRECTDRAWSURFACE pdds );
	void Reborn();
	void Lock()
	{ 
		m_bLocked = TRUE;
		m_shieldTime = m_flickerTime = timeGetTime();
	}

	int		m_nLife;
	int		m_nScore;
	BOOL	m_bLocked;
	BOOL	m_bShow;		// for flickering when locked
};


#endif // !defined(AFX_SPRITE_H__6DC846C1_DC07_11D3_B12A_831AB3E93B25__INCLUDED_)
