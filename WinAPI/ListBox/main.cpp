#define  _CRT_SECURE_NO_WARNINGS
#ifndef LB_GETLBTEXT
#define LB_GETLBTEXT 0x018A
#endif
#include<Windows.h>
#include<cstdio>
#include"resource.h"


CONST CHAR* G_SZ_VALUES[] = { "This", "is", "my","First","Combo","Box","Хорошо","живет","на ","свете","Винни","Пух" };

INT CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		HWND hList = GetDlgItem(hwnd, IDC_LIST);
		for (int i = 0; i < sizeof(G_SZ_VALUES) / sizeof(G_SZ_VALUES[0]); i++)
		{
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)G_SZ_VALUES[i]);
		}
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_ADD:
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, DlgProcAdd, 0);
			break;
		case IDC_BUTTON_DELETE:
		{
			HWND hList = GetDlgItem(hwnd, IDC_LIST); 
			int iSel = (int)SendMessage(hList, LB_GETCURSEL, 0, 0);
			if (iSel != LB_ERR)
			{
				SendMessage(hList, LB_DELETESTRING, iSel, 0);
			}
			else
			{
				MessageBox(hwnd, "Пожалуйста, выберите пункт для удаления", "Информация", MB_OK | MB_ICONINFORMATION);
			}

		}
		break;
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			CHAR sz_message[SIZE] = {};
			HWND hList = GetDlgItem(hwnd, IDC_LIST);
			INT i = SendMessage(hList, LB_GETCURSEL, 0, 0);
			SendMessage(hList, LB_GETLBTEXT, i, (LPARAM)sz_buffer);
			if (i == -1)strcpy(sz_message, "Выберите вашний вариант");
			else
				sprintf(sz_message, "Вы выбрали пункт % i  со значением '%s'", i, sz_buffer);
			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}
	}
	
	break;
	case WM_CLOSE:		
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}

BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hwnd, IDC_EDIT_ADD));
		break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			const int SIZE = 256;
			TCHAR sz_buffer[SIZE] = {};
			HWND hEditAdd = GetDlgItem(hwnd, IDC_EDIT_ADD);
			HWND hParent = GetParent(hwnd);
			HWND hList = GetDlgItem(hParent, IDC_LIST);

			SendMessage(hEditAdd, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			if (SendMessage(hList, LB_FINDSTRING, -1, (LPARAM)sz_buffer) == LB_ERR)
			{
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
			}
			else
			{
				MessageBox(hwnd, "Такое значение уже есть", "Info", MB_OK | MB_ICONINFORMATION);
			}
			EndDialog(hwnd, 1);
		}
		break;

		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
	}
	break;

	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}
