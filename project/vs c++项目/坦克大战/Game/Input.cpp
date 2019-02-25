// Input.cpp: implementation of the CDirectInput class.
//
//////////////////////////////////////////////////////////////////////

#include "Input.h"

#define SAFE_RELEASE(x)		if(x) { x->Release(); x = NULL; }

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDirectInput::CDirectInput()
{
	m_pDI = NULL;
	m_pdevKeyboard = NULL;
	m_pdevJoystick = NULL;
}

CDirectInput::~CDirectInput()
{
	Destroy();
}


BOOL CDirectInput::Create( HINSTANCE hInst, HWND hWnd )
{
	HRESULT hr;

	// Create DirectInput object
	hr = DirectInputCreate( hInst, DIRECTINPUT_VERSION, &m_pDI, NULL );
	if( FAILED(hr) )
		return FALSE;

	// Initialize keyboard...
	hr = m_pDI->CreateDevice( GUID_SysKeyboard, &m_pdevKeyboard, NULL );
	if( FAILED(hr) )
	{
		Destroy();
		return FALSE;
	}

	m_pdevKeyboard->SetDataFormat( &c_dfDIKeyboard );

	m_pdevKeyboard->SetCooperativeLevel( hWnd, 
			DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );

	// acquire keyboard
	m_pdevKeyboard->Acquire();


	
	// enum joystick devices
	m_pDI->EnumDevices( DIDEVTYPE_JOYSTICK, EnumJoystickCB,
			(LPVOID)this, DIEDFL_ATTACHEDONLY );

	if( m_pdevJoystick )
	{
		m_pdevJoystick->SetDataFormat( &c_dfDIJoystick );
		
		m_pdevJoystick->SetCooperativeLevel( hWnd,
			DISCL_FOREGROUND | DISCL_EXCLUSIVE );
		
		// Set the range of the joystick axes tp [-1000,+1000]
		DIPROPRANGE diprg; 
		diprg.diph.dwSize       = sizeof(DIPROPRANGE); 
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
		diprg.diph.dwHow        = DIPH_BYOFFSET; 
		diprg.lMin              = -10; 
		diprg.lMax              = +10; 
		
		diprg.diph.dwObj = DIJOFS_X;    // Set the x-axis range
		m_pdevJoystick->SetProperty( DIPROP_RANGE, &diprg.diph );
		
		diprg.diph.dwObj = DIJOFS_Y;    // Set the y-axis range
		m_pdevJoystick->SetProperty( DIPROP_RANGE, &diprg.diph );
		
		// Set the dead zone for the joystick axes (because many joysticks
		// aren't perfectly calibrated to be zero when centered).
		DIPROPDWORD dipdw; 
		ZeroMemory( &dipdw, sizeof(dipdw) );
		dipdw.diph.dwSize       = sizeof(DIPROPDWORD); 
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
		dipdw.diph.dwHow        = DIPH_DEVICE; 
		dipdw.dwData            = 9000;
		
		dipdw.diph.dwObj = DIJOFS_X;    // Set the x-axis deadzone
		m_pdevJoystick->SetProperty( DIPROP_DEADZONE, &dipdw.diph );
		
		dipdw.diph.dwObj = DIJOFS_Y;    // Set the y-axis deadzone
		m_pdevJoystick->SetProperty( DIPROP_DEADZONE, &dipdw.diph );
		
		// acquire joystick
		m_pdevJoystick->Acquire();
	}

	return TRUE;
}


void CDirectInput::Destroy()
{
	if( m_pdevKeyboard )
		m_pdevKeyboard->Unacquire();
	if( m_pdevJoystick )
		m_pdevJoystick->Unacquire();
	SAFE_RELEASE( m_pdevKeyboard );
	SAFE_RELEASE( m_pdevJoystick );
	SAFE_RELEASE( m_pDI );
}


BOOL CDirectInput::Acquire()
{
	if( !m_pdevKeyboard || 
		FAILED(m_pdevKeyboard->Acquire()) )
		return FALSE;

	if( m_pdevJoystick )
		m_pdevJoystick->Acquire();
	
	return TRUE;
}


BOOL CDirectInput::GetKey( WORD& input1, WORD& input2 )
{
#define KEYDOWN(key)	(buffer[key] & 0x80)
	
	// Read keyboard data...
	HRESULT hr;
	char buffer[256];

	// We have not read any data yet
	input1 = input2 = 0;

	hr = m_pdevKeyboard->GetDeviceState( sizeof(buffer), &buffer );
	if( FAILED(hr) )
	{
		if( hr == DIERR_INPUTLOST )
			hr = Acquire();
		
		return FALSE;
	}

	if( KEYDOWN( DIK_UP ) )
		input1 |= KEY_UP;
	else if( KEYDOWN( DIK_DOWN ) )
		input1 |= KEY_DOWN;
	else if( KEYDOWN( DIK_LEFT ) )
		input1 |= KEY_LEFT;
	else if( KEYDOWN( DIK_RIGHT ) )
		input1 |= KEY_RIGHT;
	if( KEYDOWN( DIK_NUMPAD0 ) )
		input1 |= KEY_FIRE;

	if( KEYDOWN( DIK_E ) )
		input2 |= KEY_UP;
	else if( KEYDOWN( DIK_D ) )
		input2 |= KEY_DOWN;
	else if( KEYDOWN( DIK_S ) )
		input2 |= KEY_LEFT;
	else if( KEYDOWN( DIK_F ) )
		input2 |= KEY_RIGHT;
	if( KEYDOWN( DIK_SPACE ) )
		input2 |= KEY_FIRE;


	if( m_pdevJoystick )
	{
		DIJOYSTATE	js;
		
		// poll the joystick to read the current state
		m_pdevJoystick->Poll();
		
		// get data from the joystick
		hr = m_pdevJoystick->GetDeviceState( sizeof(js), &js );
		if( FAILED(hr) )
		{
			// did the read fail because we lost input for some reason? 
			// if so, then attempt to reacquire. If the second acquire 
			// fails, then the error from GetDeviceData will be 
			// DIERR_NOTACQUIRED, so we won't get stuck an infinite loop.
			if( hr = DIERR_INPUTLOST )
				hr = Acquire();
			
			return FALSE;
		}

		if( js.lX < 0 )
			input1 |= KEY_LEFT;
		else if( js.lX > 0 )
			input1 |= KEY_RIGHT;
		else if( js.lY < 0 )
			input1 |= KEY_UP;
		else if( js.lY > 0 )
			input1 |= KEY_DOWN;
		if( js.rgbButtons[0] & 0x80 )
			input1 |= KEY_FIRE;
	}

	return TRUE;
}



BOOL CALLBACK EnumJoystickCB( LPCDIDEVICEINSTANCE pdinst, 
							   LPVOID pvRef )
{
	CDirectInput* p = (CDirectInput*)pvRef;
	LPDIRECTINPUTDEVICE pdev;

	if( FAILED(p->m_pDI->CreateDevice( pdinst->guidInstance, &pdev, NULL)) )
		return DIENUM_CONTINUE;

	pdev->QueryInterface( IID_IDirectInputDevice2, (LPVOID *)&p->m_pdevJoystick );
	return DIENUM_STOP;
}