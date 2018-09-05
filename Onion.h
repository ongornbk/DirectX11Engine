#pragma once
#include <string>
#include <Windows.h>
#include <atomic>

namespace Onion
{

#define SQR(x)						((x) * (x))
#define ABS(x) ((x)<0 ? -(x) : (x))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

	constexpr double     PI_extended = 3.14159265358979323844;
	constexpr float      PI = 3.14159f;
	constexpr float      E = 2.71828f;

	enum TextColors
	{
		DARKBLUE = 1,
		DARKGREEN = 2,
		OCEANBLUE = 3,
		DARKRED = 4,
		PURPLE = 5,
		GOLDEN = 6,
		LIGHTGRAY = 7,
		DARKGRAY = 8,
		BLUE = 9,
		LIGHTGREEN = 10,
		LIGHTBLUE = 11,
		RED = 12,
		PINK = 13,
		YELLOW = 14,
		WHITE = 15
	};

	template <class returntype, class type> inline returntype memory_cast(type obj)
	{
		return *(returntype*)(obj);
	}

	namespace Math
	{
		float Sin(float degrees);
		float Cos(float degrees);
		float Tan(float degrees);
		float Asin(float degrees);
		float Acos(float degrees);
		float Atan(float degrees);
		float Atan2(float y, float x);
		void SquashInt32(int &value, int min, int max) noexcept;
		bool CheckInt32(int &value, int min, int max) noexcept;
		void SquashInt32Array(int* value, int size,int min,int max) noexcept;
	}

	namespace System
	{
		int _stdcall GetScreenWidth() noexcept;
		int _stdcall GetScreenHeight() noexcept;
		std::string _stdcall GetFileName(const std::string &s) noexcept;
		void _stdcall Exit(const int return_value = 0) noexcept;
	}

	class __Console
	{
	protected:
		explicit __Console(void);
		~__Console(void);
		void __Println(float number);
		void __Println(uint32_t number);
		void __Print(std::string text);
		void __Print(std::string text, TextColors color);
		void __Print(std::string text, std::wstring wide, TextColors color);
		void __Print(std::string text,const int32_t value);
		void __Print(float number);
		void __Print(int32_t number);
		void __Print(void* address);
		void __Flush();
		void __SetCursorPosition(int16_t x, int16_t y);
		void __SetTextColor(TextColors color);
		void __SetTextColor(uint16_t color);
		std::string __GetInput();


		HANDLE                     m_outputHandle;
		CONSOLE_SCREEN_BUFFER_INFO m_screenBuffer;


	};

	class Console : __Console
	{
	public:
		~Console(void);
		static Console* GetInstance();
		static void Release();
		static void Println(std::string text);
		static void Println(std::string text, TextColors color);
		static void Println(std::string text,std::wstring wide, TextColors color);
		static void Println(std::string text, const int value);
		static void Println(float number);
		static void Println(uint32_t number);
		static void Print(std::string text);
		static void Print(float number);
		static void Print(int number);
		static void Print(void* address);
		static void Flush();
		static void SetCursorPosition(int16_t x, int16_t y);
		static void SetTextColor(TextColors color);
		static void SetTextColor(uint16_t color);
		static void SetTitle(std::string title);
		static std::string GetInput();
	private:
		explicit Console(void);

	};

	class Timer
	{
	public:

		static void Update();

		static float GetDeltaTime();
		static void  GetDeltaTime(float &dt);
	private:

		static int64_t m_prevFrame;
		static int64_t m_currentFrame;
		static int64_t m_freq;
		static float m_deltaTime;
	};






}
