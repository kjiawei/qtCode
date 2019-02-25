// Sprite.cpp: implementation of the CSprite class.
//
//////////////////////////////////////////////////////////////////////

#include "Sprite.h"
#include "Input.h"

#define	MAX_X		416.0f
#define MAX_Y		416.0f
#define TILE_W		32
#define TILE_H		32
#define BULLET_W	8
#define BULLET_H	8
#define OFFSETX		100
#define OFFSETY		48

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSprite::CSprite()
{

}


BOOL CSprite::HitTest( CSprite& sprite )
{
	if( !m_active || !sprite.m_active )
		return FALSE;
	
	RECT rc1, rc2, temp;
	
	rc1.left = (int)m_x;
	rc1.right = rc1.left + m_width;
	rc1.top = (int)m_y;
	rc1.bottom = rc1.top + m_height;
	
	rc2.left = (int)sprite.m_x;
	rc2.right = rc2.left + sprite.m_width;
	rc2.top = (int)sprite.m_y;
	rc2.bottom = rc2.top + sprite.m_height;

	return IntersectRect( &temp, &rc1, &rc2 );
}


void CSprite::Draw( LPDIRECTDRAWSURFACE pdds )
{
	if( !m_active )
		return;

	int x = (int)m_x + OFFSETX;
	int y = (int)m_y + OFFSETY;
	pdds->BltFast( x, y, m_bmp, NULL, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
}


void CBore::Draw( LPDIRECTDRAWSURFACE pdds )
{
	if( !m_active )
		return;

	RECT rc;
	rc.left = m_frame * m_width;
	rc.right = rc.left + m_width;
	rc.top = 0;
	rc.bottom = rc.top + m_height;
	int x = (int)m_x + OFFSETX;
	int y = (int)m_y + OFFSETY;

	pdds->BltFast( x, y, m_bmp, &rc, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );

	if( timeGetTime() - m_time > 100 )
	{
		m_time = timeGetTime();
		if( m_bAdvance )
		{
			if( ++m_frame > 3 )
			{
				m_frame = 2;
				m_bAdvance = FALSE;
			}
		}
		else
		{
			if( --m_frame < 0 )
			{
				m_frame = 1;
				m_bAdvance = TRUE;
			}
		}
	}
}


void CExplode::Draw( LPDIRECTDRAWSURFACE pdds )
{
	if( !m_active )
		return;

	DWORD time = timeGetTime() - m_time;
	int x = (int)m_x - 20 + OFFSETX;
	int y = (int)m_y - 20 + OFFSETY;

	if( m_bExplode )
	{
		if( time < 50 || time > 150 )
			CSprite::Draw( pdds );
		else
			pdds->BltFast( x, y, m_explode, NULL, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
		if( time > 200 )
			m_active = FALSE;
	}
	else
	{
		CSprite::Draw( pdds );
		if( time > 70 )
			m_active = FALSE;
	}
}


void CBonus::Draw( LPDIRECTDRAWSURFACE pdds )
{
	static BOOL bShow;
	
	if( !m_active )
		return;
	
	if( timeGetTime() - m_flickerTime > 200 )
	{
		m_flickerTime = timeGetTime();
		bShow = !bShow;
	}	
	
	if( bShow )
	{
		RECT rc;
		rc.left = (int)m_type * m_width;
		rc.right = rc.left + m_width;
		rc.top = 0;
		rc.bottom = m_height;

		pdds->BltFast( (int)m_x + OFFSETX, (int)m_y + OFFSETY,
			m_bmp, &rc, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
	}

	if( timeGetTime() - m_lastTime > 10000 )
		m_active = FALSE;
}


CBullet::CBullet()
{
	m_dir = DIR_UP;
	m_speed = 0;
}


BOOL CBullet::Move()
{
	if( !m_active )
		return FALSE;
	
	float offset = m_speed;
	switch( m_dir )
	{
	case DIR_UP:
		m_y -= offset;
		break;
	case DIR_DOWN:
		m_y += offset;
		break;
	case DIR_LEFT:
		m_x -= offset;
		break;
	case DIR_RIGHT:
		m_x += offset;
		break;
	}
	
	if( m_x >= 0 && m_x + m_width <= MAX_X &&
		m_y >= 0 && m_y + m_height <= MAX_Y )
		return TRUE;

	if( m_x < 0 )
		m_x = 0;
	else if( m_x + m_width > MAX_X )
		m_x = MAX_X - m_width;
	if( m_y < 0 )
		m_y = 0;
	else if( m_y + m_height > MAX_Y )
		m_y = MAX_Y - m_height;

	return FALSE;
}


void CBullet::Draw( LPDIRECTDRAWSURFACE pdds )
{
	if( !m_active )
		return;
	
	RECT rc;
	rc.left = (int)m_dir * m_width;
	rc.top = 0;
	rc.right = rc.left + m_width;
	rc.bottom = m_height;
	int x = (int)m_x + OFFSETX;
	int y = (int)m_y + OFFSETY;
	
	pdds->BltFast( x, y, m_bmp, &rc, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
}


CTank::CTank()
{
	m_bullet[0].Create( BULLET_W, BULLET_H, FALSE );
	m_bullet[1].Create( BULLET_W, BULLET_H, FALSE );	
	m_time = 0;
	m_frame = 0;
}


void CTank::ChangeDirection( DIRECTION dir )
{
	if( m_dir != dir )
	{
		m_dir = dir;
		int row = (int)m_y / TILE_H;
		int col = (int)m_x / TILE_W;
		int xoffset = (int)m_x % TILE_W;
		int yoffset = (int)m_y % TILE_H;
		if( xoffset <= 10 )
			m_x = (float)(col * TILE_W + 2);
		else if( xoffset < TILE_W - 6 )
			m_x = (float)(col * TILE_W + 18);
		else
			m_x = (float)(col * TILE_W + 34);

		if( yoffset <= 10 )
			m_y = (float)(row * TILE_H + 2);
		else if( yoffset < TILE_H - 6 )
			m_y = (float)(row * TILE_H + 18);
		else
			m_y = (float)(row * TILE_H + 34);
	}
}



BOOL CTank::HitTest( CTank& sprite, int oldx, int oldy )
{
	if( !m_active || !sprite.m_active ||
		m_bBoring || sprite.m_bBoring )
		return FALSE;
	
	int x1 = (int)sprite.m_x;
	int y1 = (int)sprite.m_y;
	int x2 = x1 + sprite.m_width;
	int y2 = y1 + sprite.m_height;
	int newx = (int)m_x;
	int newy = (int)m_y;
	switch( m_dir )
	{
	case DIR_UP:
		if( newx <= x2 && newx + m_width >= x1 &&
			oldy >= y2 && newy <= y2 )
			return TRUE;
		break;
	case DIR_DOWN:
		if( newx <= x2 && newx + m_width >= x1 &&
			oldy + m_height <= y1 && newy + m_height >= y1 )
			return TRUE;
		break;
	case DIR_RIGHT:
		if( newy <= y2 && newy + m_height >= y1 &&
			oldx + m_width <= x1 && newx + m_width >= x1 )
			return TRUE;
		break;
	case DIR_LEFT:
		if( newy <= y2 && newy + m_height >= y1 &&
			oldx >= x2 && newx <= x2 )
			return TRUE;
		break;
	}

	return FALSE;
}


void CTank::DrawShield( LPDIRECTDRAWSURFACE pdds )
{
	RECT rc;
	rc.left = 0;
	rc.top = m_bShield1 * 32;
	rc.right = rc.left + 32;
	rc.bottom = rc.top + 32;
	int x = (int)m_x - 2 + OFFSETX;
	int y = (int)m_y - 2 + OFFSETY;
	
	pdds->BltFast( x, y, m_bmpShield, &rc, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
	
	if( timeGetTime() - m_flickerTime > 50 )
	{
		m_bShield1 = !m_bShield1;
		m_flickerTime = timeGetTime();
	}
	if( timeGetTime() - m_shieldTime > m_maxTime )
		m_bShield = FALSE;
}


void CEnemy::ChangeDirection()
{
	CTank::ChangeDirection( (DIRECTION)(rand() % 4) );
}


BOOL CEnemy::Fire()
{
	if( m_bullet[0].m_active ||
		timeGetTime() - m_time < 150 )
		return FALSE;

	m_time = timeGetTime();
	m_bullet[0].m_active = TRUE;
	m_bullet[0].m_speed = 3.0f;
	m_bullet[0].m_dir = m_dir;
	
	switch( m_dir )
	{
	case DIR_UP:
		m_bullet[0].m_x = m_x + m_width/2 - 4;
		m_bullet[0].m_y = m_y;
		break;
	case DIR_DOWN:
		m_bullet[0].m_x = m_x + m_width/2 - 4;
		m_bullet[0].m_y = m_y + m_height - 8;
		break;
	case DIR_LEFT:
		m_bullet[0].m_x = m_x;
		m_bullet[0].m_y = m_y + m_height/2 - 4;
		break;
	case DIR_RIGHT:
		m_bullet[0].m_x = m_x + m_width - 8;
		m_bullet[0].m_y = m_y + m_height/2 - 4;
	}
	return TRUE;
}


void CEnemy::Reborn()
{ 
	m_active = TRUE;
	m_bShield = FALSE;
	m_bBoring = TRUE;
	m_bore.m_x = m_x - 2;
	m_bore.m_y = m_y - 2;
	m_bore.Bore();
	m_shieldTime = timeGetTime();
}


void CEnemy::Draw( LPDIRECTDRAWSURFACE pdds )
{
	if( !m_active )
		return;

	if( m_bBoring )
	{
		m_bore.Draw( pdds );
		if( timeGetTime() - m_shieldTime > 800 )
			m_bBoring = FALSE;
		return;
	}

	if( m_bBonus &&
		timeGetTime() - m_redTime > 80 )
	{	
		m_redTime = timeGetTime();
		m_bShowRed = !m_bShowRed;
	}

	int x = (int)m_x + OFFSETX;
	int y = (int)m_y + OFFSETY;
	RECT rc;
	if( m_bBonus && m_bShowRed )
	{
		switch( m_type )
		{
		case 0:
		case 1:
			rc.top = (int)m_dir * m_height;
			rc.left = (2 + m_frame + 4*m_type) * m_width;
			break;
		case 2:
			rc.top = ((int)m_dir + 4) * m_height;
			rc.left = 6 * m_width;
			break;
		}
		rc.right = rc.left + m_width;
		rc.bottom = rc.top + m_height;
		pdds->BltFast( x, y, m_bmp, &rc, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
	}
	else
	{
		switch( m_type )
		{
		case 0:
		case 1:
			rc.top = (int)m_dir * m_height;
			rc.left = (m_type * 4 + m_frame) * m_width;
			break;
		case 2:
			rc.left = ((2-m_level)*2 + m_frame) * m_width;
			rc.top = ((int)m_dir + 4) * m_height;
			break;
		}
		rc.right = rc.left + m_width;
		rc.bottom = rc.top + m_height;
		pdds->BltFast( x, y, m_bmp, &rc, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
	}

	if( m_bShield )
		DrawShield( pdds );
	m_bullet[0].Draw( pdds );
}


BOOL CPlayer::Fire()
{
	float speed;
	switch( m_type )
	{
	case 0:
		speed = 3.0f;
		break;
	case 1:
		speed = 4.0f;
		break;
	case 2:
	case 3:
		speed = 5.0f;
		break;
	}

	if( timeGetTime() - m_time < 200 )
		return FALSE;
	
	for( int i = 0; i < 2; i ++ )
		if( !m_bullet[i].m_active )
			break;
	if( i >= 2 ||
		i != 0 && m_type < 2)
		return FALSE;

	m_time = timeGetTime();
	m_bullet[i].m_active = TRUE;
	m_bullet[i].m_speed = speed;
	m_bullet[i].m_dir = m_dir;
	
	switch( m_dir )
	{
	case DIR_UP:
		m_bullet[i].m_x = m_x + m_width/2 - 4;
		m_bullet[i].m_y = m_y + 4;
		break;
	case DIR_DOWN:
		m_bullet[i].m_x = m_x + m_width/2 - 4;
		m_bullet[i].m_y = m_y + m_height - 12;
		break;
	case DIR_LEFT:
		m_bullet[i].m_x = m_x + 4;
		m_bullet[i].m_y = m_y + m_height/2 - 4;
		break;
	case DIR_RIGHT:
		m_bullet[i].m_x = m_x + m_width - 12;
		m_bullet[i].m_y = m_y + m_height/2 - 4;
	}
	return TRUE;
}



BOOL CPlayer::ProcessInput( WORD input, DWORD time )
{
	if( !m_bLocked )
	{
		DIRECTION dir;
		if( input & KEY_UP )
			dir = DIR_UP;
		else if( input & KEY_DOWN )
			dir = DIR_DOWN;
		else if( input & KEY_LEFT )
			dir = DIR_LEFT;
		else if( input & KEY_RIGHT )
			dir = DIR_RIGHT;
	
		if( input & KEY_DIRECTION )
		{
			if( m_dir == dir )
				Move();
			else
				ChangeDirection( dir );
		}
	}

	if( input & KEY_FIRE )
		return Fire();

	return FALSE;
}


void CPlayer::Reborn()
{ 
	m_active = TRUE;
	m_bShield = TRUE;
	m_bBoring = TRUE;
	m_bLocked = FALSE;
	m_bore.m_x = m_x - 2;
	m_bore.m_y = m_y - 2;
	m_bore.Bore();
	m_shieldTime = timeGetTime();
	m_dir = DIR_UP;
	m_speed = 1.0f;
}



void CPlayer::Draw( LPDIRECTDRAWSURFACE pdds )
{
	if( !m_active )
		return;
	
	if( m_bBoring )
	{
		m_bore.Draw( pdds );
		if( timeGetTime() - m_shieldTime > 800 )
		{
			m_bBoring = FALSE;
			Shield( 3000 );
		}
		return;
	}

	if( m_bLocked )
	{
		if( timeGetTime() - m_flickerTime > 200 )
		{
			m_bShow = !m_bShow;
			m_flickerTime = timeGetTime();
		}
		else if( timeGetTime() - m_shieldTime > 5000 )
			m_bLocked = FALSE;
	}
	
	if( !m_bLocked || m_bShow )
	{
		RECT rc;
		rc.left = (m_type * 2 + m_frame) * m_width;
		rc.top = (int)m_dir * m_height;
		rc.right = rc.left + m_width;
		rc.bottom = rc.top + m_height;
		int x = (int)m_x + OFFSETX;
		int y = (int)m_y + OFFSETY;

		pdds->BltFast( x, y, m_bmp, &rc, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
	}
		
	if( m_bShield )
		DrawShield( pdds );
	m_bullet[0].Draw( pdds );
	m_bullet[1].Draw( pdds );
}