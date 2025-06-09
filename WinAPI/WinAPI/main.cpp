#include<Windows.h>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_COPY:
		{	/*HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);*/
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			//SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_GETTEXT, 0, (LPARAM)sz_buffer);
		}
			break;
		case IDOK:
			MessageBox(hwnd, "Была нажата кнопка Ок", "Info", MB_OK);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}