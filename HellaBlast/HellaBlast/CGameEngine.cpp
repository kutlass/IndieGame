#include "CGameEngine.h"
#include "CGraphics.h"
#include "CInput.h"
#include "CGameWorld.h"
#include "CGameObject.h"
#include "CSound.h"
#include "CAudio.h"
#include "CContent.h"

//
// Static members
//
CGameEngine::CGameEngine() {}
CGameEngine* CGameEngine::m_pGameEngine = NULL;
const WORD CGameEngine::GAME_RESOLUTION_X = 1440;
const WORD CGameEngine::GAME_RESOLUTION_Y = 900;

CGameEngine* CGameEngine::Instance()
{
    if (NULL == m_pGameEngine)
    {
        m_pGameEngine = new(CGameEngine);
    }

    return m_pGameEngine;
}

HRESULT CGameEngine::Initialize(HINSTANCE hInstance, HWND hWnd)
{
    //
    // Initialze DirectX components
    //
    HRESULT hr = E_FAIL;
    char szCabFileName[] = "JetPak.cab";
    char szCabFileDir[] = "..\\..\\JetEditProjects\\tst\\";
    hr = CContent::Instance()->LoadContent(szCabFileName, szCabFileDir);
    BOOL fResult = CGraphics::Instance()->InitializeDirect3D(hWnd);
    if (TRUE == fResult)
    {
        hr = CInput::Instance()->InitializeDirectInput(hInstance, hWnd);
        if (SUCCEEDED(hr))
        {
            WORD const NUM_ACTIONS = 5;
            ACTION_INFO rgActionInfo[NUM_ACTIONS];
            ZeroMemory(rgActionInfo, sizeof(ACTION_INFO) * NUM_ACTIONS);
            rgActionInfo[0].actionType = MoveUp;
            rgActionInfo[0].dwKeyAssignment = DIK_W;
            rgActionInfo[0].actionTriggerCondition = KeyPressed;

            rgActionInfo[1].actionType = MoveDown;
            rgActionInfo[1].dwKeyAssignment = DIK_S;
            rgActionInfo[1].actionTriggerCondition = KeyPressed;

            rgActionInfo[2].actionType = MoveLeft;
            rgActionInfo[2].dwKeyAssignment = DIK_A;
            rgActionInfo[2].actionTriggerCondition = KeyPressed;

            rgActionInfo[3].actionType = MoveRight;
            rgActionInfo[3].dwKeyAssignment = DIK_D;
            rgActionInfo[3].actionTriggerCondition = KeyPressed;

            rgActionInfo[4].actionType = Shoot;
            rgActionInfo[4].dwKeyAssignment = DIK_RETURN;
            rgActionInfo[4].actionTriggerCondition = KeyTapped;

            hr = CInput::Instance()->InitializeActions(rgActionInfo, ARRAYSIZE(rgActionInfo));
            if (SUCCEEDED(hr))
            {
                hr = CGraphics::Instance()->CreateSprite();
                if (SUCCEEDED(hr))
                {
                    hr = CSound::Instance()->InitializeDirectSound(hWnd);
                    if (SUCCEEDED(hr))
                    {
                        CGameWorld::Instance()->Initialize();
                        CSound::Instance()->PlaySound();
                        CAudio::Instance()->InitializeFMOD();
                    }
                }
            }
        }
    }

    return hr;
}



HRESULT CGameEngine::Uninitialize()
{
    CGraphics::Instance()->UninitializeDirect3D();
    CInput::Instance()->UninitializeDirectInput();
    CSound::Instance()->UninitializeDirectSound();
    CGameWorld::Instance()->Uninitialize();

    return S_OK;
}

HRESULT CGameEngine::ExecuteSingleFrame()
{    
    //
    // Update the game input state
    //
    CInput::Instance()->Update();

    //
    // Keep the FMOD subsystem spinning
    //
    CAudio::Instance()->Update();

    //
    // Update game world state
    // 
    CGameWorld::Instance()->Update();

    //
    // Draw the updated game world
    //
    CGraphics::Instance()->Render(CGameWorld::Instance()->GetPlayerObject(), CContent::Instance()->GetGameObjects(), CContent::Instance()->GetGameObjectCount());

    return S_OK;
}