// Plane.cpp: implementation of the CPlane class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "Plane.h"
#include "Sprite.h"

#define OFFSETX		100
#define OFFSETY		48


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlane::CPlane()
{
	m_bRiver1 = TRUE;
	m_time = 0;
	m_bProtected = FALSE;
}

CPlane::~CPlane()
{

}


BOOL CPlane::Create( char* filename )
{
	FILE* fp = fopen( filename, "rb" );
	if( !fp )
		return FALSE;

	for( int i = 0; i < PLANE_H; i ++ )
		for( int j = 0; j < PLANE_W; j ++ )
		{
			m_map[i][j].obj = (BYTE)fgetc( fp );
			m_map[i][j].obj --;
			m_map[i][j].mask = 0xffff;
			if( m_map[i][j].obj == OBJ_BRICK ||
				m_map[i][j].obj == OBJ_CONCRETE )
			{
				switch( (BYTE)fgetc( fp ) )
				{
				case 0:
					m_map[i][j].mask = 0xff00;
					break;
				case 1:
					m_map[i][j].mask = 0x00ff;
					break;
				case 2:
					m_map[i][j].mask = 0xcccc;
					break;
				case 3:
					m_map[i][j].mask = 0x3333;
					break;
				}
			}
			else if( m_map[i][j].obj == OBJ_NULL )
				m_map[i][j].mask = 0;
		}

	fclose( fp );
	
	Unprotect();
	return TRUE;
}


int CPlane::HitSurface( CBullet& bullet, BOOL bDestroyConcrete )
{
	int x = (int)bullet.m_x + bullet.m_width/2;
	int y = (int)bullet.m_y + bullet.m_height/2;
	int row = y / TILE_H;
	int col = x / TILE_W;

	int shift;
	WORD mask, flag;
	int hit = OBJ_NULL;
	
	switch( bullet.m_dir )
	{
	case DIR_UP:
	case DIR_DOWN:
		if( !bDestroyConcrete )
			shift = (3 - (y - row*TILE_H) / 8) * 4;
		else
			shift = (1 - (y - row*TILE_H) / 16) * 8;
		
		if( x % TILE_W )
		{
			if( !bDestroyConcrete )
				flag = 0xf << shift;
			else
				flag = 0xff << shift;
			if( m_map[row][col].mask & flag )
			{
				hit = m_map[row][col].obj;
				if( CanDestroy(row, col, bDestroyConcrete) )
					m_map[row][col].mask &= ~flag;
			}
		}
		else
		{
			if( !bDestroyConcrete )
				flag = 0xc << shift;
			else
				flag = 0xcc << shift;
			if( m_map[row][col].mask & flag )
			{
				hit = m_map[row][col].obj;
				if( CanDestroy(row, col, bDestroyConcrete) )
					m_map[row][col].mask &= ~flag;
			}

			if( !bDestroyConcrete )
				flag = 0x3 << shift;
			else
				flag = 0x33 << shift;
			if( col >= 1 && m_map[row][col-1].mask & flag )
			{
				if( !CanHit( hit ) )
					hit = m_map[row][col-1].obj;
				if( CanDestroy(row, col-1, bDestroyConcrete) )
					m_map[row][col-1].mask &= ~flag;
			}
		}
		if( col >= 1 && m_map[row][col-1].mask == 0 )
			m_map[row][col-1].obj = OBJ_NULL;
		break;

	case DIR_LEFT:
	case DIR_RIGHT:
		if( !bDestroyConcrete )
			shift = (x - col*TILE_W) / 8;
		else
			shift = (x - col*TILE_W) / 16;
		if( y % TILE_H )
		{
			if( !bDestroyConcrete )
			{
				if( shift == 0 )
					mask = 0x8888;
				else if( shift == 1 )
					mask = 0x4444;
				else if( shift == 2 )
					mask = 0x2222;
				else
					mask = 0x1111;
			}
			else
			{
				if( shift == 0 )
					mask = 0xcccc;
				else
					mask = 0x3333;
			}
			if( m_map[row][col].mask & mask )
			{
				hit = m_map[row][col].obj;
				if( CanDestroy(row, col, bDestroyConcrete) )
					m_map[row][col].mask &= ~mask;
			}
		}
		else
		{
			if( !bDestroyConcrete )
			{
				if( shift == 0 )
					mask = 0x8800;
				else if( shift == 1 )
					mask = 0x4400;
				else if( shift == 2 )
					mask = 0x2200;
				else
					mask = 0x1100;
			}
			else
			{
				if( shift == 0 )
					mask = 0xcc00;
				else
					mask = 0x3300;
			}
			if( m_map[row][col].mask & mask )
			{
				hit = m_map[row][col].obj;
				if( CanDestroy(row, col, bDestroyConcrete) )
					m_map[row][col].mask &= ~mask;
			}
			mask >>= 8;

			if( row >= 1 && m_map[row-1][col].mask & mask )
			{
				if( !CanHit( hit ) )
					hit = m_map[row-1][col].obj;
				if( CanDestroy(row-1, col, bDestroyConcrete) )
					m_map[row-1][col].mask &= ~mask;
			}
		}
		if( row >= 1 && m_map[row-1][col].mask == 0 )
			m_map[row-1][col].obj = OBJ_NULL;
		break;
	}
	if( m_map[row][col].mask == 0 )
		m_map[row][col].obj = OBJ_NULL;

	if( hit == OBJ_HAWK )
		m_map[12][6].obj = OBJ_STONE;

	return hit;
}


