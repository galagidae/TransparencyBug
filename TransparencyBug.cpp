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
	wcex.hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE);
	wcex.lpszClassName = WindowClassName;

	return RegisterClassEx(&wcex);
}

// Create window
BOOL SetupWindow(HINSTANCE hinst)
{
	wndRect.top = 0;
	wndRect.bottom = 500;
	wndRect.left = 0;
	wndRect.right = 500;
	
	RegisterWndClass(hinst);

	hMainWnd = CreateWindowEx (WS_EX_TOPMOST,
		WindowClassName, WindowTitle,
		WS_OVERLAPPEDWINDOW,
		0, 0, wndRect.right, wndRect.bottom, NULL, NULL, hinst, NULL);
	if (!hMainWnd)
	{
		return FALSE;
	}

	// Make the window opaque.
	SetLayeredWindowAttributes(hMainWnd, 0, 255, LWA_ALPHA);

	return TRUE;
}