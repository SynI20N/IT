#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <windows.h>
#include <fileapi.h>
#include <winuser.h>

namespace FileSystem {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MyForm
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
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	protected:

	protected:
	private:

		//static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	protected:

	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Enabled = false;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(13, 13);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(704, 214);
			this->textBox1->TabIndex = 0;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(729, 261);
			this->Controls->Add(this->textBox1);
			this->Name = L"MyForm";
			this->Text = L"‘айлова€ система";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		Show_Drives(sender, e);
	}
	private: System::Void Show_Drives(System::Object^ sender, System::EventArgs^ e) 
	{
		int length = 1000;
		CHAR* output = (CHAR*)malloc(sizeof(*output) * length);
		DWORD size = GetLogicalDriveStringsA(
			length,
			output
		);
		const int count = 10;
		CHAR drives[count][200] = { 0 };
		strcpy(drives[0],"Disk\tTotal Space, Gb\tFree Space, Gb\0");
		int j = 0, k = 1;
		for (int i = 0; i < size; i++)
		{
			if (output[i] == '\0')
			{
				k++;
				j = 0;
			}
			else
			{
				drives[k][j] = output[i];
				j++;
			}
		}
		ULARGE_INTEGER freespace{};
		ULARGE_INTEGER totalnumbtype{};
		ULARGE_INTEGER totalnumberfreebyte{};
		std::string ws(drives[0]);
		String^ str = gcnew String(ws.c_str());
		textBox1->AppendText(str + L"\r\n");
		for (int i = 1; i < count; i++)
		{
			if (drives[i][0] == '\0')
			{
				continue;
			}
			BOOL res = GetDiskFreeSpaceExA(drives[i], &freespace, &totalnumbtype, &totalnumberfreebyte);
			std::string ws(drives[i]);
			String^ str = gcnew String(ws.c_str());
			double total = totalnumbtype.QuadPart / pow(1024, 3);
			double totalFree = totalnumberfreebyte.QuadPart / pow(1024, 3);
			textBox1->AppendText(str + "\t" + total +  "\t" + totalFree + L"\r\n");
		}
	}
	private: System::Void listView1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
