#pragma once
#include "windows.h"

class CGameEngine
{
protected:
    CGameEngine();

private:
    static CGameEngine* m_pGameEngine;

public:
    static CGameEngine* Instance();
    static const WORD GAME_RESOLUTION_X;
    static const WORD GAME_RESOLUTION_Y;
    HRESULT Initialize(HINSTANCE hInstance, HWND hWnd);
    HRESULT Uninitialize();
    HRESULT ExecuteSingleFrame();
};