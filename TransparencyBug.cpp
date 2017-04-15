#include <windows.h>

const TCHAR         WindowClassName[] = TEXT("TransparencyClass");
const TCHAR         WindowTitle[] = TEXT("Window Transparency / Edge bug illustration");
HWND                hMainWnd;
RECT                wndRect;
HINSTANCE           hInst;

ATOM                RegisterWndClass(HINSTANCE hInstance);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL				SetupWindow(HINSTANCE hinst);

// Entry Point
int APIENTRY WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE /*hPrevInstance*/,
	_In_ LPSTR     /*lpCmdLine*/,
	_In_ int       /*nCmdShow*/)
{
	if (FALSE == SetupWindow(hInstance))
	{
		return 0;
	}

	ShowWindow(hMainWnd, SW_SHOW);
	UpdateWindow(hMainWnd);

	// Main message loop.
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Shut down.
	return (int)msg.wParam;
}

// Window proc
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Register window class
ATOM RegisterWndClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex = {};

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 255));
	wcex.lpszClassName = WindowClassName;

	return RegisterClassEx(&wcex);
}

// Create window
BOOL SetupWindow(HINSTANCE hinst)
{
	wndRect.top = GetSystemMetrics(SM_CYSCREEN) / 4;
	wndRect.bottom = GetSystemMetrics(SM_CYSCREEN) / 2;
	wndRect.left = GetSystemMetrics(SM_CXSCREEN) / 4;
	wndRect.right = GetSystemMetrics(SM_CXSCREEN) / 2;
	
	RegisterWndClass(hinst);

	/*
	* Here we create a layered, transparent window which will allow mouse events to "click through" to whatever underlying window
	*/
	hMainWnd = CreateWindowEx (WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT,
		WindowClassName, WindowTitle,
		WS_OVERLAPPEDWINDOW,
		wndRect.left, wndRect.top, wndRect.right, wndRect.bottom, NULL, NULL, hinst, NULL);
	if (!hMainWnd)
	{
		return FALSE;
	}

	/*
	* Making the window transparent makes it totally transparent. Let's bring the opacity back up a bit so we can see where it is.
	*/
	SetLayeredWindowAttributes(hMainWnd, 0, 127, LWA_ALPHA);

	return TRUE;
}