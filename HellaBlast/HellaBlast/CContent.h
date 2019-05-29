#pragma once
#include "windows.h"
#include "tinyxml.h"
#include "tinystr.h"
#include "d3dx9.h"
#include "CGameObject.h"
#include "Fdi.h"
#include "io.h"
#include "share.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "strsafe.h"

struct XML_RECTANGLE
{
    int x;
    int y;
    int width;
    int height;
};

struct XML_OBJECT
{
    char Name[MAX_PATH];
    char type[MAX_PATH];
    int XPosition;
    int YPosition;
    XML_RECTANGLE rectangle;
};

class CContent
{
protected:
    CContent();

private:
    static CContent* m_pContent;
    XML_OBJECT* m_pXmlObjects;
    int m_numObjects;
    CGameObject* m_pGameObjects;
    int m_numGameObjects;
    struct Impl;
    Impl* m_pImpl;

public:
    enum ContentType
    {
        ContentTypeSpriteSheet = 0,
        ContentTypeBackgroundImage,
        ContentTypeBackgroundSong,
        ContentTypeCanvasXml
    };

    struct FileStream
    {
        BOOL fIsOccupied;
        BYTE* pStream;
        DWORD cbBuffer;
        char szFileName[MAX_PATH];
        char szTargetFilePath[MAX_PATH];
        ContentType contentType;
    };

    struct FileStreamList
    {
        FileStream* rgFileStream;
        USHORT cFiles;
    };

private:
    FileStreamList m_fileStreamList;

public:
    static CContent* Instance();
    HRESULT LoadContent(char* pszCabFileName, char* pszCabFileDir);
    HRESULT RetrofitFileStreams(char* pszXmlFile);
    HRESULT AssignContentType(const char* pszContentType, const char* pszFileName);
    HRESULT LoadLevel(char* pstrXmlFile);
    HRESULT GetObjectCount(IN TiXmlElement* pParent, IN char* pszChild, OUT int* pCount);
    HRESULT LoadGameObjects();
    FileStreamList* GetFileStreamList();
    CGameObject* GetGameObjects();
    int GetGameObjectCount();
    HRESULT ExtractCab(char* pszCabFileName, char* pszCabFileDir);
    USHORT GetContentTypeCount(ContentType contentType);
    static HRESULT LoadFileToMemory(IN CHAR* pszFileName, OUT BYTE** ppFileBuffer, OUT DWORD* pdwBufferSize);

    static HRESULT LoadModulesFromFileStreamList(
        IN CContent::ContentType contentType,
        IN void* pDevice,
        OUT void*** pppVoid,
        OUT USHORT* pCount,
        HRESULT (*fnAlloc) (void***, USHORT),
        HRESULT (*fnLoad) (void**, void* pDevice, CContent::FileStream*)
    );
};