BOOL CPlane::GetSurface( int row, int col, RECT& rcTank, int a, int b)
{
	char obj = m_map[row][col].obj;
	if( obj == OBJ_NULL || obj == OBJ_TREE )
		return FALSE;
	
	WORD mask = m_map[row][col].mask;
	WORD flag;
	for( int i = 0; i < 4; i ++ )
	{
		if( (i == a || i == b) ||
			(a == -1 && b == -1) )
		{
			RECT rc, temp;
			rc.left = col * TILE_W + i % 2 * 16;
			rc.right = rc.left + 16;
			rc.top = row * TILE_H + i / 2 * 16;
			rc.bottom = rc.top + 16;
			switch( i )
			{
			case 0:
				flag = 0xcc00;
				break;
			case 1:
				flag = 0x3300;
				break;
			case 2:
				flag = 0x00cc;
				break;
			case 3:
				flag = 0x0033;
			}
			if( (mask & flag) && 
				IntersectRect( &temp, &rcTank, &rc ) )
				return TRUE;
		}
	}
	return FALSE;
}


int CPlane::GetSurface( CTank& tank )
{
	int x1 = (int)tank.m_x;
	int y1 = (int)tank.m_y;
	int x2 = x1 + tank.m_width;
	int y2 = y1 + tank.m_height;
	int x = x1 + tank.m_width/2;
	int y = y1 + tank.m_height/2;
	int row, col;
	RECT rcTank;
	rcTank.left = (int)tank.m_x;
	rcTank.right = rcTank.left + tank.m_width;
	rcTank.top = (int)tank.m_y;
	rcTank.bottom = rcTank.top + tank.m_height;

	if( tank.m_dir == DIR_UP || tank.m_dir == DIR_DOWN )
	{
		col = x / TILE_W;
		if( tank.m_dir == DIR_UP )
			row = y1 / TILE_H;
		else
			row = y2 / TILE_H;
		if( x % TILE_W )
		{
			if( GetSurface( row, col, rcTank, -1, -1 ) )
				return m_map[row][col].obj;
		}
		else
		{
			if( GetSurface( row, col-1, rcTank, 1, 3 ) )
				return m_map[row][col-1].obj;
			if( GetSurface( row, col, rcTank, 0, 2 ) )
				return m_map[row][col].obj;
		}
	}
	else
	{
		row = y / TILE_H;
		if( tank.m_dir == DIR_LEFT )
			col = x1 / TILE_W;
		else
			col = x2 / TILE_W;
		if( y % TILE_H )
		{
			if( GetSurface( row, col, rcTank, -1, -1 ) )
				return m_map[row][col].obj;
		}
		else
		{
			if( GetSurface( row-1, col, rcTank, 2, 3 ) )
				return m_map[row-1][col].obj;
			if( GetSurface( row, col, rcTank, 0, 1 ) )
				return m_map[row][col].obj;
		}
	}
	return OBJ_NULL;
}


