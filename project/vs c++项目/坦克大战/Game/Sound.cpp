// DirectSound.cpp: implementation of the CDirectSound class.
//
//////////////////////////////////////////////////////////////////////

#include "Sound.h"
#include "wavread.h"

#define SAFE_RELEASE(x)		if(x){ x->Release(); x = NULL; }


static char szSoundEffects[NUM_SOUND_EFFECTS][40] =
{
	"Gunfire.wav",
	"Bang.wav",
	"Hit.wav",
	"Peow.wav",
	"Fanfare.wav",
};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDirectSound::CDirectSound()
{
	m_pDS = NULL;
	for( int i = 0; i < NUM_SOUND_EFFECTS; i ++ )
		m_pdsBuffer[i] = NULL;
}

CDirectSound::~CDirectSound()
{
	Destroy();
}


BOOL CDirectSound::Init( HWND hWnd )
{
	// Create DirectSound
	if( FAILED(DirectSoundCreate( NULL, &m_pDS, NULL )) )
		return FALSE;

	m_pDS->SetCooperativeLevel( hWnd, DSSCL_NORMAL );

	// Create Sound buffer
	CWaveSoundRead waveSound;
	char filename[MAX_PATH];

	for( int i = 0; i < NUM_SOUND_EFFECTS; i ++ )
	{
		lstrcpy( filename, "sound\\" );
		lstrcat( filename, szSoundEffects[i] );
		if( FAILED(waveSound.Open( filename )) )
			continue;
		
		waveSound.Reset();
		
		DSBUFFERDESC	dsbd;
		ZeroMemory( &dsbd, sizeof(dsbd) );
		dsbd.dwSize = sizeof(dsbd);
		dsbd.dwFlags = DSBCAPS_STATIC;
		dsbd.dwBufferBytes = waveSound.m_ckIn.cksize;
		dsbd.lpwfxFormat = waveSound.m_pwfx;

		if( FAILED(m_pDS->CreateSoundBuffer(&dsbd, &m_pdsBuffer[i], NULL)) )
		{
			waveSound.Close();
			Destroy();
			return FALSE;
		}

		LPVOID lpvAudio;
		DWORD  dwBytes;
		m_pdsBuffer[i]->Lock(
				0,
				0,
				&lpvAudio,
				&dwBytes,
				NULL,
				NULL,
				DSBLOCK_ENTIREBUFFER);
		
		UINT cbBytesRead;
		waveSound.Read( dwBytes, (LPBYTE)lpvAudio, &cbBytesRead );
	
		m_pdsBuffer[i]->Unlock( lpvAudio, dwBytes, NULL, 0 );

		waveSound.Close();
	}

	return TRUE;
}


BOOL CDirectSound::LoadEffect( EFFECT sfx )
{
	int idx = (int)sfx;

	CWaveSoundRead waveSound;
	char filename[MAX_PATH] = "sound\\";
	
	lstrcpy( filename, szSoundEffects[idx] );
	if( FAILED(waveSound.Open( filename )) )
		return FALSE;

	waveSound.Reset();
	
	LPVOID lpvAudio;
	DWORD  dwBytes;
	m_pdsBuffer[idx]->Lock(
			0,
			0,
			&lpvAudio,
			&dwBytes,
			NULL,
			NULL,
			DSBLOCK_ENTIREBUFFER);
		
	UINT cbBytesRead;
	waveSound.Read( dwBytes, (LPBYTE)lpvAudio, &cbBytesRead );
	
	m_pdsBuffer[idx]->Unlock( lpvAudio, dwBytes, NULL, 0 );

	waveSound.Close();

	return TRUE;
}


BOOL CDirectSound::Play( EFFECT sfx )
{
	HRESULT hr;
	int idx = (int)sfx;
	if( !m_pdsBuffer[idx] )
		return FALSE;

	m_pdsBuffer[idx]->SetCurrentPosition(0);
	hr = m_pdsBuffer[idx]->Play( 0, 0, 0 );
	if( hr == DSERR_BUFFERLOST )
	{
		hr = m_pdsBuffer[idx]->Restore();
		LoadEffect( sfx );
	}

	if( FAILED(hr) )
		return FALSE;
	return TRUE;
}


void CDirectSound::Stop( EFFECT sfx )
{
	int idx = (int)sfx;
	if( !m_pdsBuffer[idx] )
		return;

	m_pdsBuffer[idx]->Stop();
}


void CDirectSound::Destroy()
{
	for( int i = 0; i < NUM_SOUND_EFFECTS; i ++ )
		SAFE_RELEASE( m_pdsBuffer[i] );
	SAFE_RELEASE( m_pDS );
}