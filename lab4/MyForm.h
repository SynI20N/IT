#pragma once

static void ThreadProc(System::Object^ obj);

namespace lab4 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Collections::Generic;

	void _checkThread(System::Threading::Thread^% thread, bool& retFlag);

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
	protected:
	public: System::Windows::Forms::Button^ button1;
	public: System::Windows::Forms::Button^ button2;
	public: System::Windows::Forms::TextBox^ textBox1;
	public: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Threading::Thread^ thread1;
	private: System::Threading::Thread^ thread2;
	public: System::Windows::Forms::Button^ abort1;
	public: System::Windows::Forms::Button^ abort2;
	public: System::Windows::Forms::Button^ priority1;
	public: System::Windows::Forms::Button^ priority2;
	private: System::Windows::Forms::Form^ prompt;


	private:





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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->abort1 = (gcnew System::Windows::Forms::Button());
			this->abort2 = (gcnew System::Windows::Forms::Button());
			this->priority1 = (gcnew System::Windows::Forms::Button());
			this->priority2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(100, 59);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(187, 41);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(377, 58);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(192, 42);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Start";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(83, 276);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(221, 104);
			this->textBox1->TabIndex = 2;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(368, 276);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(216, 104);
			this->textBox2->TabIndex = 3;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(151, 22);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(86, 24);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Thread 1";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(432, 22);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(86, 24);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Thread 2";
			// 
			// abort1
			// 
			this->abort1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->abort1->Location = System::Drawing::Point(100, 119);
			this->abort1->Name = L"abort1";
			this->abort1->Size = System::Drawing::Size(187, 41);
			this->abort1->TabIndex = 6;
			this->abort1->Text = L"Abort";
			this->abort1->UseVisualStyleBackColor = true;
			this->abort1->Click += gcnew System::EventHandler(this, &MyForm::abort1_Click);
			// 
			// abort2
			// 
			this->abort2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->abort2->Location = System::Drawing::Point(377, 119);
			this->abort2->Name = L"abort2";
			this->abort2->Size = System::Drawing::Size(187, 41);
			this->abort2->TabIndex = 7;
			this->abort2->Text = L"Abort";
			this->abort2->UseVisualStyleBackColor = true;
			this->abort2->Click += gcnew System::EventHandler(this, &MyForm::abort2_Click);
			// 
			// priority1
			// 
			this->priority1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->priority1->Location = System::Drawing::Point(100, 185);
			this->priority1->Name = L"priority1";
			this->priority1->Size = System::Drawing::Size(187, 41);
			this->priority1->TabIndex = 8;
			this->priority1->Text = L"Change Priority";
			this->priority1->UseVisualStyleBackColor = true;
			this->priority1->Click += gcnew System::EventHandler(this, &MyForm::priority1_Click);
			// 
			// priority2
			// 
			this->priority2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->priority2->Location = System::Drawing::Point(377, 185);
			this->priority2->Name = L"priority2";
			this->priority2->Size = System::Drawing::Size(187, 41);
			this->priority2->TabIndex = 10;
			this->priority2->Text = L"Change Priority";
			this->priority2->UseVisualStyleBackColor = true;
			this->priority2->Click += gcnew System::EventHandler(this, &MyForm::priority2_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(719, 437);
			this->Controls->Add(this->priority2);
			this->Controls->Add(this->priority1);
			this->Controls->Add(this->abort2);
			this->Controls->Add(this->abort1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"Threads";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
public: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	_threadControl((Button^)sender, thread1, gcnew ParameterizedThreadStart(&ThreadProc), textBox1);
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	_threadControl((Button^)sender, thread2, gcnew ParameterizedThreadStart(&ThreadProc), textBox2);
}
private: void _threadControl(Button^ sender, Thread^ %thread, ParameterizedThreadStart^ func, TextBox^ textBox)
{
	if (thread == nullptr)
	{
		thread = gcnew Thread(func);
		thread->Start(textBox);
		sender->Text = "Pause";
		return;
	}
	textBox->AppendText(thread->ThreadState.ToString() + "\r\n");
	if (thread->ThreadState == ThreadState::Running || thread->ThreadState == ThreadState::WaitSleepJoin)
	{
		thread->Suspend();
		sender->Text = "Resume";
	}
	else if (thread->ThreadState == ThreadState::Suspended)
	{
		thread->Resume();
		sender->Text = "Pause";
	}
}
private: void _abortThread(Thread^% thread)
{
	bool retFlag;
	_checkThread(thread, retFlag);
	if (retFlag) return;
	thread->Abort();
}
private: void _threadPrioritySet(Thread^% thread, TextBox^ textBox)
{
	bool retFlag;
	_checkThread(thread, retFlag);
	if (retFlag) return;
	ThreadPriority prio = this->ShowDialog("Выберите приоритет потока", "Изменение приоритета");
	thread->Priority = prio;
	textBox->AppendText(thread->Priority.ToString() + "\r\n");
}
public: System::Void AbortThreads() {
	if (thread1 != nullptr)
	{
		thread1->Abort();
	}
	if (thread2 != nullptr)
	{
		thread2->Abort();
	}
}
private: System::Void abort1_Click(System::Object^ sender, System::EventArgs^ e) {
	_abortThread(thread1);
}
private: System::Void abort2_Click(System::Object^ sender, System::EventArgs^ e) {
	_abortThread(thread2);
}
private: System::Void priority1_Click(System::Object^ sender, System::EventArgs^ e) {
	_threadPrioritySet(thread1, textBox1);
}
private: System::Void priority2_Click(System::Object^ sender, System::EventArgs^ e) {
	_threadPrioritySet(thread2, textBox2);
}
public: System::Void ClosePrompt(System::Object^ sender, System::EventArgs^ e) {
	prompt->Close();
}
public: ThreadPriority ShowDialog(String^ text, String^ caption)
{
	prompt = gcnew Form();
	prompt->Width = 500;
	prompt->Height = 150;
	prompt->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
	prompt->Text = caption;
	prompt->StartPosition = FormStartPosition::CenterScreen;
	Label^ textLabel = gcnew Label();
	textLabel->Left = 50;
	textLabel->Top = 20;
	textLabel->Width = 200;
	textLabel->Text = text;
	ComboBox^ comboBox = gcnew ComboBox();
	comboBox->Left = 50;
	comboBox->Top = 50;
	comboBox->Width = 400;
	System::Array^ values = System::Enum::GetValues(ThreadPriority::typeid);
	for (int i = 0; i < values->Length; i++)
	{
		comboBox->Items->Add(values->GetValue(i));
	}
	Button^ confirmation = gcnew Button();
	confirmation->Text = "Ok";
	confirmation->Left = 350;
	confirmation->Width = 100;
	confirmation->Top = 70;
	confirmation->DialogResult = System::Windows::Forms::DialogResult::OK;
	confirmation->Click += gcnew EventHandler(this, &MyForm::ClosePrompt);
	prompt->Controls->Add(comboBox);
	prompt->Controls->Add(confirmation);
	prompt->Controls->Add(textLabel);
	prompt->AcceptButton = confirmation;

	return prompt->ShowDialog() == System::Windows::Forms::DialogResult::OK ? (ThreadPriority)comboBox->SelectedItem : ThreadPriority::Normal;
}
};
void _checkThread(System::Threading::Thread^% thread, bool& retFlag)
{
	retFlag = true;
	if (thread == nullptr)
	{
		MessageBox::Show("Thread hasn't been started yet!", "Error",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	else if (thread->ThreadState == ThreadState::Aborted)
	{
		MessageBox::Show("Thread has been aborted", "Error",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	retFlag = false;
}
}
