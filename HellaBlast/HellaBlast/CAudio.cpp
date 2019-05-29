#include "CAudio.h"

//
// Static members
//
CAudio* CAudio::m_pInstance = NULL;
CAudio* CAudio::Instance()
{
    if (NULL == m_pInstance)
    {    
        m_pInstance = new CAudio();
    }

    return m_pInstance;
}

//
// Private members
//

// Constructor - private
CAudio::CAudio()
{
    m_ppBackgroundSongs = NULL; // array of pointers to background songs
    m_cBackgroundSongs = 0;     // count of background songs
}

//
// Public members
//
HRESULT CAudio::InitializeFMOD()
{
    FMOD_RESULT fResult;
    fResult = FMOD::System_Create(&m_pSystem);
    if (FMOD_OK == fResult)
    {
        fResult = m_pSystem->init(100, FMOD_INIT_NORMAL, 0);
        if (FMOD_OK == fResult)
        {
            HRESULT hr = CContent::LoadModulesFromFileStreamList(
                CContent::ContentTypeBackgroundSong,
                m_pSystem,
                reinterpret_cast<void***>(&m_ppBackgroundSongs),
                &m_cBackgroundSongs,
                &CAudio::Callbacks::AllocSoundPointers,
                &CAudio::Callbacks::LoadSingleSound
                );
            if (SUCCEEDED(hr))
            {
                //
                // Temporary engine test - For now we simultaneously play all songs that
                // are found within the content pipeline
                //
                for (USHORT i = 0; i < m_cBackgroundSongs; i++)
                {
                    FMOD::Sound* pSound = m_ppBackgroundSongs[i];
                    fResult = m_pSystem->playSound(FMOD_CHANNEL_FREE, pSound, false, NULL);
                    if (FMOD_OK != fResult)
                    {
                        break;
                    }
                }
            }
        }
    }

    return fResult;
}

HRESULT CAudio::Update()
{
    //
    // FMOD::System::update() must be called once every frame of your game loop
    //
    return m_pSystem->update();
}

HRESULT CAudio::Callbacks::AllocSoundPointers(void*** pppVoid, USHORT count)
{
    if (NULL == pppVoid || 0 == count)
    {
        return E_INVALIDARG;
    }

    HRESULT hr;
    FMOD::Sound*** pppSounds = reinterpret_cast<FMOD::Sound***>(pppVoid);
    *pppSounds = new FMOD::Sound* [count];
    if (NULL != *pppSounds)
    {
        ZeroMemory(*pppSounds, sizeof(FMOD::Sound*) * count);
        hr = S_OK;
    }
    else
    {
        hr = E_OUTOFMEMORY;
    }

    return hr;
}

HRESULT CAudio::Callbacks::LoadSingleSound(void** ppVoid, void* pDevice, CContent::FileStream* pFileStream)
{
    if (NULL == ppVoid || NULL == pDevice || NULL == pFileStream)
    {
        return E_INVALIDARG;
    }

    FMOD::System* pSystem = reinterpret_cast<FMOD::System*>(pDevice);
    FMOD_CREATESOUNDEXINFO exinfo = {0};
    exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.length = pFileStream->cbBuffer;
    FMOD_RESULT fmodResult = pSystem->createSound(
        reinterpret_cast<const char*>(pFileStream->pStream),
        FMOD_OPENMEMORY | FMOD_CREATESTREAM,
        &exinfo,
        reinterpret_cast<FMOD::Sound**>(ppVoid)
        );
    
    return (FMOD_OK == fmodResult) ? S_OK : E_FAIL;
}