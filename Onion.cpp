
#include "Onion.h"
#include <atomic>
#include <mutex>
#include <iostream>
#include <fstream>


__int64 Onion::Timer::m_prevFrame = 0;
__int64 Onion::Timer::m_currentFrame = 0;
__int64 Onion::Timer::m_freq = 0;
float Onion::Timer::m_deltaTime = 0.0f;


namespace
{
	static Onion::Console* m_instance = nullptr;
	static std::mutex m_consoleMutex;
}

Onion::Console::~Console(void)
{
}

Onion::Console::Console(void) : __Console()
{

}

Onion::Console* Onion::Console::GetInstance()
{
	std::lock_guard<std::mutex> guard(m_consoleMutex);
	if (m_instance)
	{
		return m_instance;
	}
	else return new Console();
}

void Onion::Console::Release()
{
	if (m_instance)
	{
		delete m_instance;
		m_instance = NULL;
	}
}

void Onion::Console::Println(std::string text)
{
	GetInstance()->__Print(text + "\n");
}

void Onion::Console::Println(std::string text, TextColors color)
{
	GetInstance()->__Print(text + "\n", color);
}

void Onion::Console::Println(std::string text, std::wstring wide, TextColors color)
{
	GetInstance()->__Print(text, wide, color);
}

void Onion::Console::Println(std::string text, const int value)
{
	GetInstance()->__Print(text+ "\n", value);
}

void Onion::Console::Println(float number)
{
	GetInstance()->__Println(number);
}

void Onion::Console::Println(uint32_t number)
{
	GetInstance()->__Println(number);
}

void Onion::Console::Print(std::string text)
{
	GetInstance()->__Print(text);
}

void Onion::Console::Print(float number)
{
	GetInstance()->__Print(number);
}

void Onion::Console::Print(int number)
{
	GetInstance()->__Print(number);
}

void Onion::Console::Print(void * address)
{
	GetInstance()->__Print(address);
}

void Onion::Console::Flush()
{
	GetInstance()->__Flush();
}

void Onion::Console::SetCursorPosition(int16_t x, int16_t y)
{
	GetInstance()->__SetCursorPosition(x, y);
}

void Onion::Console::SetTextColor(TextColors color)
{
	GetInstance()->__SetTextColor(color);
}

void Onion::Console::SetTextColor(uint16_t color)
{
	GetInstance()->__SetTextColor(color);
}

void Onion::Console::SetTitle(std::string title)
{
	SetConsoleTitle(title.c_str());
}

std::string Onion::Console::GetInput()
{
	return GetInstance()->GetInput();
}



Onion::__Console::__Console(void)
{
	m_outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(m_outputHandle, &m_screenBuffer);
}

Onion::__Console::~__Console(void)
{
}

void Onion::__Console::__Println(float number)
{
	printf("%f\n",number);
}

void Onion::__Console::__Println(uint32_t number)
{
	printf("%u\n", number);
}

void Onion::__Console::__Print(std::string text)
{
	printf("%s", text.c_str());
}

void Onion::__Console::__Print(std::string text, TextColors color)
{
	SetConsoleTextAttribute(m_outputHandle, color);
	printf("%s", text.c_str());
}

void Onion::__Console::__Print(std::string text, std::wstring wide, TextColors color)
{
	SetConsoleTextAttribute(m_outputHandle, color);
	printf("%s", text.c_str());
	wprintf(L"%s", wide.c_str());
}

void Onion::__Console::__Print(std::string text, const int32_t value)
{
	printf("%s%d", text.c_str(),value);
}

void Onion::__Console::__Print(float number)
{
	printf("%f", number);
}

void Onion::__Console::__Print(int32_t number)
{
	printf("%d", number);
}

void Onion::__Console::__Print(void * address)
{
	printf("%p", address);
}

void Onion::__Console::__Flush()
{
	DWORD written;
	FillConsoleOutputCharacterA(m_outputHandle, ' ', m_screenBuffer.dwSize.X * m_screenBuffer.dwSize.Y, { 0,0 }, &written);
	FillConsoleOutputAttribute(m_outputHandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, m_screenBuffer.dwSize.X * m_screenBuffer.dwSize.Y, { 0,0 }, &written);
	__SetCursorPosition(0u, 0u);
}

void Onion::__Console::__SetCursorPosition(int16_t x, int16_t y)
{
	SetConsoleCursorPosition(m_outputHandle, { x,y });
}

void Onion::__Console::__SetTextColor(TextColors color)
{
	SetConsoleTextAttribute(m_outputHandle, color);
}

void Onion::__Console::__SetTextColor(uint16_t color)
{
	SetConsoleTextAttribute(m_outputHandle, color);
}

std::string Onion::__Console::__GetInput()
{
	std::string input{};
	std::getline(std::cin,input);
	return input;
}

void Onion::Timer::Update()
{
	m_deltaTime = 0.0f;
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_freq);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_currentFrame);
	int deltaTicks = (int)(m_currentFrame - m_prevFrame);
	m_deltaTime = ((float)deltaTicks / (float)m_freq);
	m_prevFrame = m_currentFrame;
}

float Onion::Timer::GetDeltaTime()
{
	float dt = m_deltaTime;
	if (dt <= 0.0f || dt > 1.0f)
	{
		dt = 0.025f;
	}

	return dt;
}

void Onion::Timer::GetDeltaTime(float & dt)
{
	dt = m_deltaTime;
	if (dt <= 0.0f || dt > 1.0f)
	{
		dt = 0.025f;
	}
}

float Onion::Math::Sin(float degrees)
{
	return sin(degrees * (Onion::PI / 180.0f));
}

float Onion::Math::Cos(float degrees)
{
	return cos(degrees * (Onion::PI / 180.0f));
}

float Onion::Math::Tan(float degrees)
{
	return tan(degrees * (Onion::PI / 180.0f));
}

float Onion::Math::Asin(float degrees)
{
	return asin(degrees) * (180.0f / Onion::PI);
}

float Onion::Math::Acos(float degrees)
{
	return acos(degrees) * (180.0f / Onion::PI);
}

float Onion::Math::Atan(float degrees)
{
	return atan(degrees) * (180.0f / Onion::PI);
}

float Onion::Math::Atan2(float y, float x)
{
	return atan2(y, x) * (180.0f / Onion::PI);
}

void Onion::Math::SquashInt32(int32_t & value, int32_t min, int32_t max) noexcept
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

bool Onion::Math::CheckInt32(int32_t & value, int32_t min, int32_t max) noexcept
{
		if (value > max)
		{
			return false;
		}
		if (value < min)
		{
			return false;
		}
		return true;
}

void Onion::Math::SquashInt32Array(int32_t * value, int32_t size,int32_t min,int32_t max) noexcept
{
		for (char i = 0; i < size; i++)
		{
			if (value[i] > max) value[i] = max;
			else if (value[i] < min) value[i] = min;
		}
		return;
}

uint8_t _cdecl Onion::Math::RandomUint8(uint8_t min, uint8_t max) noexcept
{
	return min + (rand() % int32_t(max - min + 1));
}

int Onion::System::GetScreenWidth() noexcept
{
	return GetSystemMetrics(SM_CXSCREEN);
}

int Onion::System::GetScreenHeight() noexcept
{
	return GetSystemMetrics(SM_CYSCREEN);
}

std::string Onion::System::GetFileName(const std::string & s) noexcept
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

void Onion::System::Exit(const int32_t return_value) noexcept
{
	if (return_value)
		Onion::Console::Println("System::Exit Code : ",return_value);
	std::exit(return_value);
}
