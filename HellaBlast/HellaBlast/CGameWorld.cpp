#include "CGameWorld.h"
#include "CGameEngine.h"
#include "dinput.h"
#include "CSound.h"
#include "CGameObject.h"
#include "CInput.h"

//
// Constructor
//
CGameWorld::CGameWorld()
{
    m_pPlayerObject = NULL;
}

CGameWorld* CGameWorld::m_pInstance = NULL;

CGameWorld* CGameWorld::Instance()
{
    if (NULL == m_pInstance)
    {
        m_pInstance = new(CGameWorld);
    }

    return m_pInstance;
}

HRESULT CGameWorld::Initialize()
{
    //
    // Find the Player object and store its pointer
    //
    CGameObject* pGameObjects = CContent::Instance()->GetGameObjects();
    int cGameObjects = CContent::Instance()->GetGameObjectCount();
    BOOL fFoundPlayerObject = FALSE;
    for (int i = 0; i < cGameObjects; i++)
    {
        CGameObject* pCurrentGameObject = &(pGameObjects[i]);
        CGameObject::GameObjectType currentGameObjectType = pCurrentGameObject->GetGameObjectType();
        if (CGameObject::Player == currentGameObjectType)
        {
            m_pPlayerObject = pCurrentGameObject;
            fFoundPlayerObject = TRUE;
            break;
        }
    }

    return (TRUE == fFoundPlayerObject) ? S_OK : E_FAIL;
}

void CGameWorld::Uninitialize()
{
    if (NULL != m_pPlayerObject)
    {
        m_pPlayerObject = NULL;
    }
}

void CGameWorld::Update()
{
    #pragma warning( disable : 4482 )
    //
    // Test new InputAction algorithms
    //
    if ( CInput::Instance()->IsActionTriggered(ActionType::MoveUp) ) // up
    {
        m_pPlayerObject->GetRenderData()->position.y -= 10;
    }
    else if ( CInput::Instance()->IsActionTriggered(ActionType::MoveDown) ) // down
    {
        m_pPlayerObject->GetRenderData()->position.y += 10;
    }
    else if ( CInput::Instance()->IsActionTriggered(ActionType::MoveLeft) ) // left
    {
        m_pPlayerObject->GetRenderData()->position.x -= 10;
    }
    else if (CInput::Instance()->IsActionTriggered(ActionType::MoveRight)) // right
    {
        m_pPlayerObject->GetRenderData()->position.x += 10;
    }
}

CGameObject* CGameWorld::GetPlayerObject()
{
    return m_pPlayerObject;
}