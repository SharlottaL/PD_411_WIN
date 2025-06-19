#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_CLASS_NAME[] = "MYCALC";

INT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));
	wClass.style = 0;
	wClass.cbSize = sizeof(wClass);
	wClass.cbWndExtra = 0;
	wClass.cbClsExtra = 0;

	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	wClass.hInstance = hInstance;
	wClass.lpszMenuName = NULL;
	wClass.lpszClassName = g_sz_CLASS_NAME;
	wClass.lpfnWndProc = (WNDPROC)WndProc;

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration faild", "", MB_OK | MB_ICONERROR);
		return 0;
	}

	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_CLASS_NAME,
		g_sz_CLASS_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
INT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hEditDisplay = CreateWindowEx
		(
			NULL, "EDIT", "0",
			WS_CHILD | WS_VISIBLE|WS_BORDER|ES_RIGHT,
			10, 10,
			500, 22,
			hwnd,
			(HMENU)IDC_EDIT_DISPLAY,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			210, 180,
			110, 35,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "1",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			100, 145,
			110, 35,
			hwnd,
			(HMENU)IDC_BUTTON_1,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "2",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			210, 145,
			110, 35,
			hwnd,
			(HMENU)IDC_BUTTON_2,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "3",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			320, 145,
			110, 35,
			hwnd,
			(HMENU)IDC_BUTTON_3,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "4",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			100, 110,
			110, 35,
			hwnd,
			(HMENU)IDC_BUTTON_4,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "5",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			210, 110,
			110, 35,
			hwnd,
			(HMENU)IDC_BUTTON_5,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "6",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			320, 110,
			110, 35,
			hwnd,
			(HMENU)IDC_BUTTON_6,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "7",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			100, 75,
			110, 35,
			hwnd,
			(HMENU)IDC_BUTTON_7,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "8",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			210, 75,
			110, 35,
			hwnd,
			(HMENU)IDC_BUTTON_8,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "9",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			320, 75,
			110, 35,
			hwnd,
			(HMENU)IDC_BUTTON_9,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "X",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20, 75,
			80, 35,
			hwnd,
			(HMENU)IDC_BUTTON_ASTER,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "/",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20, 110,
			80, 35,
			hwnd,
			(HMENU)IDC_BUTTON_SLASH,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "+",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20, 145,
			80, 35,
			hwnd,
			(HMENU)IDC_BUTTON_PLUS,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "-",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20, 180,
			80, 35,
			hwnd,
			(HMENU)IDC_BUTTON_MINUS,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			100, 180,
			110, 35,
			hwnd,
			(HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "=",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			320, 180,
			110, 35,
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "%",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			430, 145,
			80, 35,
			hwnd,
			(HMENU)IDC_BUTTON_PROCENT,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "C",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			430, 110,
			80, 35,
			hwnd,
			(HMENU)IDC_BUTTON_CLR,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "D",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			430, 75,
			80, 35,
			hwnd,
			(HMENU)IDC_BUTTON_DEL,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "e",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			430, 180,
			80, 35,
			hwnd,
			(HMENU)IDC_BUTTON_E,
			GetModuleHandle(NULL),
			NULL
		);
		
	}
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
	return FALSE;
}