#pragma once
#include <Windows.h>
#include <winreg.h>
#include <vcclr.h>
#include <map>
#include <string>
#include <msclr\marshal_cppstd.h>
#include "ReadRegDialog.h"
#include "RegChangedDialog.h"

std::map<std::string, HKEY> reg_partitions{
  {"HKEY_CLASSES_ROOT", HKEY_CLASSES_ROOT},
  {"HKEY_CURRENT_USER", HKEY_CURRENT_USER},
  {"HKEY_LOCAL_MACHINE", HKEY_LOCAL_MACHINE},
  {"HKEY_USERS", HKEY_USERS},
  {"HKEY_CURRENT_CONFIG", HKEY_CURRENT_CONFIG},
};

namespace Registry {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;


	/// <summary>
	/// Сводка для RForm
	/// </summary>
	public ref class RForm : public System::Windows::Forms::Form
	{
	public:
		RForm(void)
		{
			InitializeComponent();
			for (std::map<std::string, HKEY>::iterator iter = reg_partitions.begin(); iter != reg_partitions.end(); ++iter)
			{
				std::string k = iter->first;
				String^ clistr = gcnew String(k.c_str());
				comboBox1->Items->Add(clistr);
			}
			modifyPrivilegeWithNofity(SE_BACKUP_NAME, "SE_BACKUP_NAME");
			modifyPrivilegeWithNofity(SE_RESTORE_NAME, "SE_RESTORE_NAME");
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~RForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ Create;
	private: System::Windows::Forms::Button^ Read;
	private: System::Windows::Forms::Button^ Delete;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::Label^ dir;
	private: System::Windows::Forms::Button^ button1;

	protected:

	protected:
	private: void modifyPrivilegeWithNofity(IN LPCTSTR szPrivilege, System::String^ name) {
		HRESULT hr = modifyPrivilege(szPrivilege, TRUE);
		if (!SUCCEEDED(hr)) {
			MessageBox::Show(name + " not set", "Error",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else {
			MessageBox::Show(name + " has been set", "Warning",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}
	private: HRESULT modifyPrivilege(
		IN LPCTSTR szPrivilege,
		IN BOOL fEnable)
	{
		HRESULT hr = S_OK;
		TOKEN_PRIVILEGES NewState;
		LUID             luid;
		HANDLE hToken = NULL;

		// Open the process token for this process.
		if (!OpenProcessToken(GetCurrentProcess(),
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
			&hToken))
		{
			printf("Failed OpenProcessToken\n");
			return ERROR_FUNCTION_FAILED;
		}

		// Get the local unique ID for the privilege.
		if (!LookupPrivilegeValue(NULL,
			szPrivilege,
			&luid))
		{
			CloseHandle(hToken);
			printf("Failed LookupPrivilegeValue\n");
			return ERROR_FUNCTION_FAILED;
		}

		// Assign values to the TOKEN_PRIVILEGE structure.
		NewState.PrivilegeCount = 1;
		NewState.Privileges[0].Luid = luid;
		NewState.Privileges[0].Attributes =
			(fEnable ? SE_PRIVILEGE_ENABLED : 0);

		// Adjust the token privilege.
		if (!AdjustTokenPrivileges(hToken,
			FALSE,
			&NewState,
			0,
			NULL,
			NULL))
		{
			printf("Failed AdjustTokenPrivileges\n");
			hr = ERROR_FUNCTION_FAILED;
		}

		// Close the handle.
		CloseHandle(hToken);

		return hr;
	}




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
			this->Create = (gcnew System::Windows::Forms::Button());
			this->Read = (gcnew System::Windows::Forms::Button());
			this->Delete = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->dir = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// Create
			// 
			this->Create->Font = (gcnew System::Drawing::Font(L"Courier New", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Create->Location = System::Drawing::Point(258, 214);
			this->Create->Name = L"Create";
			this->Create->Size = System::Drawing::Size(132, 42);
			this->Create->TabIndex = 0;
			this->Create->Text = L"Create";
			this->Create->UseVisualStyleBackColor = true;
			this->Create->Click += gcnew System::EventHandler(this, &RForm::Create_Click);
			// 
			// Read
			// 
			this->Read->Font = (gcnew System::Drawing::Font(L"Courier New", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Read->Location = System::Drawing::Point(258, 262);
			this->Read->Name = L"Read";
			this->Read->Size = System::Drawing::Size(132, 43);
			this->Read->TabIndex = 1;
			this->Read->Text = L"Read";
			this->Read->UseVisualStyleBackColor = true;
			this->Read->Click += gcnew System::EventHandler(this, &RForm::Read_Click);
			// 
			// Delete
			// 
			this->Delete->Font = (gcnew System::Drawing::Font(L"Courier New", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Delete->Location = System::Drawing::Point(258, 311);
			this->Delete->Name = L"Delete";
			this->Delete->Size = System::Drawing::Size(132, 42);
			this->Delete->TabIndex = 2;
			this->Delete->Text = L"Delete";
			this->Delete->UseVisualStyleBackColor = true;
			this->Delete->Click += gcnew System::EventHandler(this, &RForm::Delete_Click);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Courier New", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(139, 71);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(327, 52);
			this->textBox1->TabIndex = 3;
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Courier New", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox2->Location = System::Drawing::Point(139, 136);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(327, 51);
			this->textBox2->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Courier New", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(40, 84);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(68, 25);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Ввод";
			this->label1->Click += gcnew System::EventHandler(this, &RForm::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Courier New", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(40, 139);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(82, 25);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Вывод";
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Courier New", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(139, 26);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(327, 33);
			this->comboBox1->TabIndex = 7;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &RForm::comboBox1_SelectedIndexChanged);
			// 
			// dir
			// 
			this->dir->AutoSize = true;
			this->dir->Font = (gcnew System::Drawing::Font(L"Courier New", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dir->Location = System::Drawing::Point(31, 29);
			this->dir->Name = L"dir";
			this->dir->Size = System::Drawing::Size(96, 25);
			this->dir->TabIndex = 8;
			this->dir->Text = L"Раздел";
			this->dir->Click += gcnew System::EventHandler(this, &RForm::label3_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Courier New", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(36, 246);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(172, 74);
			this->button1->TabIndex = 9;
			this->button1->Text = L"Integrity Check";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &RForm::button1_Click);
			// 
			// RForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(502, 372);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->dir);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->Delete);
			this->Controls->Add(this->Read);
			this->Controls->Add(this->Create);
			this->Name = L"RForm";
			this->Text = L"Редактор реестра";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void Create_Click(System::Object^ sender, System::EventArgs^ e) {
	HKEY hKey;
	HKEY part = getSelectedKey();
	String^ path = textBox1->Text;
	pin_ptr<const wchar_t> sk = PtrToStringChars(path);

	LONG openRes = RegCreateKeyEx(
		part,
		sk,
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&hKey,
		NULL);

	if (openRes != 0) {
		MessageBox::Show("Could not create registry key, errorCode:" + openRes.ToString(), "Error",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	else {
		RegCloseKey(hKey);
	}
}
private: System::Void Read_Click(System::Object^ sender, System::EventArgs^ e) {
	HKEY hKey;
	HKEY part = getSelectedKey();
	LPDWORD pdwType = (LPDWORD)malloc(sizeof(LPDWORD)); //unsigned long ptr
	PVOID pvData = (PVOID)malloc(sizeof(PVOID)); //void ptr
	LPDWORD pcbData = (LPDWORD)malloc(sizeof(LPDWORD));
	String^ path = textBox1->Text;
	pin_ptr<const wchar_t> sk = PtrToStringChars(path);
	ReadRegDialog^ prompt = gcnew ReadRegDialog();
	String^ res = prompt->ShowDialog() == System::Windows::Forms::DialogResult::OK ? prompt->textBox1->Text : String::Empty;
	pin_ptr<const wchar_t> rgValue = PtrToStringChars(res);

	LONG openRes = RegGetValueW(
		part,
		sk,
		rgValue,
		RRF_RT_ANY,
		pdwType,
		pvData,
		pcbData);
	if (openRes != 0 || !pdwType) {
		MessageBox::Show("Could not get registry key value, errorCode:" + openRes.ToString(), "Error",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	if (*pdwType == REG_SZ)
	{
		wchar_t* value = (wchar_t*)pvData;
		String^ str = gcnew String(value);
		textBox2->Text = str;
	}
}
private: System::Void Delete_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ path = textBox1->Text;
	pin_ptr<const wchar_t> sk = PtrToStringChars(path);
	HKEY part = getSelectedKey();
	LONG openRes = RegDeleteKeyExW(
		part,
		sk,
		KEY_WOW64_64KEY,
		NULL);
	if (openRes != 0) {
		MessageBox::Show("Could not delete key value, errorCode:" + openRes.ToString(), "Error",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
}
private: HKEY getSelectedKey() {
	if (!comboBox1->SelectedItem) {
		MessageBox::Show("Please, select partition of the registry", "Error",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return NULL;
	}
	String^ key = comboBox1->SelectedItem->ToString();
	std::string str = msclr::interop::marshal_as<std::string>(key);
	HKEY hKey = reg_partitions.at(str);
	return hKey;
}
private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	const int result = remove("backup");
	HKEY part = getSelectedKey();
	String^ path = textBox1->Text;
	pin_ptr<const wchar_t> sk = PtrToStringChars(path);
	HKEY hKey;
	LONG openReg = RegOpenKeyExW(
		part,
		sk,
		0,
		KEY_ALL_ACCESS,
		&hKey);
	if (openReg != 0) {
		MessageBox::Show("Could not open the hive, errorCode:" + openReg.ToString(), "Error",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	LONG saveRes = RegSaveKeyExW(
		hKey,
		L"backup",
		NULL,
		REG_LATEST_FORMAT);
	if (saveRes != 0) {
		MessageBox::Show("Could not save the hive, errorCode:" + saveRes.ToString(), "Error",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	//Ставим хук
	DWORD  dwFilter = REG_NOTIFY_CHANGE_NAME |
	REG_NOTIFY_CHANGE_ATTRIBUTES |
		REG_NOTIFY_CHANGE_LAST_SET |
		REG_NOTIFY_CHANGE_SECURITY;

	HANDLE hEvent;
	LONG   lErrorCode;

	// Create an event.
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (hEvent == NULL)
	{
		MessageBox::Show("Could not create an event", "Error",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	// Watch the registry key for a change of value.
	lErrorCode = RegNotifyChangeKeyValue(hKey,
		TRUE,
		dwFilter,
		hEvent,
		TRUE);
	if (lErrorCode != ERROR_SUCCESS)
	{
		MessageBox::Show("Could not create winhook, errorCode:" + lErrorCode.ToString(), "Error",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	// Wait for an event to occur.
	if (WaitForSingleObject(hEvent, INFINITE) == WAIT_FAILED)
	{
		MessageBox::Show("Wait for event failed", "Error",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	// Prompt the user for restore
	RegChangedDialog^ prompt = gcnew RegChangedDialog();
	bool restore = prompt->ShowDialog() == System::Windows::Forms::DialogResult::OK ? 1 : 0;
	if (restore) {
		lErrorCode = RegRestoreKeyW(
			hKey,
			L"backup",
			REG_FORCE_RESTORE
		);
		if (lErrorCode != ERROR_SUCCESS)
		{
			MessageBox::Show("Error backing up registry hive, errorCode:" + lErrorCode.ToString(), "Error",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
	}

	// Close the key.
	lErrorCode = RegCloseKey(hKey);
	if (lErrorCode != ERROR_SUCCESS)
	{
		MessageBox::Show("Error closing registry key", "Error",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	// Close the handle.
	if (!CloseHandle(hEvent))
	{
		MessageBox::Show("Error closing event handle", "Error",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

}
};
}
