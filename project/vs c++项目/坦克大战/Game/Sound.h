// DirectSound.h: interface for the CDirectSound class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECTSOUND_H__07C9F9E1_E0C6_11D3_B12A_9C25C7091C25__INCLUDED_)
#define AFX_DIRECTSOUND_H__07C9F9E1_E0C6_11D3_B12A_9C25C7091C25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <dsound.h>

#define NUM_SOUND_EFFECTS	5

enum EFFECT
{
	EFFECT_FIRE,
	EFFECT_EXPLODE,
	EFFECT_HIT,
	EFFECT_PICK,
	EFFECT_LIFE
};


class CDirectSound  
{
public:
	CDirectSound();
	~CDirectSound();

	BOOL	Init( HWND hWnd );
	void	Destroy();
	BOOL	Play( EFFECT sfx );
	void	Stop( EFFECT sfx );
	BOOL	LoadEffect( EFFECT sfx );

private:
	LPDIRECTSOUND			m_pDS;
	LPDIRECTSOUNDBUFFER		m_pdsBuffer[NUM_SOUND_EFFECTS];
};

#endif // !defined(AFX_DIRECTSOUND_H__07C9F9E1_E0C6_11D3_B12A_9C25C7091C25__INCLUDED_)
