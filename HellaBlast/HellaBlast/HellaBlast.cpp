#include "windows.h"
#include "CGameEngine.h"

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR pCmdLine, int iShowCmd)
{
	UNREFERENCED_PARAMETER(hInst);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(pCmdLine);
	UNREFERENCED_PARAMETER(iShowCmd);

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = MsgProc;
	wc.cbClsExtra = 0L;
	wc.cbWndExtra = 0L;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"D3DVertices";
	wc.hIconSm = NULL;

	HRESULT hr;
	ATOM atResult = RegisterClassEx(&wc);
	if (atResult != 0)
	{
		hr = S_OK;
		HWND hWnd = CreateWindow(
			wc.lpszClassName,    // lpClassName
			L"HellaBlast pray game TODAY!", // lpWindowName
			WS_EX_TOPMOST | WS_POPUP,       // dwStyle
			0,			                    // x
			0,				                // y
			CGameEngine::GAME_RESOLUTION_X, // nWidth
			CGameEngine::GAME_RESOLUTION_Y, // nHeight
			GetDesktopWindow(),  // hWndParent
			NULL,                // hMenu
			wc.hInstance,        // hInstance
			NULL);               // lpParam
        if (hWnd != NULL)
        {
            //
            // Initialize the game engine
            //
            hr = CGameEngine::Instance()->Initialize(hInst, hWnd);
			if (SUCCEEDED(hr))
            {
                //
                // Show the window
                //
                ShowWindow(hWnd, SW_SHOWDEFAULT);
                UpdateWindow(hWnd);
					
                //
                // Enter message loop
                //
                MSG msg;
                ZeroMemory(&msg, sizeof(msg));
                while ( msg.message != WM_QUIT )
                {
	                //
	                // TODO: Understand why Vertices sample uses PeekMessage
	                //       as opposed to GetMessage
	                //
	                if ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
	                {
		                TranslateMessage( &msg );
		                DispatchMessage( &msg );
	                }
	                else
	                {
                        //
                        // game loop GO!
                        //
                        Sleep(20);

                        hr = CGameEngine::Instance()->ExecuteSingleFrame();
	                }
                }              
            }
		}
		else
		{
			DWORD dwLastError = GetLastError();
			hr = HRESULT_FROM_WIN32(dwLastError);
		}

		//
		// Cleanup
		//
		hr = UnregisterClass(wc.lpszClassName, wc.hInstance);
		if (FAILED(hr))
		{
			DWORD dwLastError = GetLastError();
			hr = HRESULT_FROM_WIN32(dwLastError);
		}
	}
	else
	{
		DWORD dwLastError = GetLastError();
		hr = HRESULT_FROM_WIN32(dwLastError);
	}
	
	return hr;
}

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch (msg)
    {
        case WM_DESTROY:
			CGameEngine::Instance()->Uninitialize();
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
			//CGraphics::Instance()->Render();
            ValidateRect(hWnd, NULL);
            return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}