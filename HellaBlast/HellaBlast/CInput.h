#pragma once
#include "windows.h"
//#define DIRECTINPUT_VERSION 0x0800
#include "dinput.h"

typedef enum
{
    MoveUp = 0,
    MoveDown,
    MoveLeft,
    MoveRight,
    Shoot
} ActionType;

typedef enum
{
    KeyPressed = 0,
    KeyReleased,
    KeyTapped
} ActionTriggerCondition;

typedef struct
{
    ActionType actionType;
    ActionTriggerCondition actionTriggerCondition;
    DWORD dwKeyAssignment;
} ACTION_INFO;

class CAction
{
private:
    ACTION_INFO m_ActionInfo;
    BOOL m_fOldPress;
    BOOL m_fNewPress;
    BOOL m_fIsTriggered;
    BOOL IsAssignedKeyPressed(BYTE* rgKeyState);
public:
    CAction();
    HRESULT Initialize(ACTION_INFO* pActionInfo);
    ActionType GetActionType();
    void Update(BYTE* rgKeyState);
    BOOL IsTriggered();
};


class CInput
{
protected:
    CInput();

private:
    LPDIRECTINPUT8 m_pDi;                     // the pointer to our DirectInput interface
    LPDIRECTINPUTDEVICE8 m_pDiDeviceKeyboard; // the pointer to the keyboard device
    static CInput* m_pInstance;
    CAction* m_pActions;
    WORD m_wNumActions;

public:
    ~CInput();
    static CInput* Instance();
    HRESULT InitializeDirectInput(HINSTANCE hInstance, HWND hWnd);
    HRESULT InitializeActions(ACTION_INFO* pActionInfo, WORD wNumActions);
    void UninitializeDirectInput();
    HRESULT GetInputKeyboard(BYTE* rgKeys, DWORD cSize);
    void Update();
    BOOL IsActionTriggered(ActionType actionType);
};
