#include <windows.h>
#include <iostream>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define SUBMENU_EDIT 4
#define BUTTON_GENERATE 5

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);
void AddControls(HWND);

HWND hEditAge;
HWND hEditName;
HWND hEditOut;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	WNDCLASSW wc = { 0 };
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WindowProcedure;

	RegisterClassW(&wc);

	CreateWindowW(L"myWindowClass", L"Mein Fenster XD", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL);

	MSG msg = { NULL };

	while( GetMessage(&msg, NULL, NULL, NULL)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) 
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (wp)
		{
		case FILE_MENU_NEW:
			MessageBeep(MB_SERVICE_NOTIFICATION);
			break;
		case FILE_MENU_OPEN:
			break;
		case FILE_MENU_EXIT:
			PostQuitMessage(0);
			break;
		case BUTTON_GENERATE:
			wchar_t name[100], age[100], out[100];
			GetWindowTextW(hEditAge, age, 100);
			GetWindowTextW(hEditName, name, 100);
			strcpy((char *)out, (const char *)name);
			strcat((char *)out, (const char*)L" ist ");
			strcpy((char *)out, (const char*)age);
			strcat((char *)out, (const char*)L" Jahre alt.");
			SetWindowText(hEditOut, (LPCSTR)out);
			break;
		}
		break;
	case WM_CREATE:
		AddMenus(hWnd);
		AddControls(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

void AddMenus(HWND hWnd) 
{
}

void AddControls(HWND hWnd) 
{
	CreateWindowW(L"Static", L"Name:", WS_VISIBLE | WS_CHILD | SS_CENTER, 150, 100, 50, 50, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Static", L"Alter:", WS_VISIBLE | WS_CHILD | SS_CENTER, 150, 175, 50, 50, hWnd, NULL, NULL, NULL);
	hEditAge = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD, 250, 100, 100, 50, hWnd, NULL, NULL, NULL);
	hEditName = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD, 250, 175, 100, 50, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Button", L"Generieren", WS_VISIBLE | WS_CHILD | SS_CENTER, 200, 250, 100, 50, hWnd, (HMENU)BUTTON_GENERATE, NULL, NULL);
	hEditOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD, 200, 350, 100, 50, hWnd, NULL, NULL, NULL);
}