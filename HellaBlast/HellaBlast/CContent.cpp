#include "CContent.h"

//
// Constructor - Singleton
//
CContent::CContent()
{
    m_pXmlObjects = NULL;
    m_numObjects = 0;
    m_pGameObjects = NULL;
    m_numGameObjects = 0;
    ZeroMemory(&m_fileStreamList, sizeof FileStreamList);
}
CContent* CContent::m_pContent = NULL;
CContent* CContent::Instance()
{
    if (NULL == m_pContent)
    {
        m_pContent = new(CContent);
    }

    return m_pContent;
}

struct CContent::Impl
{
    static FNALLOC(alloc);
    static FNFREE(free);
    static FNOPEN(open);
    static FNREAD(read);
    static FNWRITE(write);
    static FNCLOSE(close);
    static FNSEEK(seek);
    static FNFDINOTIFY(notify);
};

//
// Private methods
//
FNALLOC(CContent::Impl::alloc)
{
    return ::malloc(cb);
}

FNFREE(CContent::Impl::free)
{
    ::free(pv);
}

FNOPEN(CContent::Impl::open)
{
    int fh;
    ::_sopen_s(&fh, pszFile, oflag, _SH_DENYNO, pmode);
    return fh;
}

FNREAD(CContent::Impl::read)
{
    return ::_read(hf, pv, cb);
}

FNWRITE(CContent::Impl::write)
{
    return ::_write(hf, pv, cb);
}

FNCLOSE(CContent::Impl::close)
{
    return ::_close(hf);
}

FNSEEK(CContent::Impl::seek)
{
    return ::_lseek(hf, dist, seektype);
}

FNFDINOTIFY(CContent::Impl::notify)
{
    pfdin;
    fdint;
    //
    // Assign const identifiers for FDICopy's notify() return values - removes ambiguity
    //
    const int FDI_CONTINUE = 0;
    const int FDI_ABORT = -1;

    //
    // Resolve our user-specified value (the pfdin->pv void pointer)
    //
    FileStreamList* pFileStreamList = reinterpret_cast<FileStreamList*>(pfdin->pv);
    int retVal = 0;
    switch (fdint)
    {
    case fdintCABINET_INFO:
        FDI_CONTINUE;
        break;
    case fdintCOPY_FILE:
        {   
            //
            // Find an empty pFileStream slot to do work against
            //
            FileStream* pFileStream = NULL;
            for (int i = 0; i < pFileStreamList->cFiles; i++)
            {
                FileStream* pCurrentFileStream = &(pFileStreamList->rgFileStream[i]);             
                if (FALSE == pCurrentFileStream->fIsOccupied)
                {
                    // Empty pStream found
                    pFileStream = pCurrentFileStream;
                    pCurrentFileStream->fIsOccupied = TRUE;

                    break;
                }
            }
            if (NULL != pFileStream)
            {
                //
                // Copy the file name into our blank FileStream::szFileName
                //
                char* pszFileToExtract = pfdin->psz1;
                HRESULT hr = StringCchCopyA(pFileStream->szFileName, ARRAYSIZE(pFileStream->szFileName) * sizeof(char), pszFileToExtract);
                if (SUCCEEDED(hr))
                {
                    //
                    // Copy appropriate values into FileStream::cbBuffer and FileStream::szTargetFilePath
                    //
                    pFileStream->cbBuffer = pfdin->cb;
                    char szTempDir[MAX_PATH] = {0};
                    DWORD dwResult = ExpandEnvironmentStringsA("%temp%", szTempDir, ARRAYSIZE(szTempDir));
                    if (0 != dwResult)
                    {
                        dwResult = _makepath_s(pFileStream->szTargetFilePath, NULL, szTempDir, pszFileToExtract, NULL);
                        if (0 == dwResult)
                        {
                            retVal = Impl::open(pFileStream->szTargetFilePath, _O_BINARY|_O_CREAT|_O_WRONLY|_O_SEQUENTIAL, _S_IREAD|_S_IWRITE);
                        }
                        else
                        {
                            retVal = FDI_ABORT;
                        }
                    }
                    else
                    {
                        retVal = FDI_ABORT;
                    }
                }
            }
            else
            {
                // No empty FileStream slots found
                retVal = FDI_ABORT;
            }
                
            break;
        }
    case fdintCLOSE_FILE_INFO:
        {
            //
            // Close the FDI file handle, finalizing it's storage to disk.
            // I initially wanted to copy this open handle to memory before
            // closing, but couldn't get this to work via ::_read().
            //
            close(pfdin->hf);

            //
            // Copy the stored file from disk into memory (CContent::FileStream)
            //
            char* pszCurrentFileName = pfdin->psz1;
            for (int i = 0; i < pFileStreamList->cFiles; i++)
            {
                FileStream* pCurrentFileStream = &(pFileStreamList->rgFileStream[i]);
                if (TRUE == pCurrentFileStream->fIsOccupied)
                {
                    // Check if this occupied slot is the correct one
                    int iResult = strcmp(pszCurrentFileName, pCurrentFileStream->szFileName);
                    if (0 == iResult)
                    {
                        DWORD cbBytesRead = 0;
                        HRESULT hr = CContent::LoadFileToMemory(
                            pCurrentFileStream->szTargetFilePath,
                            &(pCurrentFileStream->pStream),
                            &cbBytesRead);
                        if (SUCCEEDED(hr))
                        {
                            if (cbBytesRead == pCurrentFileStream->cbBuffer)
                            {
                                // Stream allocation succeeded!
                                retVal = TRUE;
                            }
                            else
                            {
                                retVal = FDI_ABORT;
                            }
                        }

                        break;
                    }
                }
            }

            break;
        }
    }

    return retVal;
}

