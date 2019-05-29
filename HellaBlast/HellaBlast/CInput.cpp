#include "CInput.h"

//
// CAction Implementation
//
ActionType CAction::GetActionType()
{
    return m_ActionInfo.actionType;
}
BOOL CAction::IsAssignedKeyPressed(BYTE* rgKeyState)
{
    BOOL fIsAssignedKeyPressed = FALSE;
    if (rgKeyState[m_ActionInfo.dwKeyAssignment] & 0x80)
    {
        fIsAssignedKeyPressed = TRUE;
    }
    else
    {
        fIsAssignedKeyPressed = FALSE;
    }

    return fIsAssignedKeyPressed;
}
void CAction::Update(BYTE* rgKeyState)
{
    //
    // Reset the IsTriggered state to FALSE every frame
    //
    m_fIsTriggered = FALSE;

    //
    // Get current pressed state
    //
    m_fNewPress = IsAssignedKeyPressed(rgKeyState);
    if (TRUE == m_fNewPress)
    {
        if (KeyPressed == m_ActionInfo.actionTriggerCondition)
        {
            m_fIsTriggered = TRUE;
        }
        if (KeyTapped == m_ActionInfo.actionTriggerCondition)
        {
            if (FALSE == m_fOldPress)
            {
                m_fIsTriggered = TRUE;
            }
            else
            {
                m_fIsTriggered = FALSE;
            }
        }
    }
    else
    {
        if (KeyReleased == m_ActionInfo.actionTriggerCondition)
        {
            if (TRUE == m_fOldPress)
            {
                m_fIsTriggered = TRUE;
            }
        }
        else
        {
            m_fIsTriggered = FALSE;
        }
    }

    //
    // Keep record of current frame's pressed state for comparison with subsequent frame
    //
    m_fOldPress = m_fNewPress;
}
CAction::CAction()
{
    m_fOldPress = FALSE;
    m_fNewPress = FALSE;
    m_fIsTriggered = FALSE;
    ZeroMemory(&m_ActionInfo, sizeof(ACTION_INFO));
}
HRESULT CAction::Initialize(ACTION_INFO* pActionInfo)
{
    if (NULL == pActionInfo)
    {
        return E_INVALIDARG;
    }
    m_ActionInfo.actionTriggerCondition = pActionInfo->actionTriggerCondition;
    m_ActionInfo.actionType = pActionInfo->actionType;
    m_ActionInfo.dwKeyAssignment = pActionInfo->dwKeyAssignment;

    return S_OK;
}
BOOL CAction::IsTriggered()
{
    return m_fIsTriggered;
}

//
// CInput Implementation
//
CInput* CInput::m_pInstance = NULL;

//
// Constructor (Protected)
//
CInput::CInput()
{
    m_pDi = NULL;
    m_pDiDeviceKeyboard = NULL;
}

HRESULT CInput::InitializeDirectInput(HINSTANCE hInstance, HWND hWnd)
{
    HRESULT hr = DirectInput8Create(
        hInstance,
        DIRECTINPUT_VERSION,
        IID_IDirectInput8,
        (void**)&m_pDi,
        NULL
        );
    if (SUCCEEDED(hr))
    {
        hr = m_pDi->CreateDevice(GUID_SysKeyboard, &m_pDiDeviceKeyboard, NULL);
        if (SUCCEEDED(hr))
        {
            hr = m_pDiDeviceKeyboard->SetDataFormat(&c_dfDIKeyboard);
            if (SUCCEEDED(hr))
            {
                hr = m_pDiDeviceKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
                if (SUCCEEDED(hr))
                {
                    hr = m_pDiDeviceKeyboard->Acquire();
                    //
                    // I think swallowing E_ACCESSDENIED is ok.  Our game loop will always attempt a reacquire.
                    //
                    if (hr == E_ACCESSDENIED)
                    {
                        hr = S_OK;
                    }
                }
            }
        }
    }

    return hr;
}

void CInput::UninitializeDirectInput()
{
    if (NULL != m_pDiDeviceKeyboard)
    {
        m_pDiDeviceKeyboard->Unacquire();
        m_pDiDeviceKeyboard->Release();
        m_pDiDeviceKeyboard = NULL;
    }

    if (NULL != m_pDi)
    {
        m_pDi->Release();
        m_pDi = NULL;
    }
}

HRESULT CInput::GetInputKeyboard(BYTE* rgKeys, DWORD cSize)
{
    HRESULT hr = m_pDiDeviceKeyboard->Acquire();
    if (SUCCEEDED(hr))
    {
        ZeroMemory(rgKeys, cSize);
        hr = m_pDiDeviceKeyboard->GetDeviceState(cSize, rgKeys);
    }

    return hr;
}

CInput* CInput::Instance()
{
    if (NULL == m_pInstance)
    {
        m_pInstance = new(CInput);
    }

    return m_pInstance;
}

void CInput::Update()
{
    //
    // Get snapshot of input state for the current game frame
    //
    BYTE rgKeyState[256];
    GetInputKeyboard(rgKeyState, sizeof(rgKeyState));

    // update the state of our collection of actions
    for (int i = 0; i < m_wNumActions; i++)
    {
        m_pActions[i].Update(rgKeyState);
    }
}

BOOL CInput::IsActionTriggered(ActionType actionType)
{
    //
    // Check if a specific action within the collection is triggered
    //
    BOOL fIsTriggered = FALSE;
    for (int i = 0; i < m_wNumActions; i++)
    {
        if (actionType == m_pActions[i].GetActionType() )
        {
            fIsTriggered = m_pActions[i].IsTriggered();
            break;
        }
    }

    return fIsTriggered;
}

HRESULT CInput::InitializeActions(ACTION_INFO* pActions, WORD wNumActions)
{
    if (NULL == pActions || 0 == wNumActions)
    {
        return E_INVALIDARG;
    }

    HRESULT hr;
    m_pActions = new CAction[wNumActions];
    if (NULL != m_pActions)
    {
        hr = S_OK;
        
        //
        // Initialize internal CAction objects based on caller-provided ACTION_INFO collection
        //
        m_wNumActions = wNumActions;
        ZeroMemory(m_pActions, wNumActions * sizeof(CAction));
        for (int i = 0; i < wNumActions; i++)
        {
            hr = m_pActions[i].Initialize( &(pActions[i]) );
            if (FAILED(hr))
            {
                break;
            }
        }
    }
    else
    {
        hr = E_OUTOFMEMORY;
    }

    return hr;
}