#define LOGIN "Введите имя пользователя"
#include<Windows.h>
#include <commctrl.h>
#include"resource.h"


BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//#define MESSAGE_BOX

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{

#ifdef MESSAGE_BOX
	MessageBox
	(
		NULL, //
		"Привет WinAPI!\nЭто самое простое окно - окно сообщения\t\t\t\t(MessageBox)",
		"Привет!",
		MB_ABORTRETRYIGNORE | MB_ICONINFORMATION //| MB_HELP
		| MB_DEFBUTTON4
		| MB_TOPMOST
	);
	//MB_ - MessageBox
	//Венгерска нотация  
#endif // MESSAGE_BOX

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)LOGIN);
	}//Выполняется один раз - при запуске окна
		break;

	case WM_COMMAND:
	{

	case IDC_BUTTON_ADD:
		DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, DlgProcAdd, 0);
		break;
	}
	
		//Обрабатывает нажатие кнопок, перемещение мыши и т.д.
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			if (HIWORD(wParam) == EN_SETFOCUS)
			{
				HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

				if (strcmp(sz_buffer, LOGIN) == 0)
				{
					SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");
					SendMessage(hEditLogin, EM_SETSEL, 0, 0);
				}
			}
			if (HIWORD(wParam) == EN_KILLFOCUS)
			{
				HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

				if (sz_buffer[0] == '\0')
				{
					SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)LOGIN);
				}
			}
		}
		break;
		case IDC_BUTTON_COPY:
		{
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDOK:
			MessageBox(hwnd, "Была нажата кнопка 'OK'", "Info", MB_OK | MB_ICONINFORMATION);
			break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:		//Отрабатывает при нажатии на кнопку "Закрыть" X
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
			HWND hCombo = GetDlgItem(hParent, IDC_COMBO);

			SendMessage(hEditAdd, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			if (SendMessage(hCombo, CB_FINDSTRING, -1, (LPARAM)sz_buffer) == CB_ERR)
			{
				SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)sz_buffer);
			}
			else
			{
				MessageBox(hwnd,"Такое значение уже есть", "Info", MB_OK | MB_ICONINFORMATION);
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