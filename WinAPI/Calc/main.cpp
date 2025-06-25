
#include<Windows.h>
#include<float.h>
#include<stdio.h>
#include"resource.h"


CONST CHAR g_sz_CLASS_NAME[] = "MyCalc";

CONST CHAR* g_sz_OPERATIONS[] = { "+", "-", "*", "/" };
CONST CHAR* g_sz_EDIT[] = { "<-", "C", "=" };

CONST INT g_i_BUTTON_SIZE = 50;
CONST INT g_i_INTERVAL = 1;
CONST INT g_i_BUTTON_SPACE = g_i_BUTTON_SIZE + g_i_INTERVAL;
//CONST INT g_i_BUTTON_SPACE_DOUBLE = (g_i_BUTTON_SIZE + g_i_INTERVAL) * 2;

CONST INT g_i_BUTTON_SIZE_DOUBLE = g_i_BUTTON_SIZE * 2 + g_i_INTERVAL;
CONST INT g_i_START_X = 10;
CONST INT g_i_START_Y = 10;
CONST INT g_i_DISPLAY_HEIGHT = 22;
CONST INT g_i_DISPLAY_WIDTH = g_i_BUTTON_SIZE * 5 + g_i_INTERVAL * 4;
CONST INT g_i_BUTTON_START_X = g_i_START_X;
CONST INT g_i_BUTTON_START_Y = g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_INTERVAL;

CONST INT g_i_WINDOW_WIDTH = g_i_DISPLAY_WIDTH + 2 * g_i_START_X + 16;
CONST INT g_i_WINDOW_HEIGHT = (g_i_DISPLAY_HEIGHT + g_i_INTERVAL) + g_i_BUTTON_SPACE * 4 + 2 * g_i_START_Y + 24 + 16;

