#include<Windows.h>
#include <stdio.h>

const char g_sz_CLASS_NAME[] = "Параметры Окна:";

INT WINAPI WndProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));
	wClass.style = 0;
	wClass.cbSize = sizeof(wClass);
	wClass.cbWndExtra = 0;
	wClass.cbClsExtra = 0;
	wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hCursor = LoadCursor(NULL, IDC_HAND);
	HBRUSH hBrush = CreateSolidBrush(RGB(180, 90, 130));
	wClass.hbrBackground = hBrush;

	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.lpszMenuName = NULL;
	wClass.lpszClassName = g_sz_CLASS_NAME;

	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registration failed", "", MB_OK | MB_ICONERROR);
		return 0;
	}
	
	RECT workArea;
	SystemParametersInfoA(SPI_GETWORKAREA, 0, &workArea, 0);
	
	int weith = (workArea.right - workArea.left) * 0.75;
	int hegth = (workArea.bottom - workArea.top) * 0.75;
	int x = (workArea.right + workArea.left - weith) / 2;
	int y = (workArea.bottom + workArea.top - hegth) / 2;
	char size[256];
	sprintf_s(size, sizeof(size), "%s [Размер: %dx%d, Позиция: (%d,%d)]", g_sz_CLASS_NAME, weith, hegth, x, y);

	
	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_CLASS_NAME,
		g_sz_CLASS_NAME,
		WS_OVERLAPPEDWINDOW,
		x, y,
		weith, hegth,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "WINDOW creation failed", "", MB_OK | MB_ICONERROR);
		return 0;
	}
	SetWindowTextA(hwnd, size);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.message;
	DeleteObject(hBrush);
}

INT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);

	}
	return FALSE;
}