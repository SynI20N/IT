#include "MyForm.h"
#include "Thread.h"

using namespace System;
using namespace System::Windows;

int main(array<String^>^ args)
{
	Forms::Application::EnableVisualStyles();
	Forms::Application::SetCompatibleTextRenderingDefault(false);
	lab4::MyForm form;

    MyData^ mydata = gcnew MyData();
    Forms::TextBox^ managed = form.textBox1;
    Forms::TextBox^ managed2 = form.textBox2;
    mydata->text1 = managed;
    mydata->text2 = managed2;
    pin_ptr<void> pinned = &mydata;
    DWORD   dwThreadIdArray[MAX_THREADS];
    HANDLE  hThreadArray[MAX_THREADS];

    // Create MAX_THREADS worker threads.

    for (int i = 0; i < MAX_THREADS; i++)
    {

        // Create the thread to begin execution on its own.

        hThreadArray[i] = CreateThread(
            NULL,                   // default security attributes
            0,                      // use default stack size  
            MyThreadFunction,       // thread function name
            pinned,          // argument to thread function 
            0,                      // use default creation flags 
            &dwThreadIdArray[i]);   // returns the thread identifier 


        // Check the return value for success.
        // If CreateThread fails, terminate execution. 
        // This will automatically clean up threads and memory. 

        if (hThreadArray[i] == NULL)
        {
            ErrorHandler(TEXT("CreateThread"));
            ExitProcess(3);
        }
    } // End of main thread creation loop.

    // Wait until all threads have terminated.

    WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

    // Close all thread handles and free memory allocations.

    for (int i = 0; i < MAX_THREADS; i++)
    {
        CloseHandle(hThreadArray[i]);
    }
    Forms::Application::Run(% form);
    return 0;
}