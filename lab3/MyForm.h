#pragma once
#include "Header.h"
#include <string>
#include <msclr\marshal_cppstd.h>
#include <winbase.h>

namespace FileManager {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace msclr::interop;

	/// <summary>
	/// —водка дл¤ MyForm
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
	private: System::Windows::Forms::Button^ back;
	private: System::Windows::Forms::Button^ forw;
	private: System::Windows::Forms::Button^ open;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ path;

	private: System::Windows::Forms::Button^ cmd_move;
	private: System::Windows::Forms::Button^ cmd_copy;
	private: System::Windows::Forms::Button^ cmd_rename;
	private: System::Windows::Forms::Button^ cmd_delete;

	private: ListForm^ form = gcnew ListForm();
	private: System::Windows::Forms::ListBox^ fileBox;




	private:
		/// <summary>
		/// ќб¤зательна¤ переменна¤ конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;
		/// <summary>
		/// “ребуемый метод дл¤ поддержки конструктора Ч не измен¤йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->back = (gcnew System::Windows::Forms::Button());
			this->forw = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->path = (gcnew System::Windows::Forms::TextBox());
			this->open = (gcnew System::Windows::Forms::Button());
			this->cmd_move = (gcnew System::Windows::Forms::Button());
			this->cmd_copy = (gcnew System::Windows::Forms::Button());
			this->cmd_rename = (gcnew System::Windows::Forms::Button());
			this->cmd_delete = (gcnew System::Windows::Forms::Button());
			this->fileBox = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// back
			// 
			this->back->Location = System::Drawing::Point(12, 12);
			this->back->Name = L"back";
			this->back->Size = System::Drawing::Size(75, 23);
			this->back->TabIndex = 0;
			this->back->Text = L"<<";
			this->back->UseVisualStyleBackColor = true;
			this->back->Click += gcnew System::EventHandler(this, &MyForm::back_Click);
			// 
			// forw
			// 
			this->forw->Location = System::Drawing::Point(93, 12);
			this->forw->Name = L"forw";
			this->forw->Size = System::Drawing::Size(75, 23);
			this->forw->TabIndex = 1;
			this->forw->Text = L">>";
			this->forw->UseVisualStyleBackColor = true;
			this->forw->Click += gcnew System::EventHandler(this, &MyForm::forw_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(174, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(32, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Path:";
			// 
			// path
			// 
			this->path->Location = System::Drawing::Point(215, 15);
			this->path->Name = L"path";
			this->path->ReadOnly = true;
			this->path->Size = System::Drawing::Size(817, 20);
			this->path->TabIndex = 3;
			this->path->TextChanged += gcnew System::EventHandler(this, &MyForm::path_TextChanged);
			// 
			// open
			// 
			this->open->Location = System::Drawing::Point(1038, 15);
			this->open->Name = L"open";
			this->open->Size = System::Drawing::Size(75, 21);
			this->open->TabIndex = 4;
			this->open->Text = L"Open";
			this->open->UseVisualStyleBackColor = true;
			this->open->Click += gcnew System::EventHandler(this, &MyForm::open_Click);
			// 
			// cmd_move
			// 
			this->cmd_move->Location = System::Drawing::Point(852, 95);
			this->cmd_move->Name = L"cmd_move";
			this->cmd_move->Size = System::Drawing::Size(236, 45);
			this->cmd_move->TabIndex = 6;
			this->cmd_move->Text = L"Move";
			this->cmd_move->UseVisualStyleBackColor = true;
			this->cmd_move->Click += gcnew System::EventHandler(this, &MyForm::cmd_move_Click);
			// 
			// cmd_copy
			// 
			this->cmd_copy->Location = System::Drawing::Point(852, 162);
			this->cmd_copy->Name = L"cmd_copy";
			this->cmd_copy->Size = System::Drawing::Size(236, 45);
			this->cmd_copy->TabIndex = 7;
			this->cmd_copy->Text = L"Copy";
			this->cmd_copy->UseVisualStyleBackColor = true;
			// 
			// cmd_rename
			// 
			this->cmd_rename->Location = System::Drawing::Point(852, 229);
			this->cmd_rename->Name = L"cmd_rename";
			this->cmd_rename->Size = System::Drawing::Size(236, 45);
			this->cmd_rename->TabIndex = 8;
			this->cmd_rename->Text = L"Rename";
			this->cmd_rename->UseVisualStyleBackColor = true;
			// 
			// cmd_delete
			// 
			this->cmd_delete->Location = System::Drawing::Point(852, 297);
			this->cmd_delete->Name = L"cmd_delete";
			this->cmd_delete->Size = System::Drawing::Size(236, 45);
			this->cmd_delete->TabIndex = 9;
			this->cmd_delete->Text = L"Delete";
			this->cmd_delete->UseVisualStyleBackColor = true;
			// 
			// fileBox
			// 
			this->fileBox->Font = (gcnew System::Drawing::Font(L"Courier New", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->fileBox->FormattingEnabled = true;
			this->fileBox->ItemHeight = 21;
			this->fileBox->Location = System::Drawing::Point(13, 52);
			this->fileBox->Name = L"fileBox";
			this->fileBox->Size = System::Drawing::Size(794, 571);
			this->fileBox->TabIndex = 10;
			this->fileBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::fileBox_SelectedIndexChanged);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1151, 668);
			this->Controls->Add(this->fileBox);
			this->Controls->Add(this->cmd_delete);
			this->Controls->Add(this->cmd_rename);
			this->Controls->Add(this->cmd_copy);
			this->Controls->Add(this->cmd_move);
			this->Controls->Add(this->open);
			this->Controls->Add(this->path);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->forw);
			this->Controls->Add(this->back);
			this->Name = L"MyForm";
			this->Text = L"FileManager";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
	public: void Init_Form()
	{
		form->cmd_buttons->Add(cmd_copy);
		form->cmd_buttons->Add(cmd_delete);
		form->cmd_buttons->Add(cmd_move);
		form->cmd_buttons->Add(cmd_rename);
		onChangePath();
	}
	private: System::Void back_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (form->selectedPath == nullptr)
		{
			return;
		}
		System::IO::DirectoryInfo^ parent = System::IO::Directory::GetParent(form->selectedPath);
		if (parent == nullptr)
		{
			return;
		}
		path->Text = parent->FullName;
		form->selectedPath = parent->FullName;
		updateListBox(fileBox);
	}
	private: System::Void path_TextChanged(System::Object^ sender, System::EventArgs^ e)
	{
		onChangePath();
	}
	private: System::Void onChangePath()
	{
		for (int i = 0; i < form->cmd_buttons->Count; i++)
		{
			form->cmd_buttons[i]->Enabled = false;
		}
	}
	private: System::Void updateListBox(ListBox^ lsb)
	{
		if (form->selectedPath == nullptr)
		{
			return;
		}
		System::IO::DirectoryInfo^ dinfo = gcnew System::IO::DirectoryInfo(form->selectedPath);
		array<System::IO::FileInfo^>^ Files = dinfo->GetFiles();
		lsb->Items->Clear();
		for(int i = 0; i < Files->Length; i++)
		{
			lsb->Items->Add(Files[i]->Name);
		}
	}
	private: System::Void open_Click(System::Object^ sender, System::EventArgs^ e)
	{
		FolderBrowserDialog^ f = gcnew FolderBrowserDialog();
		if (f->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			path->Text = f->SelectedPath;
			form->selectedPath = f->SelectedPath;
		}
		updateListBox(fileBox);
	}
	private: System::Void forw_Click(System::Object^ sender, System::EventArgs^ e)
	{
		
	}
	private: System::Void fileBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		if (fileBox->SelectedItem == nullptr)
		{
			return;
		}
		for (int i = 0; i < form->cmd_buttons->Count; i++)
		{
			form->cmd_buttons[i]->Enabled = true;
		}
		form->selectedFilePath = form->selectedPath + "\\" + fileBox->SelectedItem->ToString();
	}
	private: System::Void cmd_move_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		if (form->selectedFilePath == nullptr)
		{
			return;
		}
		SaveFileDialog^ f = gcnew SaveFileDialog();
		if (f->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			const CHAR* filePath = (const char*)(void*)
				System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(form->selectedFilePath);
			const CHAR* wherePath = (const char*)(void*)
				System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(System::IO::Path::GetFullPath(f->FileName));
			BOOL b = MoveFileA(filePath, wherePath);
			if (b)
			{
				updateListBox(fileBox);
			}
			else
			{
				System::Windows::Forms::MessageBox::Show("File couldn't be move by WinApi", "Error moving file",
					System::Windows::Forms::MessageBoxButtons::OK,
					System::Windows::Forms::MessageBoxIcon::Error);
			}
		}
	}
};
}
