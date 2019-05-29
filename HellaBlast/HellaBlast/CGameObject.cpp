#include "CGameObject.h"

CGameObject::CGameObject()
{
    m_pRenderData = NULL;
}

//
// Caller fills in a RENDER_DATA data structure and passes it by ref
//
HRESULT CGameObject::Initialize(GameObjectType gameObjectType, RENDER_DATA* pRenderData)
{
    if (NULL == pRenderData)
    {
        return E_INVALIDARG;
    }

    m_gameObjectType = gameObjectType;

    HRESULT hr;
    m_pRenderData = new RENDER_DATA();
    if (NULL != m_pRenderData)
    {
        hr = S_OK;
        ZeroMemory(m_pRenderData, sizeof(RENDER_DATA));

        //
        // Copy the caller-specified render data internally
        //
        CopyMemory(m_pRenderData, pRenderData, sizeof(RENDER_DATA));
    }
    else
    {
        hr = E_OUTOFMEMORY;
    }

    return hr;
}

CGameObject::RENDER_DATA* CGameObject::GetRenderData()
{
    return m_pRenderData;
}

CGameObject::GameObjectType CGameObject::GetGameObjectType()
{
    return m_gameObjectType;
}