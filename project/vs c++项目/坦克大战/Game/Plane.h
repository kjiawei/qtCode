// Plane.h: interface for the CPlane class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLANE_H__10522B85_DB55_11D3_B12A_A4591823B325__INCLUDED_)
#define AFX_PLANE_H__10522B85_DB55_11D3_B12A_A4591823B325__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ddraw.h>

#define PLANE_W		13
#define PLANE_H		13
#define TILE_W		32
#define TILE_H		32

enum{
	OBJ_NULL = -1,
	OBJ_BRICK = 0,
	OBJ_CONCRETE = 1,
	OBJ_TREE = 2,
	OBJ_RIVER = 3,
	OBJ_HAWK = 5,
	OBJ_STONE
};


struct TILE
{
	char	obj;
	WORD	mask;
};

class CTank;
class CBullet;
class CPlane  
{
public:
	CPlane();
	virtual ~CPlane();

	BOOL Create( char* filename );
	void BitBlt( LPDIRECTDRAWSURFACE bmp ){ m_bmp = bmp; }
	BOOL CanHit( int surface )
	{
		return surface==OBJ_BRICK || surface==OBJ_CONCRETE;
	}
	BOOL CanDestroy( int row, int col, BOOL bDestroyConcrete )
	{
		return (m_map[row][col].obj == OBJ_BRICK ||
			m_map[row][col].obj == OBJ_CONCRETE && bDestroyConcrete);
	}	
	BOOL HitSurface( CBullet& bullet, BOOL bDestroyConcrete=FALSE );
	BOOL GetSurface( int row, int col, RECT& rcTank, int a, int b );
	int GetSurface( CTank& tank );
	void Draw( LPDIRECTDRAWSURFACE pdds );
	void DrawTree( LPDIRECTDRAWSURFACE pdds );
	void Protect();
	void Unprotect();
	void Bare();

private:
	TILE					m_map[PLANE_H][PLANE_W];
	LPDIRECTDRAWSURFACE		m_bmp;
	BOOL					m_bRiver1;
	DWORD					m_time;
	DWORD					m_protectTime;
	BOOL					m_bProtected;
};

#endif // !defined(AFX_PLANE_H__10522B85_DB55_11D3_B12A_A4591823B325__INCLUDED_)
