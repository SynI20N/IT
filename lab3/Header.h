#pragma once
namespace FileManager {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	public ref class ListForm
	{
	public:List<System::Windows::Forms::Button^>^ cmd_buttons = gcnew List< System::Windows::Forms::Button^>();
		  String^ selectedPath;
		  String^ selectedFilePath;
		  Form^ prompt;
	public: String^ ShowDialog(String^ text, String^ caption)
	{
		Form^ prompt = gcnew Form();
		prompt->Width = 500;
		prompt->Height = 150;
		prompt->FormBorderStyle = FormBorderStyle::FixedDialog;
		prompt->Text = caption;
		prompt->StartPosition = FormStartPosition::CenterScreen;
		this->prompt = prompt;
		Label^ textLabel = gcnew Label();
		textLabel->Left = 50;
		textLabel->Top = 20;
		textLabel->Width = 200;
		textLabel->Text = text;
		TextBox^ textBox = gcnew TextBox();
		textBox->Left = 50;
		textBox->Top = 50;
		textBox->Width = 400;
		Button^ confirmation = gcnew Button();
		confirmation->Text = "Ok";
		confirmation->Left = 350;
		confirmation->Width = 100;
		confirmation->Top = 70;
		confirmation->DialogResult = DialogResult::OK;
		confirmation->Click += gcnew EventHandler(this, &ListForm::Close);
		prompt->Controls->Add(textBox);
		prompt->Controls->Add(confirmation);
		prompt->Controls->Add(textLabel);
		prompt->AcceptButton = confirmation;

		return prompt->ShowDialog() == DialogResult::OK ? textBox->Text : "";
	}
	public: void Close(System::Object^ sender, System::EventArgs^ e)
	{
		if (this->prompt == nullptr)
		{
			return;
		}
		this->prompt->Close();
	}
	};
}