HRESULT CContent::ExtractCab(char* pszCabFileName, char* pszCabFileDir)
{
    char szTargetFilePath[MAX_PATH] = {0};
    _makepath_s(szTargetFilePath, NULL, pszCabFileDir, pszCabFileName, NULL);
    ERF erf = {0};
    HFDI hfdi = NULL;
    hfdi = ::FDICreate(
        Impl::alloc, 
            Impl::free, 
            Impl::open, 
            Impl::read, 
            Impl::write, 
            Impl::close, 
            Impl::seek,
            cpuUNKNOWN,
            &erf);
    if (NULL != hfdi)
    {
        INT_PTR hf = Impl::open(szTargetFilePath, _O_BINARY | _O_RDONLY | _O_SEQUENTIAL, 0);
        if (-1 != hf)
        {
            FDICABINETINFO fdici = {0};
            BOOL fIsCabinet = FDIIsCabinet(hfdi, hf, &fdici);
            if (TRUE == fIsCabinet)
            {
                //
                // Allocate header memory for our custom CContent::FileStream(s)
                // We get this information from FDICABINETINFO
                //
                m_fileStreamList.cFiles = fdici.cFiles;
                m_fileStreamList.rgFileStream = new FileStream[m_fileStreamList.cFiles];
                ZeroMemory( m_fileStreamList.rgFileStream, m_fileStreamList.cFiles * sizeof(FileStream) );
                if (NULL != m_fileStreamList.rgFileStream)
                {
                    BOOL fResult = FDICopy(
                        hfdi,
                        pszCabFileName,
                        pszCabFileDir,
                        0,
                        Impl::notify,
                        NULL,
                        reinterpret_cast<void*>(&m_fileStreamList));
                    if (TRUE == fResult)
                    {
                        //fResult;
                    }
                    else
                    {
                        //erf.fError;
                    }
                }
                else
                {
                    // out of memory
                }
            }
            Impl::close(hf);
        }
    }

    return S_OK;
}

//
// Public methods
//
HRESULT CContent::LoadContent(char* pszCabFileName, char* pszCabFileDir)
{
    CContent::ExtractCab(pszCabFileName, pszCabFileDir);
    char* pszXmlFile = NULL;
    char szSearch[] = "JetCanvas.xml";
    for (USHORT i = 0; i < m_fileStreamList.cFiles; i++)
    {
        FileStream* pFileStream = &(m_fileStreamList.rgFileStream[i]);
        int iResult = strcmp(szSearch, pFileStream->szFileName);
        if (0 == iResult)
        {
            pszXmlFile = pFileStream->szTargetFilePath;
        }
    }
    CContent::LoadLevel(pszXmlFile);
    CContent::RetrofitFileStreams(pszXmlFile);
    CContent::LoadGameObjects();
    return S_OK;
}

