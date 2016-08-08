//main.cpp
/************************************************************************/
/*                       
	Created time: 2016/4/19
	Created author: llc
	Function: Windows api study
*/
/************************************************************************/

#include <windows.h>
#include <tchar.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CDECL MessageBoxPrintf(TCHAR* szCaption, TCHAR* szFormat, ...)
{
	TCHAR szBuffer[1024];

	/* 
	va_list是C语言中解决变参问题的一组宏，用于获取不确定个数的参数。                                                                    
	*/
	va_list pArgList;
	va_start(pArgList, szFormat);
	_vsntprintf(szBuffer, sizeof(szBuffer)/sizeof(TCHAR), szFormat, pArgList);
	va_end(pArgList);

	return MessageBox(NULL, szBuffer, szCaption, 0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	int cxScreen, cyScreen;
	cxScreen = GetSystemMetrics(SM_CXSCREEN);
	cyScreen = GetSystemMetrics(SM_CYSCREEN);
	//MessageBoxPrintf(TEXT("ScrnSize"), TEXT("The screen is %i pixels wide by %i pixels high."), cxScreen, cyScreen);

	static TCHAR szAppName[] = TEXT("HelloWin");
	HWND hWnd;
	MSG msg;
	WNDCLASS wndClass;

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = szAppName;

	if (!RegisterClass(&wndClass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}

	hWnd = CreateWindow(szAppName,				//window class name
						TEXT("The Hello"),		//window caption
						WS_THICKFRAME|WS_POPUP,	//window style
						10,			//initial x position
						10,			//initial y position
						1280,			//initial x size
						768,			//initial y size
						NULL,					//parent window handle
						NULL,					//window menu handle
						hInstance,				//program instance handle
						NULL);					//creation parameters

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	// 实现透明必须设置WS_EX_LAYERED标志
	LONG nRet = ::GetWindowLong(hWnd, GWL_EXSTYLE);
	nRet = nRet | WS_EX_LAYERED;
	::SetWindowLong(hWnd, GWL_EXSTYLE, nRet);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;

	switch (message)
	{
	case WM_CREATE:
		{
			break;
		}
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rc);
			DrawText(hdc, TEXT("Hello"), -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hWnd, &ps);
			break;
		}
	case WM_LBUTTONDOWN:
		{
			//::MessageBeep(0); 
			::SetLayeredWindowAttributes(hWnd, 0, 123, LWA_ALPHA);    // 设置半透明
		}
		break;
	case WM_RBUTTONDOWN:
		{
			//::MessageBeep(0); 
			::SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);    // 设置不透明
		}
		break;
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}