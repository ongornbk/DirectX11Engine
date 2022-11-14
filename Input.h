#pragma once
#define DIRECTINPUT_VERSION 0X0800
#include <dinput.h>
#include <cstdint>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"Xinput.lib")
#pragma comment(lib,"dxguid.lib")

class Input
{
public:
	Input(void);
	~Input(void);

	enum DeviceReadingState
	{
		READ_KEYBOARD,READ_MOUSE,READ_KEYBOARDANDMOUSE,READ_NOTHING
	};

	bool Initialize(HINSTANCE hInstance, HWND hwnd, int screenWidth, int screenHeight);
	bool Refresh(HINSTANCE hInstance, HWND hwnd, int screenWidth, int screenHeight);
	bool Update();
	void Release();

	bool IsKeyDown(unsigned int key);
	bool IsKeyHit(unsigned int key);
	void GetMousePosition(int& x, int& y);
	void SetReadingState(DeviceReadingState readingState);
	BYTE GetMouseState(int index);
	bool GetMousePressed(int32_t index);

private:
	const static int s_NumKeys = 256;
	static DeviceReadingState m_readingState;

	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();
	

	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;
	DIMOUSESTATE m_mouseState;

	bool m_keys[s_NumKeys];
	bool m_prevKeys[s_NumKeys];

	BYTE m_prevMouseState[4];

	int m_screenWidth;
	int m_screenHeight;
	int m_mouseX;
	int m_mouseY;
};