HRESULT CContent::RetrofitFileStreams(char* pszXmlFile)
{
    TiXmlDocument doc(pszXmlFile);
    bool fResult = doc.LoadFile();
    if (true == fResult)
    {
        TiXmlElement* pLevels = doc.FirstChildElement("Levels");
        if (NULL != pLevels)
        {
            TiXmlElement* pCabElements = pLevels->FirstChildElement("CabElements");
            if (NULL != pCabElements)
            {
                int count;
                HRESULT hr = CContent::GetObjectCount(pCabElements, "CabElement", &count);
                if (SUCCEEDED(hr))
                {
                    if (count == m_fileStreamList.cFiles)
                    {
                        TiXmlElement* pPrevElement = NULL;
                        TiXmlElement* pNextElement = NULL;
                        for (int i = 0; i < count; i++)
                        {
                            if (0 == i)
                            {
                                pNextElement = pCabElements->FirstChildElement("CabElement");
                                pPrevElement = pNextElement;
                            }
                            else
                            {
                                pNextElement = pPrevElement->NextSiblingElement();
                                pPrevElement = pNextElement;
                            }
                            
                            const char* pszContentType = pNextElement->Attribute("ContentType");
                            const char* pszFileName = pNextElement->Attribute("FileName");
                            CContent::AssignContentType(pszContentType, pszFileName);
                        }
                    }
                }
            }
        }
    }

    return S_OK;
}

HRESULT CContent::AssignContentType(const char* pszContentType, const char* pszFileName)
{
    if (NULL == pszContentType || NULL == pszFileName)
    {
        return E_INVALIDARG;
    }

    for (int i = 0; i < m_fileStreamList.cFiles; i++)
    {
        FileStream* pFileStream = &(m_fileStreamList.rgFileStream[i]);
        int iResult = strcmp(pszFileName, pFileStream->szFileName);
        if (0 == iResult)
        {
            if ( 0 == strcmp(pszContentType, "SpriteSheet") )
            {
                pFileStream->contentType = ContentTypeSpriteSheet;
            }
            else if ( 0 == strcmp(pszContentType, "BackgroundImage") )
            {
                pFileStream->contentType = ContentTypeBackgroundImage;
            }
            else if ( 0 == strcmp(pszContentType, "BackgroundSong") )
            {
                pFileStream->contentType = ContentTypeBackgroundSong;
            }
            else if ( 0 == strcmp(pszContentType, "CanvasXml") )
            {
                pFileStream->contentType = ContentTypeCanvasXml;
            }

            break;
        }
    }

    return S_OK;
}

HRESULT CContent::LoadLevel(char* pstrXmlFile)
{
    TiXmlDocument doc(pstrXmlFile);
    bool fResult = doc.LoadFile();
    if (true == fResult)
    {
        TiXmlElement* pLevels = doc.FirstChildElement("Levels");
        if (NULL != pLevels)
        {
            TiXmlElement* pLevel = pLevels->FirstChildElement("Level");
            if (NULL != pLevel)
            {
                int count;
                HRESULT hr = GetObjectCount(pLevel, "Object", &count);
                if (SUCCEEDED(hr))
                {
                    m_pXmlObjects  = new XML_OBJECT[count];
                    if (NULL != m_pXmlObjects)
                    {
                        m_numObjects = count;
                        ZeroMemory(m_pXmlObjects, m_numObjects * sizeof(XML_OBJECT));               
                        TiXmlElement* pObject = pLevel->FirstChildElement("Object");
                        if (NULL != pObject)
                        {
                            const char* pszType = pObject->Attribute("Type");
                            StringCchCopyA(m_pXmlObjects[0].type, ARRAYSIZE(m_pXmlObjects[0].type), pszType);
                            pObject->QueryIntAttribute("XPosition", &(m_pXmlObjects[0].XPosition));
                            pObject->QueryIntAttribute("YPosition", &(m_pXmlObjects[0].YPosition));
                            TiXmlElement* pRectangle = pObject->FirstChildElement("Rectangle");
                            if (NULL != pRectangle)
                            {
                                pRectangle->QueryIntAttribute("X", &(m_pXmlObjects[0].rectangle.x));
                                pRectangle->QueryIntAttribute("Y", &(m_pXmlObjects[0].rectangle.y));
                                pRectangle->QueryIntAttribute("Width", &(m_pXmlObjects[0].rectangle.width));
                                pRectangle->QueryIntAttribute("Height", &(m_pXmlObjects[0].rectangle.height));
                            }
                            TiXmlElement* pObjectNext = NULL;
                            for (int i = 1; i < m_numObjects; i++)
                            {
                                pObjectNext = pObject->NextSiblingElement();
                                if (NULL != pObjectNext)
                                {
#pragma warning(disable:4456)
                                    const char* pszType = pObjectNext->Attribute("Type");
#pragma warning(default:4456)
                                    StringCchCopyA(m_pXmlObjects[i].type, ARRAYSIZE(m_pXmlObjects[i].type), pszType);
                                    pObjectNext->QueryIntAttribute("XPosition", &(m_pXmlObjects[i].XPosition));
                                    pObjectNext->QueryIntAttribute("YPosition", &(m_pXmlObjects[i].YPosition));
                                    pRectangle = pObjectNext->FirstChildElement("Rectangle");
                                    if (NULL != pRectangle)
                                    {
                                        pRectangle->QueryIntAttribute("X", &(m_pXmlObjects[i].rectangle.x));
                                        pRectangle->QueryIntAttribute("Y", &(m_pXmlObjects[i].rectangle.y));
                                        pRectangle->QueryIntAttribute("Width", &(m_pXmlObjects[i].rectangle.width));
                                        pRectangle->QueryIntAttribute("Height", &(m_pXmlObjects[i].rectangle.height));
                                    }
                                }
                                // Shift pointer position
                                pObject = pObjectNext;
                            }
                        }
                    }
                    else
                    {
                        hr = E_OUTOFMEMORY;
                    }
                }  
            }
        }
    }

    return S_OK;
}

