#pragma once
#include <Windows.h>
#include <strsafe.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <objbase.h>
#include <vcclr.h>
#include <tchar.h>
#include <string>

#define MAX_CMD 500

namespace lab8 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ Run;
	protected:

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ Open;
	private: System::String^ _folderPath;
	private: System::String^ _filePath;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::ComboBox^ combo1;

	private: System::Windows::Forms::Button^ open1;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ button2;

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->Run = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->Open = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->combo1 = (gcnew System::Windows::Forms::ComboBox());
			this->open1 = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// Run
			// 
			this->Run->AllowDrop = true;
			this->Run->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Run->Location = System::Drawing::Point(76, 138);
			this->Run->Name = L"Run";
			this->Run->Size = System::Drawing::Size(228, 50);
			this->Run->TabIndex = 0;
			this->Run->Text = L"Запуск";
			this->Run->UseVisualStyleBackColor = true;
			this->Run->Click += gcnew System::EventHandler(this, &MyForm::run_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(37, 71);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(160, 24);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Выберите папку:";
			// 
			// Open
			// 
			this->Open->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Open->Location = System::Drawing::Point(226, 61);
			this->Open->Name = L"Open";
			this->Open->Size = System::Drawing::Size(103, 45);
			this->Open->TabIndex = 3;
			this->Open->Text = L"Открыть";
			this->Open->UseVisualStyleBackColor = true;
			this->Open->Click += gcnew System::EventHandler(this, &MyForm::open_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(133, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(103, 24);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Задание 1";
			this->label2->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(676, 9);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(103, 24);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Задание 2";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(408, 71);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(155, 24);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Выберите файл:";
			// 
			// combo1
			// 
			this->combo1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->combo1->FormattingEnabled = true;
			this->combo1->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"mp4", L"avi", L"mkv", L"mov" });
			this->combo1->Location = System::Drawing::Point(895, 68);
			this->combo1->Name = L"combo1";
			this->combo1->Size = System::Drawing::Size(121, 32);
			this->combo1->TabIndex = 7;
			// 
			// open1
			// 
			this->open1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->open1->Location = System::Drawing::Point(576, 61);
			this->open1->Name = L"open1";
			this->open1->Size = System::Drawing::Size(101, 45);
			this->open1->TabIndex = 8;
			this->open1->Text = L"Открыть";
			this->open1->UseVisualStyleBackColor = true;
			this->open1->Click += gcnew System::EventHandler(this, &MyForm::open1_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(700, 71);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(179, 24);
			this->label5->TabIndex = 9;
			this->label5->Text = L"Выберите формат:";
			this->label5->Click += gcnew System::EventHandler(this, &MyForm::label5_Click);
			// 
			// button2
			// 
			this->button2->Cursor = System::Windows::Forms::Cursors::Default;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(620, 138);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(217, 50);
			this->button2->TabIndex = 10;
			this->button2->Text = L"Конвертировать";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1055, 226);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->open1);
			this->Controls->Add(this->combo1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->Open);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Run);
			this->Name = L"MyForm";
			this->Text = L"Lab8";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
	private: System::Void ErrorExit(LPCTSTR lpszFunction)
	{
		// Retrieve the system error message for the last-error code

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

		// Display the error message and exit the process

		lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
			(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 100) * sizeof(TCHAR));
		StringCchPrintf((LPTSTR)lpDisplayBuf,
			LocalSize(lpDisplayBuf) / sizeof(TCHAR),
			TEXT("%s failed with error %d: %s"),
			lpszFunction, dw, lpMsgBuf);
		::MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

		LocalFree(lpMsgBuf);
		LocalFree(lpDisplayBuf);
		ExitProcess(dw);
	}
#pragma endregion
	private: System::Void run_Click(System::Object^ sender, System::EventArgs^ e) {
		if (_folderPath == nullptr)
		{
			System::Windows::Forms::MessageBox::Show("Please, select folder", "Folder empty error",
				System::Windows::Forms::MessageBoxButtons::OK,
				System::Windows::Forms::MessageBoxIcon::Error);

			return;
		}
		HWND hwnd = NULL;
		pin_ptr<const wchar_t> folder = PtrToStringChars(_folderPath);
		ShellExecute(hwnd, L"find", folder, NULL, NULL, 0);
	}

	private: System::Void open_Click(System::Object^ sender, System::EventArgs^ e) {
		FolderBrowserDialog^ f = gcnew FolderBrowserDialog();
		if (f->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			_folderPath = f->SelectedPath;
		}
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void open1_Click(System::Object^ sender, System::EventArgs^ e) {
	OpenFileDialog^ f = gcnew OpenFileDialog();
	if (f->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		_filePath = f->FileName;
	}
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	if (_filePath == nullptr)
	{
		System::Windows::Forms::MessageBox::Show("Please, select file", "File not specified",
			System::Windows::Forms::MessageBoxButtons::OK,
			System::Windows::Forms::MessageBoxIcon::Error);

		return;
	}
	if (combo1->SelectedItem == nullptr)
	{
		System::Windows::Forms::MessageBox::Show("Please, select extension", "Extension not specified",
			System::Windows::Forms::MessageBoxButtons::OK,
			System::Windows::Forms::MessageBoxIcon::Error);

		return;
	}
	System::String^ ext = combo1->SelectedItem->ToString();
	System::String^ result = System::IO::Path::GetFileName(_filePath);
	System::String^ result2 = System::IO::Path::GetDirectoryName(_filePath);
	System::String^ result3 = System::IO::Path::GetFileNameWithoutExtension(result) + "." + ext;
	pin_ptr<const wchar_t> file = PtrToStringChars(result);
	pin_ptr<const wchar_t> dir = PtrToStringChars(result2);
	pin_ptr<const wchar_t> out = PtrToStringChars(result3);
	HANDLE rPipe, wPipe;
	CreatePipe(&rPipe, &wPipe, NULL, 0);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	wchar_t* cmdLine = (wchar_t*)malloc(sizeof(*cmdLine) * MAX_CMD);
	wsprintf(cmdLine, L"-y -i \"%s\" \"%s\"", file, out);
	wchar_t* appName = _tcsdup(TEXT("C:\\ProgramData\\chocolatey\\bin\\ffmpeg.exe"));
	wchar_t* currDir = _tcsdup(dir);

	// Start the child process. 
	int code = CreateProcess(
		appName,
		cmdLine,
		NULL, 
		NULL,           
		TRUE,         
		CREATE_NO_WINDOW,              
		NULL,           
		currDir,           
		&si,            
		&pi);           

	if (!code) {
		ErrorExit(TEXT("CreateProcess"));
	}
	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
};
}
