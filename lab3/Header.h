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
	};
}