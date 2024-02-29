#include "MyForm.h"

using namespace System;

using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

[STAThread]

int main(array<String^>^ args)
{

    Application::EnableVisualStyles();

    Application::SetCompatibleTextRenderingDefault(false);

    FileManager::MyForm form;

    form.Init_Form();
    Application::Run(% form);
    return 0;
}