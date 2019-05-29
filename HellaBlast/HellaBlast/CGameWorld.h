#pragma once
#include "windows.h"
#include "CGameObject.h"

class CGameWorld
{
protected:
    CGameWorld();

private:
    static CGameWorld* m_pInstance;
    CGameObject* m_pPlayerObject;

public:
    static CGameWorld* Instance();
    HRESULT Initialize();
    void Uninitialize();
    void Update();
    CGameObject* GetPlayerObject();
};