CONST INT g_SIZE = 256;

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
		MessageBox(NULL, "Class registration failed", "", MB_OK | MB_ICONERROR);
		return 0;
	}

	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_CLASS_NAME,
		g_sz_CLASS_NAME,
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		g_i_WINDOW_WIDTH, g_i_WINDOW_HEIGHT,
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
	static DOUBLE a = DBL_MIN;
	static DOUBLE b = DBL_MIN;
	static INT operation = 0;
	static BOOL input = FALSE;				
	static BOOL input_operation = FALSE;	

	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hEditDisplay = CreateWindowEx
		(
			NULL, "Edit", "0",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
			g_i_BUTTON_START_X, g_i_START_Y,
			g_i_DISPLAY_WIDTH, g_i_DISPLAY_HEIGHT,
			hwnd,
			(HMENU)IDC_EDIT_DISPLAY,
			GetModuleHandle(NULL),
			NULL
		);
		INT iDigit = IDC_BUTTON_1;
		CHAR szDigit[2] = {};
		for (int i = 6; i >= 0; i -= 3)
		{
			for (int j = 0; j < 3; j++)
			{
				szDigit[0] = iDigit - IDC_BUTTON_0 + '0';
				HWND hbattonsD = CreateWindowEx
				(
					NULL, "Button", NULL,
					WS_CHILD | WS_VISIBLE | BS_ICON,
					g_i_BUTTON_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * j,
					g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * i / 3,
					g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
					hwnd,
					(HMENU)iDigit,
					GetModuleHandle(NULL),
					NULL
				);
				HICON hIcon = (HICON)LoadImage(
					GetModuleHandle(NULL),
					MAKEINTRESOURCE(IDI_ICON_1 + (iDigit - IDC_BUTTON_1)),
					IMAGE_ICON,
					g_i_BUTTON_SIZE,
					g_i_BUTTON_SIZE, 
					LR_DEFAULTCOLOR);
				SendMessage(hbattonsD, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hIcon);
				iDigit++;
			}
			
		}
		HWND hButton0 = CreateWindowEx
		(
			NULL, "Button", NULL,
			WS_CHILD | WS_VISIBLE | BS_ICON,
			g_i_BUTTON_START_X, g_i_BUTTON_START_Y + (g_i_BUTTON_SPACE) * 3,
			g_i_BUTTON_SIZE_DOUBLE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);
		HICON hIcon = LoadIcon(GetModuleHandle(NULL),	MAKEINTRESOURCE(IDI_ICON_0));
	    SendMessage(hButton0, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hIcon);

		HWND hButtonDOT = CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE | BS_ICON,
			g_i_BUTTON_START_X + g_i_BUTTON_SPACE * 2,
			g_i_BUTTON_START_Y + g_i_BUTTON_SPACE * 3,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL),
			NULL
		);
		HICON hIconD = (HICON)LoadImage(
			GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDI_ICON_DOT), 
			IMAGE_ICON,
			g_i_BUTTON_SIZE - 40,  
			g_i_BUTTON_SIZE - 30, 
			LR_DEFAULTCOLOR
		);
		SendMessage(hButtonDOT, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hIconD);

		HWND hButtonsO = CreateWindowEx
		(
			NULL, "Button", NULL,
			WS_CHILD | WS_VISIBLE | BS_ICON,
			g_i_BUTTON_START_X, g_i_BUTTON_START_Y + (g_i_BUTTON_SPACE) * 3,
			g_i_BUTTON_SIZE_DOUBLE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);
		HICON hIconO = (HICON)LoadImage(
			GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDI_ICON_0),  
			IMAGE_ICON,
			g_i_BUTTON_SIZE-20,
			g_i_BUTTON_SIZE-20, 
			LR_DEFAULTCOLOR
		);
		SendMessage(hButtonsO, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hIconO);
		INT iOperators = IDC_BUTTON_PLUS;
		for (int i = 0; i < 4; i++)
		{
			HWND hButtons_op = CreateWindowEx
			(
				NULL, "Button", NULL,
				WS_CHILD | WS_VISIBLE | BS_ICON,
				g_i_BUTTON_START_X + g_i_BUTTON_SPACE * 3, g_i_BUTTON_START_Y + g_i_BUTTON_SPACE * (3 - i),
				g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
				hwnd,
				(HMENU)iOperators,
				GetModuleHandle(NULL),
				NULL
			);
			HICON hIconn = (HICON)LoadImage(
				GetModuleHandle(NULL),
				MAKEINTRESOURCE(IDI_ICON1 + (iOperators - IDC_BUTTON_PLUS)),  
				IMAGE_ICON,
				g_i_BUTTON_SIZE_DOUBLE - 50,  
				g_i_BUTTON_SIZE -10,        
				LR_DEFAULTCOLOR
			);
				SendMessage(hButtons_op, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hIconn);
				iOperators++;
		}
		INT iEdit = IDC_BUTTON_BSP;
		for (int i = 0; i < 3; i++)
		{
			HWND hButtonsE = CreateWindowEx
			(
				NULL, "Button", NULL,
				WS_CHILD | WS_VISIBLE | BS_ICON,
				g_i_BUTTON_START_X + g_i_BUTTON_SPACE * 4,
				g_i_BUTTON_START_Y + g_i_BUTTON_SPACE * i,
				g_i_BUTTON_SIZE, i < 2 ? g_i_BUTTON_SIZE : g_i_BUTTON_SIZE_DOUBLE,
				hwnd,
				(HMENU)iEdit,
				GetModuleHandle(NULL),
				NULL
			);
			HICON hIconn = (HICON)LoadImage(
				GetModuleHandle(NULL),
				MAKEINTRESOURCE(IDI_ICON_D + (iEdit - IDC_BUTTON_BSP)), 
				IMAGE_ICON,
				g_i_BUTTON_SIZE_DOUBLE - 60,  
				g_i_BUTTON_SIZE, 
				LR_DEFAULTCOLOR
			);

			SendMessage(hButtonsE, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hIconn);
			iEdit++;
		}
	}
	break;
	case WM_COMMAND:
	{
		CHAR szDisplay[g_SIZE] = {};
		CHAR szDigit[2] = {};
		HWND hEditDisplay = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_POINT)
		{
			if (input == FALSE)SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"0");
			if (LOWORD(wParam) == IDC_BUTTON_POINT)	szDigit[0] = '.';
			else				szDigit[0] = LOWORD(wParam) - IDC_BUTTON_0 + '0';
			SendMessage(hEditDisplay, WM_GETTEXT, g_SIZE, (LPARAM)szDisplay);
			if (szDisplay[0] == '0' && szDisplay[1] != '.')szDisplay[0] = 0;
			if (szDigit[0] == '.' && strchr(szDisplay, '.'))break;
			strcat(szDisplay, szDigit);
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)szDisplay);
			input = TRUE;
		}
		if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam) <= IDC_BUTTON_SLASH)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, g_SIZE, (LPARAM)szDisplay);
			if (input && a == DBL_MIN)a = atof(szDisplay);
			if (input)b = atof(szDisplay);
			input = FALSE;
			SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_EQUAL, 0);	
			operation = LOWORD(wParam);		
			input_operation = TRUE;
		}
		if (LOWORD(wParam) == IDC_BUTTON_BSP)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, g_SIZE, (LPARAM)szDisplay);
			if (strlen(szDisplay) > 1)szDisplay[strlen(szDisplay) - 1] = 0;
			else szDisplay[0] = '0';
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)szDisplay);
		}
		if (LOWORD(wParam) == IDC_BUTTON_CLR)
		{
			a = b = DBL_MIN;
			operation = 0;
			input = input_operation = FALSE;
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"0");
		}
		if (LOWORD(wParam) == IDC_BUTTON_EQUAL)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, g_SIZE, (LPARAM)szDisplay);
			if (input && a == DBL_MIN)a = atof(szDisplay);	
			if (input) b = atof(szDisplay);
			if (a == DBL_MIN) break;
			input = FALSE;
			switch (operation)
			{
			case IDC_BUTTON_PLUS:	a += b;		break;
			case IDC_BUTTON_MINUS:	a -= b;		break;
			case IDC_BUTTON_ASTER:	a *= b;		break;
			case IDC_BUTTON_SLASH:	a /= b;		break;
			}
			input_operation = FALSE;
			sprintf(szDisplay, "%g", a);
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)szDisplay);
		}

	}
	break;

	case WM_KEYDOWN:
	{
		if (GetKeyState(VK_SHIFT) < 0)
		{
			if (wParam == 0x38)
			{
				SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ASTER, 0);
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, TRUE, 0);
			}
		}
		else
			if (wParam >= '0' && wParam <= '9')
				SendMessage(GetDlgItem(hwnd, LOWORD(wParam) - '0' + IDC_BUTTON_0), BM_SETSTATE, TRUE, 0);

		switch (wParam)
		{
		case VK_OEM_PERIOD:
		case VK_DECIMAL:	SendMessage(GetDlgItem(hwnd, IDC_BUTTON_POINT), BM_SETSTATE, TRUE, 0); break;
		case VK_ADD:
		case VK_OEM_PLUS:	SendMessage(GetDlgItem(hwnd, IDC_BUTTON_PLUS), BM_SETSTATE, TRUE, 0); break;
		case VK_OEM_MINUS:	SendMessage(GetDlgItem(hwnd, IDC_BUTTON_MINUS), BM_SETSTATE, TRUE, 0); break;
		case VK_MULTIPLY:	SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, TRUE, 0); break;
		case VK_DIVIDE:
		case VK_OEM_2:		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_SLASH), BM_SETSTATE, TRUE, 0); break;
		case VK_BACK:		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_BSP), BM_SETSTATE, TRUE, 0); break;
		case VK_ESCAPE:		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_CLR), BM_SETSTATE, TRUE, 0); break;
		case VK_RETURN:		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_EQUAL), BM_SETSTATE, TRUE, 0); break;
		}
	}
	break;
	case WM_KEYUP:
	{
		switch (wParam)
		{
		default:
			if (wParam >= '0' && wParam <= '9')
			{
				SendMessage(hwnd, WM_COMMAND, LOWORD(wParam - '0' + IDC_BUTTON_0), 0);
				SendMessage(GetDlgItem(hwnd, LOWORD(wParam) - '0' + IDC_BUTTON_0), BM_SETSTATE, FALSE, 0);
			}
		}
	}
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