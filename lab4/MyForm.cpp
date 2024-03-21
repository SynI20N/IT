#include "MyForm.h"

using namespace System;
using namespace System::Windows;
using namespace System::Threading;

public delegate void MyDelegate(System::Windows::Forms::TextBox^ box, int value);
public delegate void ButtonDelegate(System::Windows::Forms::TextBox^ box, int value);
static void AddValueToTextbox(System::Windows::Forms::TextBox^ box, int value)
{
	box->AppendText(value.ToString() + "\r\n");
}

int main(array<String^>^ args)
{
	Forms::Application::EnableVisualStyles();
	Forms::Application::SetCompatibleTextRenderingDefault(false);
	lab4::MyForm^ form = gcnew lab4::MyForm;

	Forms::Application::Run(form);
	form->AbortThreads();
    return 0;
}


static void ThreadProc(System::Object^ obj)
{
	Forms::TextBox^ textBox = (Forms::TextBox^)obj;
	array<System::Object^>^ myArray = gcnew array<System::Object^>(2);
	myArray[0] = textBox;
	int i = 0;
	while(true)
	{
		myArray[1] = i;
		textBox->Invoke(gcnew MyDelegate(AddValueToTextbox), myArray);
		Thread::Sleep(200);
		i++;
	}
}