void CPlane::Draw( LPDIRECTDRAWSURFACE pdds )
{
	for( int i = 0; i < PLANE_H; i ++ )
		for( int j = 0; j < PLANE_W; j ++ )
		{
			int x = j * TILE_W + OFFSETX;
			int y = i * TILE_H + OFFSETY;
			int obj = m_map[i][j].obj;
			WORD mask = m_map[i][j].mask;
			if( obj == OBJ_NULL || obj == OBJ_TREE )
				continue;

			RECT rc;
			rc.left = obj * TILE_W;
			rc.right = rc.left + TILE_W;
			rc.top = 0;
			rc.bottom = TILE_H;

			if( mask == 0xffff )
			{
				if( obj == OBJ_RIVER && !m_bRiver1 )
				{
					RECT rcRiver;
					rcRiver.left = rc.left + TILE_W;
					rcRiver.right = rcRiver.left + TILE_W;
					rcRiver.top = 0;
					rcRiver.bottom = TILE_H;
					pdds->BltFast( x, y, m_bmp, &rcRiver, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
				}
				else
					pdds->BltFast( x, y, m_bmp, &rc, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
			}
			else
			{
				for( int cnt = 0; cnt < 16; cnt ++ )
				{
					if( mask & 0x8000 )
					{	
						rc.left = obj * TILE_W + cnt % 4 * 8;
						rc.top = cnt / 4 * 8;
						rc.right = rc.left + 8;
						rc.bottom = rc.top + 8;
						pdds->BltFast( x + cnt%4*8, y + cnt/4*8,
							m_bmp, &rc, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
					}
					mask <<= 1;
				}
			}
		}
	if( timeGetTime() - m_time > 500 )
	{
		m_bRiver1 = !m_bRiver1;
		m_time = timeGetTime();
	}

	if( m_bProtected &&
		timeGetTime() - m_protectTime > 20000 )
	{
		Unprotect();
	}
}


void CPlane::DrawTree( LPDIRECTDRAWSURFACE pdds )
{
	for( int i = 0; i < PLANE_H; i ++ )
		for( int j = 0; j < PLANE_W; j ++ )
		{
			int obj = m_map[i][j].obj;
			if( obj == OBJ_TREE )
			{
				int x = j * TILE_W + OFFSETX;
				int y = i * TILE_H + OFFSETY;
				RECT rc;
				rc.left = obj * TILE_W;
				rc.right = rc.left + TILE_W;
				rc.top = 0;
				rc.bottom = TILE_H;
				pdds->BltFast( x, y, m_bmp, &rc, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
			}
		}
}



void CPlane::Protect()
{
	m_map[12][5].obj = OBJ_CONCRETE;
	m_map[12][5].mask = 0x3333;
	m_map[11][5].obj = OBJ_CONCRETE;
	m_map[11][5].mask = 0x0033;
	m_map[11][6].obj = OBJ_CONCRETE;
	m_map[11][6].mask = 0x00ff;
	m_map[11][7].obj = OBJ_CONCRETE;
	m_map[11][7].mask = 0x00cc;
	m_map[12][7].obj = OBJ_CONCRETE;
	m_map[12][7].mask = 0xcccc;

	m_protectTime = timeGetTime();
	m_bProtected = TRUE;
}


void CPlane::Unprotect()
{
	m_map[12][5].obj = OBJ_BRICK;
	m_map[12][5].mask = 0x3333;
	m_map[11][5].obj = OBJ_BRICK;
	m_map[11][5].mask = 0x0033;
	m_map[11][6].obj = OBJ_BRICK;
	m_map[11][6].mask = 0x00ff;
	m_map[11][7].obj = OBJ_BRICK;
	m_map[11][7].mask = 0x00cc;
	m_map[12][7].obj = OBJ_BRICK;
	m_map[12][7].mask = 0xcccc;
	m_bProtected = FALSE;
}


void CPlane::Bare()
{
	m_map[12][5].obj = OBJ_NULL;
	m_map[12][5].mask = 0;
	m_map[11][5].obj = OBJ_NULL;
	m_map[11][5].mask = 0;
	m_map[11][6].obj = OBJ_NULL;
	m_map[11][6].mask = 0;
	m_map[11][7].obj = OBJ_NULL;
	m_map[11][7].mask = 0;
	m_map[12][7].obj = OBJ_NULL;
	m_map[12][7].mask = 0;
	m_bProtected = FALSE;
}