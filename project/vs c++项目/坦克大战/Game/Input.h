// Input.h: interface for the CDirectInput class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INPUT_H__81DD96A4_AFE9_11D3_B12A_ED3DDE047E66__INCLUDED_)
#define AFX_INPUT_H__81DD96A4_AFE9_11D3_B12A_ED3DDE047E66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <dinput.h>

#define KEY_UP				0x0001
#define	KEY_RIGHT			0x0002
#define KEY_DOWN			0x0004
#define KEY_LEFT			0x0008
#define KEY_DIRECTION		0x000f
#define KEY_FIRE			0x0010

class CDirectInput  
{
friend BOOL CALLBACK EnumJoystickCB( LPCDIDEVICEINSTANCE pdinst, LPVOID pvRef );

public:
	CDirectInput();
	virtual ~CDirectInput();

	BOOL	Create( HINSTANCE hInst, HWND hWnd );
	void	Destroy();
	BOOL	Acquire();
	BOOL	GetKey( WORD& input1, WORD& input2 );

private:
	LPDIRECTINPUT			m_pDI;
	LPDIRECTINPUTDEVICE		m_pdevKeyboard;
	LPDIRECTINPUTDEVICE2	m_pdevJoystick;
};

#endif // !defined(AFX_INPUT_H__81DD96A4_AFE9_11D3_B12A_ED3DDE047E66__INCLUDED_)
