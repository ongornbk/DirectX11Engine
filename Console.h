#pragma once
#include <string>
#include <iostream>
#include <Windows.h>

#define CONSOLE Console::GetInstance()-> 


class Console
{
public:
	Console();
	~Console();

	void Print(std::string value);
	void Println(std::string value);
	void Print(WCHAR* value);
	void Println(WCHAR* value);
	void Println(int value);
	void Endline();
	void SetColor(WORD color);

	static Console* GetInstance();
private:
	HANDLE   m_hConsole;


};

