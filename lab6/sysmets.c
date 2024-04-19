#include <windows.h>
#include <stdlib.h>
#include "sysmets.h"
#include "resource.h"

HDC drawHdc;
int enumPtr, enumCount, width, height;
static int cxChar, cxCaps, cyChar, cyClient, iVscrollPos;
DEVMODE prevDevMode;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK SubWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK EnumWindowsProcSize(_In_ HWND   hWnd,_In_ LPARAM lParam)
{
    RECT rect;
    GetWindowRect(hWnd, &rect);
    SetWindowPos(hWnd, HWND_TOP, rect.left + 200, rect.top, width, height, SWP_NOACTIVATE);
    return TRUE;
}

void ChangeWindowSize() {
    // Сохранение текущего разрешения экрана
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &prevDevMode);

    // Изменение разрешения экрана на полноэкранное
    DEVMODE fullscreenDevMode = {0};
    fullscreenDevMode.dmSize = sizeof(DEVMODE);
    fullscreenDevMode.dmPelsWidth = width;
    fullscreenDevMode.dmPelsHeight = height;
    fullscreenDevMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
    ChangeDisplaySettingsEx(NULL, &fullscreenDevMode, NULL, CDS_RESET, NULL);

    // Изменение размеров окон
    EnumWindows(EnumWindowsProcSize, 0);

    // Восстановление предыдущего разрешения экрана
    ChangeDisplaySettingsEx(NULL, &prevDevMode, NULL, 0, NULL);
}

