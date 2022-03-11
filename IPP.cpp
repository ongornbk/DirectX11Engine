#include "IPP.h"
#include <mutex>
#include <iostream>
#include <fstream>
#include <string>
#include <inttypes.h>


namespace
{
	static ipp::Console* m_instance = nullptr;
	static std::mutex m_consoleMutex;
}

ipp::Console::~Console(void)
{
}

ipp::Console::Console(void) : __Console()
{

}

ipp::Console* ipp::Console::GetInstance()
{
	std::lock_guard<std::mutex> guard(m_consoleMutex);
	if (m_instance)
	{
		return m_instance;
	}
	else return new Console();
}

void ipp::Console::Release()
{
	if (m_instance)
	{
		delete m_instance;
		m_instance = NULL;
	}
}

void ipp::Console::Println(std::string text)
{
	GetInstance()->__Print(text + "\n");
}

void ipp::Console::Println(std::wstring text)
{
	GetInstance()->__Print((const wchar_t*)(text + L"\n").c_str());
}

void ipp::Console::Println(std::string text, TextColors color)
{
	GetInstance()->__Print(text + "\n", color);
}

void ipp::Console::Println(std::string text, std::wstring wide, TextColors color)
{
	GetInstance()->__Print(text, wide, color);
}

void ipp::Console::Println(std::string text, const int value)
{
	GetInstance()->__Print(text+ "\n", value);
}

void ipp::Console::Println(float number)
{
	GetInstance()->__Println(number);
}

void ipp::Console::Println(uint32_t number)
{
	GetInstance()->__Println(number);
}

void ipp::Console::Println(uint64_t number)
{
	GetInstance()->__Println(number);
}

void ipp::Console::Print(std::string text)
{
	GetInstance()->__Print(text);
}

void ipp::Console::Print(const char * text)
{
	GetInstance()->__Print(text);
}

void ipp::Console::Print(const wchar_t* text)
{
	GetInstance()->__Print(text);
}

void ipp::Console::Print(float number)
{
	GetInstance()->__Print(number);
}

void ipp::Console::Print(int number)
{
	GetInstance()->__Print(number);
}

void ipp::Console::Print(char ch)
{
	GetInstance()->__Print(ch);
}

void ipp::Console::Print(void * address)
{
	GetInstance()->__Print(address);
}

void ipp::Console::Flush()
{
	GetInstance()->__Flush();
}

void ipp::Console::SetCursorPosition(int16_t x, int16_t y)
{
	GetInstance()->__SetCursorPosition(x, y);
}

void ipp::Console::SetTextColor(TextColors color)
{
	GetInstance()->__SetTextColor(color);
}

void ipp::Console::SetTextColor(uint16_t color)
{
	GetInstance()->__SetTextColor(color);
}

void ipp::Console::SetTitle(std::string title)
{
	SetConsoleTitle(title.c_str());
}

std::string ipp::Console::GetInput()
{
	return GetInstance()->__GetInput();
}



ipp::__Console::__Console(void)
{
	m_outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(m_outputHandle, &m_screenBuffer);
}

ipp::__Console::~__Console(void)
{
}

void ipp::__Console::__Println(float number)
{
	printf("%f\n",number);
}

void ipp::__Console::__Println(uint32_t number)
{
	printf("%u\n", number);
}

void ipp::__Console::__Print(std::string text)
{
	printf("%s", text.c_str());
}

void ipp::__Console::__Print(const char * text)
{
	printf("%s", text);
}

void ipp::__Console::__Print(const wchar_t* text)
{
	wprintf(L"%s", text);
}

void ipp::__Console::__Print(std::string text, TextColors color)
{
	SetConsoleTextAttribute(m_outputHandle, color);
	printf("%s", text.c_str());
}

void ipp::__Console::__Print(std::string text, std::wstring wide, TextColors color)
{
	SetConsoleTextAttribute(m_outputHandle, color);
	printf("%s", text.c_str());
	wprintf(L"%s", wide.c_str());
}

void ipp::__Console::__Print(std::string text, const int32_t value)
{
	printf("%s%d", text.c_str(),value);
}

void ipp::__Console::__Print(float number)
{
	printf("%f", number);
}

void ipp::__Console::__Print(int32_t number)
{
	printf("%d", number);
}

