#include "Console.h"

#pragma region
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::getline;
#pragma endregion



namespace
{
static Console* m_instance;
}

Console::Console()
{
	if (m_instance)
	{
		delete m_instance;
	}
	m_instance = this;
	if (m_hConsole)
	{
		delete m_hConsole;
	}
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}


Console::~Console()
{
}

void Console::Print(std::string value)
{
	cout << value;
}

void Console::Println(std::string value)
{
	cout << value << endl;
}

void Console::Endline()
{
	cout << endl;
}

void Console::SetColor(WORD color)
{
	SetConsoleTextAttribute(m_hConsole, 12);
}

Console * Console::GetInstance()
{
	if (m_instance)
		return m_instance;
	else return new Console();
}
