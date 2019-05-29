#include "CGraphics.h"

CGraphics* CGraphics::pInstance = NULL;

CGraphics::CGraphics()
{
    m_pD3dObject = NULL;       // the directX object
    m_pD3dDevice = NULL;       // the directX device
    m_pSprite = NULL;          // the D3DX sprite interfaces
    m_ppTextureBackgroundImage = NULL; // array of pointers to background images
    m_cTextureBackgroundImage = 0;     // count of background images
    m_ppTextureSpriteSheet = NULL;     // array of pointers to sprite sheets
    m_cTextureSpriteSheet = 0;         // count of sprite sheets
}

CGraphics* CGraphics::Instance()
{
   if (pInstance == NULL)
   {
       pInstance = new CGraphics();
   }

   return pInstance;
}

/**************************************************************************************************
Desc: To initialise DirectX we must create the Direct3D object and then a device
**************************************************************************************************/
bool CGraphics::InitializeDirect3D(HWND hWnd)
{	
    // Create the D3D object
    m_pD3dObject=Direct3DCreate9(D3D_SDK_VERSION);
    if (m_pD3dObject==NULL)
	    return FALSE;

    // Fill out some presentation parameters for running in a window
    D3DPRESENT_PARAMETERS presParams;
    ZeroMemory(&presParams,sizeof(presParams));

    presParams.Windowed=TRUE;
    presParams.SwapEffect=D3DSWAPEFFECT_DISCARD;
    presParams.BackBufferFormat=D3DFMT_UNKNOWN;
    presParams.BackBufferCount=1;

	// Create the D3D device
	HRESULT hr=m_pD3dObject->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &presParams, &m_pD3dDevice);
	if (FAILED(hr))
	{
		// Some cards may not do hardware vertex processing so fall back to software:
		hr = m_pD3dObject->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &presParams, &m_pD3dDevice);
		if (FAILED(hr))
			return FALSE;
	}

	return TRUE;
}

/**************************************************************************************************
Desc: Create our sprite object. Return FALSE if an error occured.
Note: We only use one sprite object as this is the most efficient way of doing it. The sprite object
is purely a mechanism for drawing 2D graphics. By using just one and doing all our drawing between
begin and end Direct3D can batch the rendering of the textures most efficiently
**************************************************************************************************/
HRESULT CGraphics::Callbacks::AllocTexturePointers(void*** pppVoid, USHORT count)
{
    if (NULL == pppVoid || 0 == count)
    {
        return E_INVALIDARG;
    }

    HRESULT hr;
    IDirect3DTexture9*** pppTextures = reinterpret_cast<IDirect3DTexture9***>(pppVoid);
    *pppTextures = new IDirect3DTexture9* [count];
    if (NULL != *pppTextures)
    {
        ZeroMemory(*pppTextures, sizeof(IDirect3DTexture9*) * count);
        hr = S_OK;
    }
    else
    {
        hr = E_OUTOFMEMORY;
    }

    return hr;
}

HRESULT CGraphics::Callbacks::LoadSingleTexture(void** ppVoid, void* pDevice, CContent::FileStream* pFileStream)
{
    if (NULL == ppVoid || NULL == pDevice || NULL == pFileStream)
    {
        return E_INVALIDARG;
    }

    HRESULT hr = D3DXCreateTextureFromFileInMemory(
        reinterpret_cast<IDirect3DDevice9*>(pDevice),
        pFileStream->pStream,
        pFileStream->cbBuffer,
        reinterpret_cast<IDirect3DTexture9**>(ppVoid)
        );

    return hr;
}

