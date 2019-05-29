#pragma once
#include "windows.h"
#include "d3d9.h"
#include "d3dx9.h"
#include "CGameObject.h"
#include "CContent.h"

class CGraphics
{
protected:
    CGraphics();

private:
    // DirectX interfaces
    IDirect3D9*  m_pD3dObject;             // the directX object
    IDirect3DDevice9* m_pD3dDevice;        // the directX device
    ID3DXSprite* m_pSprite;                // the D3DX sprite interfaces
    IDirect3DTexture9** m_ppTextureBackgroundImage; // array of pointers to background images
    USHORT m_cTextureBackgroundImage;               // count of background images
    IDirect3DTexture9** m_ppTextureSpriteSheet;     // array of pointers to sprite sheets
    USHORT m_cTextureSpriteSheet;                   // count of sprite sheets

    static CGraphics* pInstance;

public:
    ~CGraphics();
    static CGraphics* Instance();
    bool InitializeDirect3D(HWND hWnd);

    struct Callbacks
    {
        static HRESULT AllocTexturePointers(void*** pppVoid, USHORT count);
        static HRESULT LoadSingleTexture(void** ppVoid, void* pDevice, CContent::FileStream* pFileStream);
    };

    HRESULT CreateSprite();
    void Render(CGameObject* pPlayerObject, CGameObject* pContentObjects, int cContentObjects);
    void UninitializeDirect3D();
};