#pragma once

#include "windows.h"
#include "fmod.hpp"
#include "CContent.h"

class CAudio
{
private:
    static CAudio* m_pInstance;
    CAudio();
    FMOD::System* m_pSystem;
    FMOD::Sound** m_ppBackgroundSongs; // array of pointers to background songs
    USHORT m_cBackgroundSongs;         // count of background songs

public:
    static CAudio* Instance();
    HRESULT InitializeFMOD();
    HRESULT Update();
    struct Callbacks
    {      
        static HRESULT AllocSoundPointers(void*** pppVoid, USHORT count);
        static HRESULT LoadSingleSound(void** ppVoid, void* pDevice, CContent::FileStream* pFileStream);
    };
};