#pragma once
#include "windows.h"
#include "dsound.h"
#include "CContent.h"

class CSound
{
public:
    static CSound* Instance();
    HRESULT InitializeDirectSound(HWND hWnd);
    HRESULT UninitializeDirectSound();
    HRESULT PlaySound();

private:
    static CSound* m_pInstance;
    IDirectSound8* m_piDirectSound8;
    LPDIRECTSOUNDBUFFER m_piDirectSoundBuffer8;
    HRESULT CreateBasicBuffer(IDirectSound8* piDirectSound, LPDIRECTSOUNDBUFFER* ppDsb8);

    //
    // Constructor
    //
    CSound();    
};