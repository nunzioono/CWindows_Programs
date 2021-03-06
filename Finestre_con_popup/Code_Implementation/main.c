#include <windows.h>
#include "resource.h"

#define ID_FILE_EXIT 9001
#define ID_STUFF_GO 9002
    
const char g_szClassName[] = "myWindowClass";

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_FILE_EXIT:
                    PostMessage(hwnd, WM_CLOSE, 0, 0);
                    break;
                case ID_STUFF_GO:
                
                    break;
            }
            break;
        case WM_CREATE:
            {
            HMENU hMenu, hSubMenu;
            HICON hIcon, hIconSm;

            hMenu = CreateMenu();

            hSubMenu = CreatePopupMenu();
            AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "E&sci");
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu,
                   "&File");
                
            hSubMenu = CreatePopupMenu();
            AppendMenu(hSubMenu, MF_STRING, ID_STUFF_GO, "&Vai");
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu,"&Processa");

            SetMenu(hwnd, hMenu);


            hIcon = LoadImage(NULL, "Images/my_menu.ico", IMAGE_ICON, 32, 32,LR_LOADFROMFILE);
                if(hIcon)
                SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
                else
                MessageBox(hwnd, "Impossibile caricare l'icona grande!","Errore", MB_OK | MB_ICONERROR);

                hIconSm = LoadImage(NULL, "Images/my_menu.ico", IMAGE_ICON, 16, 16,LR_LOADFROMFILE);
                if(hIconSm)
                    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSm);
                else
                    MessageBox(hwnd, "Impossibile caricare l'icona piccola!","Errore", MB_OK | MB_ICONERROR);
            }
        break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;
    HICON hIcon = LoadImage(NULL, "Images/my_icon.ico", IMAGE_ICON, 256, 256,LR_LOADFROMFILE);
    
    //Step 1: Registrazione della Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon  = hIcon;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MYMENU);
    wc.lpszClassName = g_szClassName;
    wc.hIconSm  = hIcon;
    
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