HRESULT CContent::GetObjectCount(IN TiXmlElement* pParent, IN char* pszChild, OUT int* pCount)
{
    if (NULL == pParent || NULL == pszChild || NULL == pCount)
    {
        return E_INVALIDARG;
    }
    
    HRESULT hr;
    *pCount = 0;      
    TiXmlElement* pObject = pParent->FirstChildElement(pszChild);
    if (NULL != pObject)
    {
        hr = S_OK;
        (*pCount)++;
        TiXmlElement* pObjectNext = NULL;
        do
        {
            pObjectNext = pObject->NextSiblingElement();
            if (pObjectNext)
            {
                (*pCount)++;
                pObject = pObjectNext;
            }
        } while (NULL != pObjectNext);
    }
    else
    {
        hr = E_FAIL;
    }

    return hr;
}

HRESULT CContent::LoadGameObjects()
{
    HRESULT hr;
    if (NULL != m_pXmlObjects && m_numObjects > 0)
    {
        hr = S_OK;
        m_pGameObjects = new CGameObject[m_numObjects];
        if (NULL != m_pGameObjects)
        {
            m_numGameObjects = m_numObjects;
            for (int i = 0; i < m_numGameObjects; i++)
            {
                CGameObject::GameObjectType gameObjectType;
                if ( 0 == strcmp("Player", m_pXmlObjects[i].type) )
                {
                    gameObjectType = CGameObject::Player;
                }
                else if ( 0 == strcmp("Enemy", m_pXmlObjects[i].type) )
                {
                    gameObjectType = CGameObject::Enemy;
                }
                else if ( 0 == strcmp("Weapon", m_pXmlObjects[i].type) )
                {
                    gameObjectType = CGameObject::Weapon;
                }
                else if ( 0 == strcmp("Powerup", m_pXmlObjects[i].type) )
                {
                    gameObjectType = CGameObject::PowerUp;
                }
                else // Terrain is a catch-all
                {
                    gameObjectType = CGameObject::Terrain;
                }

                CGameObject::RENDER_DATA renderData;
                ZeroMemory(&renderData, sizeof(renderData));
                renderData.fIsVisible = TRUE;
                renderData.drawRect.left = m_pXmlObjects[i].rectangle.x;
                renderData.drawRect.right = renderData.drawRect.left + m_pXmlObjects[i].rectangle.width;
                renderData.drawRect.top = m_pXmlObjects[i].rectangle.y;
                renderData.drawRect.bottom = m_pXmlObjects[i].rectangle.y + m_pXmlObjects[i].rectangle.height;
            
                renderData.position.z = 0;
                renderData.position.x = (float) m_pXmlObjects[i].XPosition;
                renderData.position.y = (float) m_pXmlObjects[i].YPosition;

                hr = m_pGameObjects[i].Initialize(gameObjectType, &renderData);
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
    }
    else
    {
        hr = E_INVALIDARG;
    }
    
    return hr;
}

CContent::FileStreamList* CContent::GetFileStreamList()
{
    return &m_fileStreamList;
}

CGameObject* CContent::GetGameObjects()
{
    return m_pGameObjects;
}

int CContent::GetGameObjectCount()
{
    return m_numGameObjects;
}

USHORT CContent::GetContentTypeCount(ContentType contentType)
{
    if (0 == m_fileStreamList.cFiles)
    {
        return 0;
    }

    USHORT count = 0;
    for (USHORT i = 0; i < m_fileStreamList.cFiles; i++)
    {
        FileStream* pFileStream = &(m_fileStreamList.rgFileStream[i]);
        if (contentType == pFileStream->contentType)
        {
            count++;
        }
    }

    return count;
}

//
// CAUTION! Caller must delete the allocated memory
// S_OK hr will guarantee allocation succeeded
//
HRESULT CContent::LoadFileToMemory(IN CHAR* pszFileName, OUT BYTE** ppFileBuffer, OUT DWORD* pdwBufferSize)
{
    //
    // HRESULT is guilty til proven innocent by our final step
    //
    HRESULT hr = E_FAIL;
    HANDLE hFile = CreateFileA(
        pszFileName,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL, // lpSecurityAttributes
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );
    if (INVALID_HANDLE_VALUE != hFile)
    {        
        LARGE_INTEGER largeInteger;
        ZeroMemory(&largeInteger, sizeof(largeInteger));
        BOOL fResult = GetFileSizeEx(hFile, &largeInteger);
        if (TRUE == fResult)
        {     
            *pdwBufferSize = static_cast<DWORD>(largeInteger.QuadPart);
            *ppFileBuffer = new BYTE[*pdwBufferSize];
            ZeroMemory(*ppFileBuffer, *pdwBufferSize);
            if (NULL != *ppFileBuffer)
            {         
                DWORD dwNumberOfBytesRead = 0;                    
                fResult = ReadFile(
                    hFile,
                    *ppFileBuffer,
                    *pdwBufferSize,
                    &dwNumberOfBytesRead,
                    NULL
                    );
                if (TRUE == fResult)
                {
                    //
                    // Cleanup
                    //
                    fResult = CloseHandle(hFile);
                    if (TRUE == fResult)
                    {
                        // Final step succeeded, S_OK stamp of approval.
                        hr = S_OK;
                    }
                    else
                    {
                        DWORD dwLastError = GetLastError();
                        hr = HRESULT_FROM_WIN32(dwLastError);
                    }
                }
                else
                {
                    // Fail - ReadFile
                    DWORD dwLastError = GetLastError();
                    hr = HRESULT_FROM_WIN32(dwLastError);
                }
            }
            else
            {
                // Fail - buffer allocate
                hr = E_OUTOFMEMORY;
            }
        }
        else
        {
            // Fail - GetFileSizeEx
            DWORD dwLastError = GetLastError();
            hr = HRESULT_FROM_WIN32(dwLastError);
        }
    }
    else
    {
        // Fail - CreateFile
        DWORD dwLastError = GetLastError();
        hr = HRESULT_FROM_WIN32(dwLastError);
    }

    return hr;
}

HRESULT CContent::LoadModulesFromFileStreamList(
    IN CContent::ContentType contentType,
    IN void* pDevice,
    OUT void*** pppVoid,
    OUT USHORT* pCount,
    HRESULT (*fnAlloc) (void***, USHORT),
    HRESULT (*fnLoad) (void**, void* pDevice, CContent::FileStream*)
    )
{
    HRESULT hr = E_FAIL;
    *pCount = CContent::Instance()->GetContentTypeCount(contentType);
    if (*pCount > 0)
    {
        hr = fnAlloc(pppVoid, *pCount);
        if (SUCCEEDED(hr))
        {
            CContent::FileStreamList* pFileStreamList = CContent::Instance()->GetFileStreamList();
            for (USHORT k = 0; k < pFileStreamList->cFiles; k++)
            {
                for (USHORT j = 0; j < *pCount; j++)
                {
                    CContent::FileStream* pFileStream = &(pFileStreamList->rgFileStream[k]);
                    if (contentType == pFileStream->contentType)
                    { 
                        if (NULL == (*pppVoid)[j])
                        {
                            // Address of pointer variable in position j
                            void** ppVoid = &( (*pppVoid)[j] );
                            hr = fnLoad(ppVoid, pDevice, pFileStream );
                                
                            break;
                        }
                    }
                }
            }
        }
    }

    return hr;
}