HRESULT CGraphics::CreateSprite()
{
    //
    // Load background images into graphics subsystem
    //
    HRESULT hr = CContent::LoadModulesFromFileStreamList(
        CContent::ContentTypeBackgroundImage,
        m_pD3dDevice,
        reinterpret_cast<void***>(&m_ppTextureBackgroundImage),
        &m_cTextureBackgroundImage,
        &CGraphics::Callbacks::AllocTexturePointers,
        &CGraphics::Callbacks::LoadSingleTexture
        );
    if (SUCCEEDED(hr))
    {
        //
        // Load sprite sheets into graphics subsystem
        //
        hr = CContent::LoadModulesFromFileStreamList(
                CContent::ContentTypeSpriteSheet,
                m_pD3dDevice,
                reinterpret_cast<void***>(&m_ppTextureSpriteSheet),
                &m_cTextureSpriteSheet,
                &CGraphics::Callbacks::AllocTexturePointers,
                &CGraphics::Callbacks::LoadSingleTexture
                );
        if (SUCCEEDED(hr))
        {
            hr = D3DXCreateSprite(m_pD3dDevice, &m_pSprite);
        }
    }

	return hr;
}

/**************************************************************************************************
Desc: We use Direct3D to display our scene
**************************************************************************************************/
void CGraphics::Render(CGameObject* pPlayerObject, CGameObject* pContentObjects, int cContentObjects)
{
    // Clear the back buffer
    HRESULT hr = m_pD3dDevice->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0),1.0f,0);
    if (FAILED(hr))
        return;

    // Begin the scene
	hr = m_pD3dDevice->BeginScene();
	if (SUCCEEDED(hr))
	{
        //
        // Draw background images, then game objects (both with alpha blending)
        //
        m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
        for (USHORT i = 0; i < m_cTextureBackgroundImage; i++)
        {
            m_pSprite->Draw(m_ppTextureBackgroundImage[i], NULL, NULL, NULL, 0xFFFFFFFF);
        }

        //
        // Draw the game objects that were pulled from our XML game content
        //
        for (int i = 0; i < cContentObjects; i++)
        {
            BOOL fIsVisible = pContentObjects[i].GetRenderData()->fIsVisible;
            if (TRUE == fIsVisible)
            {
                m_pSprite->Draw(m_ppTextureSpriteSheet[0], &(pContentObjects[i].GetRenderData()->drawRect), NULL, &(pContentObjects[i].GetRenderData()->position), 0xFFFFFFFF);
            }
        }

        //
        // Draw the Player object
        //
        m_pSprite->Draw(m_ppTextureSpriteSheet[0], &(pPlayerObject->GetRenderData()->drawRect), NULL, &(pPlayerObject->GetRenderData()->position), 0xFFFFFFFF);
        		
		// Finished drawing. By reusing the same sprite object D3D can maximise batching of the draws
        m_pSprite->End();

		// Finished rendering
        m_pD3dDevice->EndScene();
        m_pD3dDevice->Present(NULL, NULL, NULL, NULL);
    }
}

/**************************************************************************************************
Desc: Our application is finishing so we must clean up by deallocating any DirectX objects
Every DirectX object has a release function to call
**************************************************************************************************/
void CGraphics::UninitializeDirect3D()
{
    if (NULL != m_ppTextureSpriteSheet && m_cTextureSpriteSheet > 0)
    {
        for (USHORT i = 0; i < m_cTextureSpriteSheet; i++)
        {
            m_ppTextureSpriteSheet[i]->Release();
            m_ppTextureSpriteSheet[i] = NULL;
        }

        delete [] m_ppTextureSpriteSheet;
        m_ppTextureSpriteSheet = NULL;
    }

    if (NULL != m_ppTextureBackgroundImage && m_cTextureBackgroundImage > 0)
    {
        for (USHORT i = 0; i < m_cTextureBackgroundImage; i++)
        {
            m_ppTextureBackgroundImage[i]->Release();
            m_ppTextureBackgroundImage[i] = NULL;
        }

        delete [] m_ppTextureBackgroundImage;
        m_ppTextureBackgroundImage = NULL;
    }

    if (NULL != m_pSprite)
        m_pSprite->Release();

    if (NULL != m_pD3dObject)
        m_pD3dObject->Release();

    if (NULL != m_pD3dDevice)
        m_pD3dDevice->Release();
}