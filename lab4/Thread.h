#pragma once
#include "MyForm.h"
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <iostream>
#include <WinUser.h>
#include <msclr\marshal_cppstd.h>
#include <string>

#define MAX_THREADS 2
#define BUF_SIZE 255

DWORD WINAPI MyThreadFunction(LPVOID lpParam);
void ErrorHandler(LPCTSTR lpszFunction);
HWND GetConsoleHwnd(void);

struct MyData{
	std::string box1;
	std::string box2;
};

extern MyData threadData;
