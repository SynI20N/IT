#include "Thread.h"

//void CreateThread()

using namespace System;
using namespace System::Windows;
using namespace System::Runtime::InteropServices;
using namespace lab4;

DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
    HANDLE hStdout;

    TCHAR msgBuf[BUF_SIZE];
    size_t cchStringSize;
    DWORD dwChars;

    lab4::MyForm form;
    String^ str = "uninitialized";

    int num = *((int*)lpParam);
    if (num == 0)
    {
        str = gcnew String(threadData.box1.c_str());
        form.textBox1->Text = str;
    }
    else if (num == 1)
    {
        str = gcnew String(threadData.box2.c_str());
        form.textBox2->Text = str;
    }
    else
    {
        form.textBox2->Text = num.ToString();
    }

    Forms::Application::Run(% form);
    return 0;
}

void ErrorHandler(LPCTSTR lpszFunction)
{
    // Retrieve the system error message for the last-error code.

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);

    // Display the error message.

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
    StringCchPrintf((LPTSTR)lpDisplayBuf,
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"),
        lpszFunction, dw, lpMsgBuf);
    MessageBoxW(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    // Free error-handling buffer allocations.

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}

HWND GetConsoleHwnd(void)
{
#define MY_BUFSIZE 1024 // Buffer size for console window titles.
    HWND hwndFound;         // This is what is returned to the caller.
    char pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
    // WindowTitle.
    char pszOldWindowTitle[MY_BUFSIZE]; // Contains original
    // WindowTitle.

// Fetch current window title.

    GetConsoleTitle(LPWSTR(pszOldWindowTitle), MY_BUFSIZE);

    // Format a "unique" NewWindowTitle.

    wsprintf(LPWSTR(pszNewWindowTitle), LPWSTR("%d/%d"),
        GetTickCount(),
        GetCurrentProcessId());

    // Change current window title.

    SetConsoleTitle(LPWSTR(pszNewWindowTitle));

    // Ensure window title has been updated.

    Sleep(40);

    // Look for NewWindowTitle.

    hwndFound = FindWindow(NULL, LPWSTR(pszNewWindowTitle));

    // Restore original window title.

    SetConsoleTitle(LPWSTR(pszOldWindowTitle));

    return(hwndFound);
}