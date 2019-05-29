#include "CSound.h"

//
// Static members
//
CSound* CSound::m_pInstance = NULL;
CSound* CSound::Instance()
{
    if (NULL == m_pInstance)
    {    
        m_pInstance = new CSound();
    }

    return m_pInstance;
}

//
// Private members
//

// Constructor - private
CSound::CSound()
{
    m_piDirectSound8 = NULL;
    m_piDirectSoundBuffer8 = NULL;
}

//
// Public members
//
HRESULT CSound::InitializeDirectSound(HWND hWnd)
{
    HRESULT hr = DirectSoundCreate8(NULL, &m_piDirectSound8, NULL);
    if (SUCCEEDED(hr))
    {
        hr = m_piDirectSound8->SetCooperativeLevel(hWnd, DSSCL_PRIORITY);
        if (SUCCEEDED(hr))
        {
            hr = CreateBasicBuffer(m_piDirectSound8, &m_piDirectSoundBuffer8);
        }
    }

    return hr;
}

HRESULT CSound::UninitializeDirectSound()
{
    if (NULL != m_piDirectSoundBuffer8)
    {
        m_piDirectSoundBuffer8->Release();
        m_piDirectSoundBuffer8 = NULL;
    }

    if (NULL != m_piDirectSound8)
    {
        m_piDirectSound8->Release();
        m_piDirectSound8 = NULL;
    }

    return S_OK;
}

HRESULT CSound::PlaySound()
{
    //
    // TODO: Starting at position 64 removes the audio crackling.  WHY!?
    //
    HRESULT hr = m_piDirectSoundBuffer8->SetCurrentPosition(64);
    if (SUCCEEDED(hr))
    {
        hr =m_piDirectSoundBuffer8->Play(
            0,  // Unused.
            0,  // Priority for voice management.
            0   // Flags.
            ); 
    }

    return S_OK;
}

//
// Private members
//
HRESULT CSound::CreateBasicBuffer(IDirectSound8* piDirectSound, LPDIRECTSOUNDBUFFER* ppDsb8)
{
    //
    // Load the wave file from disk into memory
    //
    BYTE* pFileBuffer = NULL;
    DWORD dwFileBufferSize = 0;
    HRESULT hr = CContent::LoadFileToMemory("30935__aust_paul__possiblelazer.wav", &pFileBuffer, &dwFileBufferSize);
    if (SUCCEEDED(hr))
    {
        // Set up WDSBUFFERDESC dsbdesc; AV format structure.
        WAVEFORMATEX wfx; 
        memset(&wfx, 0, sizeof(WAVEFORMATEX)); 
        wfx.wFormatTag = WAVE_FORMAT_PCM;
        wfx.nChannels = 2;
        //wfx.nSamplesPerSec = 88200 * 2;
        wfx.nSamplesPerSec = 44100;        
        wfx.wBitsPerSample = 16;
        wfx.nBlockAlign = (wfx.nChannels * wfx.wBitsPerSample) / 8;
        wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

        // Set up DSBUFFERDESC structure.
        DSBUFFERDESC dsbdesc;
        memset(&dsbdesc, 0, sizeof(DSBUFFERDESC)); 
        dsbdesc.dwSize = sizeof(DSBUFFERDESC); 
        dsbdesc.dwFlags = DSBCAPS_CTRLPAN       | DSBCAPS_CTRLVOLUME |
                          DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS; 
        dsbdesc.dwBufferBytes = dwFileBufferSize; 
        dsbdesc.lpwfxFormat = &wfx; 
 
        // Create buffer.
        hr = piDirectSound->CreateSoundBuffer(&dsbdesc, ppDsb8, NULL);
        if (SUCCEEDED(hr)) 
        {
            //
            // TODO: Seems like sound still works without the call to QueryInterface...
            //       Investigate if we really need this call at all.
            //
            hr = (*ppDsb8)->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*) ppDsb8);
            if (SUCCEEDED(hr))
            {
                LPVOID lpvWrite;
                DWORD  dwLength;
                hr = (*ppDsb8)->Lock(
                        0,          // Offset at which to start lock.
                        dsbdesc.dwBufferBytes, // Size of lock; ignored because of flag.
                        &lpvWrite,  // Gets address of first part of lock.
                        &dwLength,  // Gets size of first part of lock.
                        NULL,       // Address of wraparound not needed. 
                        NULL,       // Size of wraparound not needed.
                        0);         // Flag.
                if (SUCCEEDED(hr))
                {
                    memcpy(lpvWrite, pFileBuffer, dwFileBufferSize);
                    (*ppDsb8)->Unlock(
                        lpvWrite,   // Address of lock start.
                        dwLength,   // Size of lock.
                        NULL,       // No wraparound portion.
                        0);         // No wraparound size.
                }
            }
        }

        //
        // Cleanup
        //
        delete [] pFileBuffer;
        pFileBuffer = NULL;
    }

    return hr;
}