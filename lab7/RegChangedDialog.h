#pragma once

namespace Registry {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для RegChangedDialog
	/// </summary>
	public ref class RegChangedDialog : public System::Windows::Forms::Form
	{
	public:
		RegChangedDialog(void)
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
		~RegChangedDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::Button^ restore;
	private: System::Windows::Forms::Button^ ignore;

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->restore = (gcnew System::Windows::Forms::Button());
			this->ignore = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Courier New", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(13, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(626, 21);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Данная ветка реестра была изменена, хотите восстановить\?";
			// 
			// restore
			// 
			this->restore->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->restore->Font = (gcnew System::Drawing::Font(L"Courier New", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->restore->Location = System::Drawing::Point(154, 65);
			this->restore->Name = L"restore";
			this->restore->Size = System::Drawing::Size(126, 34);
			this->restore->TabIndex = 1;
			this->restore->Text = L"Да";
			this->restore->UseVisualStyleBackColor = true;
			// 
			// ignore
			// 
			this->ignore->DialogResult = System::Windows::Forms::DialogResult::Ignore;
			this->ignore->Font = (gcnew System::Drawing::Font(L"Courier New", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ignore->Location = System::Drawing::Point(366, 65);
			this->ignore->Name = L"ignore";
			this->ignore->Size = System::Drawing::Size(124, 34);
			this->ignore->TabIndex = 2;
			this->ignore->Text = L"Нет";
			this->ignore->UseVisualStyleBackColor = true;
			// 
			// RegChangedDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(648, 124);
			this->Controls->Add(this->ignore);
			this->Controls->Add(this->restore);
			this->Controls->Add(this->label1);
			this->Name = L"RegChangedDialog";
			this->Text = L"RegChangedDialog";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}
