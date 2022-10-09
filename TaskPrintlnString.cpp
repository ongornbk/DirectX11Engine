#include "TaskPrintlnString.h"
#include "IPP.h"

TaskPrintlnString::TaskPrintlnString(const class modern_string& str, enum MODERN_CONSOLE_TEXT_COLOR color) : m_color(color)
{
	m_str = str;
}

TaskPrintlnString::~TaskPrintlnString()
{
}

void TaskPrintlnString::execute()
{
	//ipp::Console::Println(m_str, m_color);
	//throw modern_exception(m_str);
	ipp::Console::GetInstance()->__Println(m_str, m_color);
}
