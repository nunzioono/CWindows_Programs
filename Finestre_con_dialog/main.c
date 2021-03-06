#include <windows.h>
#include "resource.h"
    
const char g_szClassName[] = "myWindowClass";

BOOL CALLBACK ToolDlgProc(HWND hwnd, UINT Message, WPARAM wParam,
                    LPARAM lParam)
{
    HWND g_hToolbar = NULL;
    
    switch(Message)
    {
        case WM_CREATE:
        g_hToolbar = CreateDialog(GetModuleHandle(NULL),
                                  MAKEINTRESOURCE(IDD_TOOLBAR),
            hwnd, ToolDlgProc);
        if(g_hToolbar != NULL)
        {
            ShowWindow(g_hToolbar, SW_SHOW);
        }
        else
        {
            MessageBox(hwnd, "CreateDialog ha restituito NULL", "Attenzione!", MB_OK | MB_ICONINFORMATION);        }
        break;
        case WM_DESTROY:
            DestroyWindow(g_hToolbar);
            PostQuitMessage(0);
        break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
           {
                case IDC_PRESS:
                    MessageBox(hwnd, "Salve!", "Questo è un messaggio",
                        MB_OK | MB_ICONEXCLAMATION);
                break;
                case IDC_OTHER:
                    MessageBox(hwnd, "Arrivederci!",
                        "Questo è un altro messaggio",
                        MB_OK | MB_ICONEXCLAMATION);case WM_DESTROY:
                    DestroyWindow(g_hToolbar);
                    PostQuitMessage(0);
                break;
            }
        break
        default:
            return FALSE;
    }
    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {    
        case WM_COMMAND:
        switch(LOWORD(wParam))
        {
            case ID_DIALOG_SHOW:
                ShowWindow(g_hToolbar, SW_SHOW);
            break;
            case ID_DIALOG_HIDE:
                ShowWindow(g_hToolbar, SW_HIDE);
            break;
            //... altri handlers di comandi
        }
        break;
        case WM_LBUTTONDOWN:
            DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), hwnd,AboutDlgProc);
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    
    while(GetMessage(&Msg, NULL, 0, 0))
    {
        if(!IsDialogMessage(g_hToolbar, &Msg))
        {
            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
        }
    }
    
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registrazione della Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon  = LoadIcon(GetModuleHandle(NULL),
                         MAKEINTRESOURCE(IDI_MYICON));
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MYMENU);
    wc.lpszClassName = g_szClassName;
    wc.hIconSm  = (HICON)LoadImage(GetModuleHandle(NULL),
                         MAKEINTRESOURCE(IDI_MYICON),
                         IMAGE_ICON, 16, 16, 0);
    
    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Registrazione della Finestra Fallita!", "Errore!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creazione della finestra
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Titolo della mia finestra",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Creazione della Finestra Fallita!", "Errore!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    // Step 3: Il ciclo dei messaggi
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}