#pragma once
#include <msclr/marshal_cppstd.h>
#include <string>
#include <fstream>
#include "Lexer.h"
#include "Translator.h"

namespace CppToPy {
	std::fstream file;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace msclr::interop;
	//covert strings
	std::string StrTo_str(System::String^ arg) {
		return marshal_as<std::string>(arg);
	}
	System::String^ strToStr(std::string arg) {
		return marshal_as<System::String^>(arg);
	}
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^ CppCode;

	protected:


	private: System::Windows::Forms::Button^ submitButton;
	private: System::Windows::Forms::RichTextBox^ pytonResult;

	private: System::Windows::Forms::Button^ loadButton;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::Label^ label2;




	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->submitButton = (gcnew System::Windows::Forms::Button());
			this->CppCode = (gcnew System::Windows::Forms::RichTextBox());
			this->pytonResult = (gcnew System::Windows::Forms::RichTextBox());
			this->loadButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// submitButton
			// 
			this->submitButton->BackColor = System::Drawing::Color::Lime;
			this->submitButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->submitButton->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->submitButton->Location = System::Drawing::Point(217, 2);
			this->submitButton->Name = L"submitButton";
			this->submitButton->Size = System::Drawing::Size(115, 70);
			this->submitButton->TabIndex = 0;
			this->submitButton->Text = L"submit";
			this->submitButton->UseVisualStyleBackColor = false;
			this->submitButton->Click += gcnew System::EventHandler(this, &MyForm::submitButton_Click);
			// 
			// CppCode
			// 
			this->CppCode->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->CppCode->BackColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->CppCode->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->CppCode->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->CppCode->Location = System::Drawing::Point(1, 69);
			this->CppCode->Name = L"CppCode";
			this->CppCode->Size = System::Drawing::Size(667, 590);
			this->CppCode->TabIndex = 1;
			this->CppCode->Text = L"";
			this->CppCode->TextChanged += gcnew System::EventHandler(this, &MyForm::CppCode_TextChanged);
			// 
			// pytonResult
			// 
			this->pytonResult->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pytonResult->BackColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->pytonResult->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->pytonResult->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->pytonResult->Location = System::Drawing::Point(667, 69);
			this->pytonResult->Name = L"pytonResult";
			this->pytonResult->ReadOnly = true;
			this->pytonResult->Size = System::Drawing::Size(675, 590);
			this->pytonResult->TabIndex = 2;
			this->pytonResult->Text = L"";
			// 
			// loadButton
			// 
			this->loadButton->BackColor = System::Drawing::Color::Cyan;
			this->loadButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->loadButton->Location = System::Drawing::Point(356, 2);
			this->loadButton->Name = L"loadButton";
			this->loadButton->Size = System::Drawing::Size(113, 70);
			this->loadButton->TabIndex = 4;
			this->loadButton->Text = L"load";
			this->loadButton->UseVisualStyleBackColor = false;
			this->loadButton->Click += gcnew System::EventHandler(this, &MyForm::loadButton_click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label1->Location = System::Drawing::Point(-3, 42);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(93, 24);
			this->label1->TabIndex = 5;
			this->label1->Text = L"C++ code";
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Location = System::Drawing::Point(12, 16);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(11, 8);
			this->flowLayoutPanel1->TabIndex = 6;
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label2->Location = System::Drawing::Point(1227, 42);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(115, 24);
			this->label2->TabIndex = 7;
			this->label2->Text = L"python code";
			// 
			// MyForm
			// 
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->ClientSize = System::Drawing::Size(1342, 687);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->flowLayoutPanel1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->loadButton);
			this->Controls->Add(this->submitButton);
			this->Controls->Add(this->pytonResult);
			this->Controls->Add(this->CppCode);
			this->Name = L"MyForm";
			this->Opacity = 0.97;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Show;
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void submitButton_Click(System::Object^ sender, System::EventArgs^ e) {

	pytonResult->Text = strToStr(translate(StrTo_str(CppCode->Text)));
}
private: System::Void loadButton_click(System::Object^ sender, System::EventArgs^ e) {
	std::string SavedText, x;
	file.open("SavedCode.txt");
	while (file >> x)
		SavedText += x + " ";
	file.close();
	CppCode->Text = strToStr(SavedText);
	pytonResult->Text = strToStr(translate(StrTo_str(CppCode->Text)));
}
private: System::Void CppCode_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	file.open("SavedCode.txt");
	file.clear();
	file << StrTo_str(CppCode->Text);
	file.close();
	
}
};
}
