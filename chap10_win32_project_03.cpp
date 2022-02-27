// chap10_win32_project_03.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "chap10_win32_project_03.h"
#include <string>
#include <Windows.h>
#include <Windowsx.h>


#define MAX_LOADSTRING 100

//Customary Defined Names


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Custom Global Variables
HWND hwndEdit = NULL;
HWND hwndEditInput = NULL;
HWND hwndBtnExecute = NULL;
HWND hwndBtnClear = NULL;



// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Customary User Defined Functions Prototypes

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CHAP10_WIN32_PROJECT_03, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHAP10_WIN32_PROJECT_03));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CHAP10_WIN32_PROJECT_03));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CHAP10_WIN32_PROJECT_03);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            // Parse the menu selections:
            switch (LOWORD(wParam))
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd); 
                break;

			case ID_BTN_GO:
			{
				int inpLen = 0, edtLen = 0;
				
				LPWSTR lpWStr0 = nullptr, lpWStr1= nullptr;
				wchar_t* pInitialFound = nullptr;

				if (GetWindowTextLengthW(hwndEditInput) && GetWindowTextLengthW(hwndEdit)) {
					inpLen = GetWindowTextLengthW(hwndEditInput);
					edtLen = GetWindowTextLengthW(hwndEdit);

					lpWStr0 = new WCHAR[inpLen * sizeof(WCHAR)];
					lpWStr1 = new WCHAR[edtLen * sizeof(WCHAR)];

					if (!GetWindowTextW(hwndEditInput, lpWStr0, inpLen) ||
						!GetWindowTextW(hwndEdit, lpWStr1, edtLen)) {
						MessageBoxW(nullptr, TEXT("No Input or No Source Text !!"), TEXT("ERROR"), MB_OK);
						break;
					}
					else 
						pInitialFound = wcsstr(lpWStr1, lpWStr0);
						
					if ((nullptr == pInitialFound)) {
						MessageBoxW(nullptr, TEXT("No String Should be Matched !!"), TEXT("Excuse .."), MB_OK);
						break;
					}
					else {
						int selPos = (int)(pInitialFound - lpWStr1);
						int selEnd = selPos + (lstrlenW(lpWStr0)) + 1;
						SendMessageW(hwndEdit, EM_SETSEL, selPos, selEnd);
						SendMessageW(hwndEdit, EM_SCROLLCARET, NULL, NULL);
					}
					
					if (nullptr != lpWStr0) delete[]lpWStr0;
					if (nullptr != lpWStr1) delete[]lpWStr1;

					lpWStr0 = nullptr; lpWStr1 = nullptr; 

				}
					
			}
			break;

			case ID_BTN_CLEAR:
			{
				int IDRESPONSE = 0;
				IDRESPONSE = MessageBoxW(nullptr, TEXT("Are You Sure? "), TEXT("Action Info"), MB_YESNO);
				if (IDRESPONSE == IDYES) SetWindowTextW(hwndEdit, NULL);
			}
			break; 

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

	case WM_CREATE:
	{
		
		hwndBtnExecute = CreateWindowW(TEXT("Button"), TEXT("Go"), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, 270, 5, 40, 20, hWnd, (HMENU)(int)ID_BTN_GO, hInst, NULL);

		hwndEditInput = CreateWindowW(TEXT("Edit"), TEXT("Input Search.."), WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 5, 250, 20, hWnd, (HMENU)(int)ID_EDT_FRAME, GetModuleHandle(NULL), NULL);

		hwndEdit = CreateWindowW(TEXT("Edit"), TEXT("EditBox"), WS_CHILD | WS_BORDER | WS_VSCROLL | WS_VISIBLE
			| ES_LEFT | ES_MULTILINE | ES_NOHIDESEL, 10, 35, 600, 200, hWnd, NULL, GetModuleHandle(NULL), NULL);

		hwndBtnClear = CreateWindowW(TEXT("Button"), TEXT("Clear"), WS_CHILD | WS_BORDER | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, 550, 235, 60, 30, hWnd, (HMENU)(int)ID_BTN_CLEAR, hInst, NULL);

	}
	break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