void ipp::__Console::__Print(char ch)
{
	printf("%c", ch);
}

void ipp::__Console::__Println(uint64_t number)
{
	printf("%" PRIu64, number);
}

void ipp::__Console::__Print(void * address)
{
	printf("%p", address);
}

void ipp::__Console::__Flush()
{
	DWORD written;
	FillConsoleOutputCharacterA(m_outputHandle, ' ', m_screenBuffer.dwSize.X * m_screenBuffer.dwSize.Y, { 0,0 }, &written);
	FillConsoleOutputAttribute(m_outputHandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, m_screenBuffer.dwSize.X * m_screenBuffer.dwSize.Y, { 0,0 }, &written);
	__SetCursorPosition(0u, 0u);
}

void ipp::__Console::__SetCursorPosition(int16_t x, int16_t y)
{
	SetConsoleCursorPosition(m_outputHandle, { x,y });
}

void ipp::__Console::__SetTextColor(TextColors color)
{
	SetConsoleTextAttribute(m_outputHandle, color);
}

void ipp::__Console::__SetTextColor(uint16_t color)
{
	SetConsoleTextAttribute(m_outputHandle, color);
}

std::string ipp::__Console::__GetInput()
{
	std::string input{};
	std::getline(std::cin,input);
	return input;
}




void _fastcall ipp::math::clamp(char& value, const char min, const char max)
{
	if (value > max)
	{
		value = max;
		return;
	}
	if (value < min)
	{
		value = min;
		return;
	}
}


void _fastcall ipp::math::clamp(int32 & value,const int32 min,const int32 max)
{
		if (value > max)
		{
			Console::Println((uint32_t)value);
			value = max;
			return;
		}
		if (value < min)
		{
			value = min;
			return;
		}
}

void _fastcall ipp::math::clamp(float & value,const float min,const float max)
{
	if (value > max)
	{
		value = max;
		return;
	}
	if (value < min)
	{
		value = min;
		return;
	}
}

int32 _fastcall ipp::math::range(int32 &value,const int32 min,const int32 max)
{
		if (value > max)
		{
			return 0;
		}
		if (value < min)
		{
			return 0;
		}
		return 1;
}

void  ipp::math::SquashInt32Array(int32 * value,const int32 size,const int32 min,const int32 max) noexcept
{
		for (int32 i = 0; i < size; ++i)
		{
			if (value[i] > max) value[i] = max;
			else if (value[i] < min) value[i] = min;
		}
		return;
}

void ipp::math::SquashInt32Array(DirectX::XMINT2& int2, const int32 min, const int32 max) noexcept
{
	if (int2.x > max) int2.x = max;
	else if (int2.x < min) int2.x = min;
	if (int2.y > max) int2.y = max;
	else if (int2.y < min) int2.y = min;
}

int32 ipp::math::SquashInt32ArrayWithCheck(int32 * value,const int32 size,const int32 min,const int32 max) noexcept
{
	int32 out = 0;
	for (int32 i = 0; i < size; ++i)
	{
		if (value[i] > max)
		{
			value[i] = max;
			out = 1;
		}
		else if (value[i] <= min)
		{
			value[i] = min;
			out = 1;
		}
	}
	return out;
}

uint8 _cdecl ipp::math::RandomUint8(const uint8 min,const uint8 max) noexcept
{
	return min + (rand() % int32(max - min + 1));
}

int32 _stdcall ipp::math::RandomInt32(const int32 min, const int32 max) noexcept
{
	return min + (rand() % int32(max - min + 1));
}

int32 ipp::System::GetScreenWidth() noexcept
{
	return GetSystemMetrics(SM_CXSCREEN);
}

int32 ipp::System::GetScreenHeight() noexcept
{
	return GetSystemMetrics(SM_CYSCREEN);
}

std::string ipp::System::GetFileName(const std::string & s) noexcept
{
	char sep = '/';

#ifdef _WIN32
	sep = '\\';
#endif

	// cout << "in get_file_name\n";
	size_t i = s.rfind(sep, s.length());
	if (i != std::string::npos) {
		return (s.substr(i + 1, s.length() - i));
	}

	return ("");
}


void _stdcall ipp::System::Exit(const int32 return_value) noexcept
{
	if (return_value)
		ipp::Console::Println("System::Exit Code : ",return_value);
	std::exit(return_value);
}
