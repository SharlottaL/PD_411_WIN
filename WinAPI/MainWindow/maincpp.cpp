#include<Windows.h>
#include <stdio.h>
#include"resource.h"

#define IDC_STATIC   1000
#define IDC_EDIT     1001
#define IDC_BUTTON   1002


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
	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_EZIK));
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_ZAY));
	//wClass.hIcon = (HICON)LoadImage(hInstance, "zay.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wClass.hIconSm = (HICON)LoadImage(hInstance, "ezik.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hCursor = (HCURSOR)LoadImage(
		hInstance,
		"rabbit.cur",
		IMAGE_CURSOR,
		LR_DEFAULTSIZE, LR_DEFAULTSIZE,
		LR_LOADFROMFILE
	);
	//HBRUSH hBrush = CreateSolidBrush(RGB(180, 90, 130));
	//wClass.hbrBackground = hBrush;
	wClass.hbrBackground = (HBRUSH)22;

	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.lpszMenuName = NULL;
	wClass.lpszClassName = g_sz_CLASS_NAME;

	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registration failed", "", MB_OK | MB_ICONERROR);
		return 0;
	}

	/*RECT workArea;
	SystemParametersInfoA(SPI_GETWORKAREA, 0, &workArea, 0);

	int weith = (workArea.right - workArea.left) * 0.75;
	int hegth = (workArea.bottom - workArea.top) * 0.75;
	int x = (workArea.right + workArea.left - weith) / 2;
	int y = (workArea.bottom + workArea.top - hegth) / 2;
	char size[256];
	sprintf_s(size, sizeof(size), "%s [Размер: %dx%d, Позиция: (%d,%d)]", g_sz_CLASS_NAME, weith, hegth, x, y);*/
	INT screen_width = GetSystemMetrics(SM_CXSCREEN);
	INT screen_heigth = GetSystemMetrics(SM_CXSCREEN);

	INT window_width = screen_width * .75;
	INT window_hegth = screen_heigth * 3 / 4;
	INT window_start_x = screen_width / 8;
	INT window_start_y = screen_heigth / 8;
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

	if (hwnd == NULL)
	{
		MessageBox(NULL, "WINDOW creation failed", "", MB_OK | MB_ICONERROR);
		return 0;
	}
	/*SetWindowTextA(hwnd, size);*/
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
	//DeleteObject(hBrush);
}

INT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
	HWND hStatic = CreateWindowEx
		(
			NULL,
			"Static",
			"Этот staticText  создан при помощи функции CreateWindowEx().",
			WS_CHILD | WS_VISIBLE,
			10, 10,
			550, 25,
			hwnd,
			(HMENU)IDC_STATIC,
			GetModuleHandle(NULL),
			NULL
			);
	CreateWindowEx(
		NULL, "EDIT", "",
		WS_CHILD | WS_VISIBLE|WS_BORDER|ES_CENTER, 
		10, 50,
		550, 22,
		hwnd,
		(HMENU)IDC_EDIT,
		GetModuleHandle(NULL),
		NULL

	);
	CreateWindowEx
	(
		NULL, "Button", "Применить",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		450, 75,
		110, 25,
		hwnd,
		(HMENU)IDC_BUTTON,
		GetModuleHandle(NULL),
		NULL
	);
	}
	break;
	/*case WM_PAINT:
	{
		SendMessage(GetDlgItem(hwnd, 1000), WM_SETTEXT, 0, (LPARAM)"Этот staticText  создан при помощи функции CreateWindowEx().");
	}
	break;*/
	case WM_MOVE:
	case WM_SIZE:
	{
		RECT window_rect;
		GetWindowRect(hwnd, &window_rect);
		INT window_width = window_rect.right - window_rect.left;
		INT window_height = window_rect.bottom - window_rect.top;
		CONST INT SIZE = 256;
		CHAR sz_title[SIZE] = {};
		sprintf
		(
			sz_title,
			"%s - Position: %ix%i, Size:%iX%i",
			g_sz_CLASS_NAME,
			window_rect.left, window_rect.top,
			window_width, window_height);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_title);
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_STATIC:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			HWND hStatic = GetDlgItem(hwnd, IDC_STATIC);
			CONST INT SIZE = 1024;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
			break;
		}
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