BOOL CALLBACK EnumWindowsProc(_In_ HWND   hWnd,_In_ LPARAM lParam)
{
    int length = GetWindowTextLength(hWnd);
    if (length > 0) {
        char* name = (char*)malloc(sizeof(*name) * (length+1));
        GetWindowTextA(hWnd, name, length+1);
        enumPtr++;
        RECT rect = { 40, 10 + 30*(enumPtr - iVscrollPos) };
        SetTextColor(drawHdc, 0x00000000);
        SetBkMode(drawHdc, TRANSPARENT);
        DrawText(drawHdc, name, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
    }
    return 1;
}

BOOL CALLBACK EnumWindowsProcInit(_In_ HWND   hWnd,_In_ LPARAM lParam)
{
    int length = GetWindowTextLength(hWnd);
    if (length > 0) {
        enumCount++;
    }
    return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("SysMets2");
    HWND hwnd, subWnd;
    HWND button;
    MSG msg;
    WNDCLASS wndclass, subWndClass;

    // Регистрация класса для основного окна
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;
    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("This program requires Windows NT!"),
                   szAppName, MB_ICONERROR);
        return 0;
    }

    // Регистрация класса для дополнительного окна
    static TCHAR subWndAppName[] = TEXT("SubWnd");
    subWndClass.style = CS_HREDRAW | CS_VREDRAW;
    subWndClass.lpfnWndProc = SubWndProc;
    subWndClass.cbClsExtra = 0;
    subWndClass.cbWndExtra = 0;
    subWndClass.hInstance = hInstance;
    subWndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    subWndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    subWndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    subWndClass.lpszMenuName = NULL;
    subWndClass.lpszClassName = subWndAppName;
    if (!RegisterClass(&subWndClass))
    {
        MessageBox(NULL, TEXT("Failed to register sub window class!"),
                   subWndAppName, MB_ICONERROR);
        return 0;
    }

    // Создание основного окна
    hwnd = CreateWindow(szAppName, TEXT("Hack windows"),
                        WS_OVERLAPPEDWINDOW | WS_VSCROLL,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        NULL, NULL, hInstance, NULL);

    // Создание дополнительного окна
    subWnd = CreateWindow(subWndAppName, TEXT("Sub Window"),
                        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        NULL, NULL, hInstance, NULL);

    // Создание кнопок и полей
    button = CreateWindow(TEXT("BUTTON"), TEXT("Change Window Size"), 
                          WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
                          300, 40, 200, 30, hwnd, NULL, hInstance, NULL);
    CreateWindow(TEXT("EDIT"), TEXT(""), 
             WS_VISIBLE | WS_CHILD | WS_BORDER, 
             300, 10, 50, 20, hwnd, (HMENU)IDC_WIDTH_EDIT, hInstance, NULL);
    CreateWindow(TEXT("EDIT"), TEXT(""),
                 WS_VISIBLE | WS_CHILD | WS_BORDER,
                 360, 10, 50, 20, hwnd, (HMENU)IDC_HEIGHT_EDIT, hInstance, NULL);

    // Показываем основное окно
    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    // Показываем дополнительное окно
    ShowWindow(subWnd, iCmdShow);
    UpdateWindow(subWnd);

    // Цикл обработки сообщений
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    int i, y;
    PAINTSTRUCT ps;
    TCHAR szBuffer[10];
    TEXTMETRIC tm;
    switch (message)
    {
    case WM_CREATE:
        hdc = GetDC(hwnd);
        GetTextMetrics(hdc, &tm);
        cxChar = tm.tmAveCharWidth;
        cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
        cyChar = tm.tmHeight + tm.tmExternalLeading;
        ReleaseDC(hwnd, hdc);
        SetScrollRange(hwnd, SB_VERT, 0, enumCount - 1, FALSE);
        SetScrollPos(hwnd, SB_VERT, iVscrollPos, TRUE);
        EnumWindows(EnumWindowsProcInit, 0);
        return 0;
    case WM_SIZE:
        cyClient = HIWORD(lParam);
        return 0;
    case WM_MOUSEWHEEL:
        // Обработка прокрутки колеса мыши
        if ((int)wParam > 0) {
            // Прокрутка вверх
            SendMessage(hwnd, WM_VSCROLL, MAKEWPARAM(SB_LINEUP, 0), 0);
        } else {
            // Прокрутка вниз
            SendMessage(hwnd, WM_VSCROLL, MAKEWPARAM(SB_LINEDOWN, 0), 0);
        }
        return 0;
    case WM_VSCROLL:
        switch (LOWORD(wParam))
        {
        case SB_LINEUP:
            iVscrollPos -= 1;
            break;
        case SB_LINEDOWN:
            iVscrollPos += 1;
            break;
        case SB_PAGEUP:
            iVscrollPos -= cyClient / cyChar;
            break;
        case SB_PAGEDOWN:
            iVscrollPos += cyClient / cyChar;
            break;
        case SB_THUMBPOSITION:
            iVscrollPos = HIWORD(wParam);
            break;
        default:
            break;
        }
        iVscrollPos = max(0, min(iVscrollPos, enumCount - 1));
        if (iVscrollPos != GetScrollPos(hwnd, SB_VERT))
        {
            SetScrollPos(hwnd, SB_VERT, iVscrollPos, TRUE);
            InvalidateRect(hwnd, NULL, TRUE);
        }
        return 0;
    case WM_COMMAND:
        if (LOWORD(wParam) == BN_CLICKED) {
        // Запрос размеров у пользователя
        TCHAR szWidth[10], szHeight[10];
        GetDlgItemText(hwnd, IDC_WIDTH_EDIT, szWidth, 10);
        GetDlgItemText(hwnd, IDC_HEIGHT_EDIT, szHeight, 10);
        width = atoi(szWidth); // Преобразование строки в число
        height = atoi(szHeight); // Преобразование строки в число
        // Проверка на корректность введенных значений (например, можно добавить проверку на положительные значения)
        if (width > 0 && height > 0) {
            ChangeWindowSize();
        }
        else {
            MessageBox(hwnd, TEXT("Please enter valid width and height!"), TEXT("Error"), MB_OK | MB_ICONERROR);
        }
    }
    return 0;
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        drawHdc = hdc;
        enumPtr = 0;
        EnumWindows(EnumWindowsProc, 0);
        EndPaint(hwnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK SubWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        // Здесь можно инициализировать дополнительные параметры окна
        return 0;
    case WM_PAINT:
        // Обработка сообщения отрисовки
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            // Здесь можно выполнить отрисовку в дополнительном окне
            EndPaint(hwnd, &ps);
        }
        return 0;
    case WM_CLOSE:
        // Обработка сообщения о закрытии окна
        DestroyWindow(hwnd);
        return 0;
    case WM_DESTROY:
        // Обработка сообщения разрушения окна
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
