#pragma once
#include <shlobj.h>
#include <shlwapi.h>
#include <objbase.h>
#include <vcclr.h>

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
			this->combo1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::combo1_SelectedIndexChanged);
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
#pragma endregion
	private: System::Void run_Click(System::Object^ sender, System::EventArgs^ e) {
		if (_folderPath == nullptr)
		{
			System::Windows::Forms::MessageBox::Show("Please, select folder", "Folder empty error",
				System::Windows::Forms::MessageBoxButtons::OK,
				System::Windows::Forms::MessageBoxIcon::Error);
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
}
private: System::Void combo1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	WCHAR* cmd = L"-y -i D:\\Labs\\OperatingSystem\\lab8\\x64\\Debug\\sample.mp4 D:\\Labs\\OperatingSystem\\lab8\\x64\\Debug\\sample.avi 1>D:\\Labs\\OperatingSystem\\lab8\\x64\\Debug\\output.txt 2>&1";
	WCHAR* name = L"C:\\ProgramData\\chocolatey\\bin\\ffmpeg.exe";

	// Start the child process. 
	int code = CreateProcess(
		name,			// No module name (use command line)
		cmd,            // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi);           // Pointer to PROCESS_INFORMATION structure

	if (!code) {
		System::Windows::Forms::MessageBox::Show(GetLastError().ToString(), "Error in CreateProcess",
			System::Windows::Forms::MessageBoxButtons::OK,
			System::Windows::Forms::MessageBoxIcon::Error);
	}
	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
};
}
