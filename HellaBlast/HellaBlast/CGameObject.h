#pragma once
#include "windows.h"
#include "d3dx9.h"

class CGameObject
{
public:
    CGameObject();

    enum GameObjectType
    {
        Player = 0,
        Enemy,
        Weapon,
        PowerUp,
        Terrain
    };

    struct RENDER_DATA
    {
        RECT drawRect;
        D3DXVECTOR3 position;
        WORD wNumAttachments;
        RENDER_DATA* m_rgAttachments;
        BOOL fIsVisible;
    };

    HRESULT Initialize(GameObjectType gameObjectType, RENDER_DATA* pRenderData);

private:
    RENDER_DATA* m_pRenderData;
    GameObjectType m_gameObjectType;

public:
    RENDER_DATA* GetRenderData();
    GameObjectType GetGameObjectType();
};