#include "Input.h"
#include <iostream>
#include "GlobalUtilities.h"
#include "IPP.h"

using GlobalUtilities::Unacquire;

Input::DeviceReadingState Input::m_readingState = Input::DeviceReadingState::READ_KEYBOARDANDMOUSE;

static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

Input::Input(void)
{
	m_directInput = 0;
	m_keyboard = 0;
	m_mouse = 0;
	memset(m_keys,0, sizeof(bool)*s_NumKeys);
}


Input::~Input(void)
{
	Unacquire(m_mouse);
	Unacquire(m_keyboard);
	if (m_directInput)
	{
		(void)m_directInput->Release();
		m_directInput = NULL;
	}
}

bool Input::Initialize(HINSTANCE hInstance, HWND hwnd, int screenWidth, int screenHeight)
{
	HRESULT result;

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	m_mouseX = 0;
	m_mouseY = 0;

	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput,NULL);
	if (FAILED(result))
	{
		return false;
	}

	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if (FAILED(result))
	{
		return false;
	}

	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}

	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	result = m_keyboard->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if (FAILED(result))
	{
		return false;
	}

	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}

	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	result = m_mouse->Acquire();
	if (FAILED(result))
	{
		return false;
	}
	ipp::Console::Println(modern_string(L"DirectInput Initialized Successfully!"), MODERN_CONSOLE_TEXT_COLOR::LIGHTGREEN);
	return true;
}

bool Input::Refresh(HINSTANCE hInstance, HWND hwnd, int screenWidth, int screenHeight)
{
	if (hInstance && hwnd)
	{

		Unacquire(m_mouse);
		Unacquire(m_keyboard);
		if (m_directInput)
		{
			(void)m_directInput->Release();
			m_directInput = NULL;
		}
		return Initialize(hInstance, hwnd, screenWidth, screenHeight);
	}
	else
	{
		return false;
	}
}

bool __cdecl Input::Update()
{
	memcpy(m_prevKeys, m_keys, sizeof(bool)*s_NumKeys);
	memcpy(m_prevMouseState, m_mouseState.rgbButtons, sizeof(BYTE) * 4);
	bool result;
	result = ReadKeyboard();
	if (!result)return false;
	result = ReadMouse();
	if (!result) return false;
	ProcessInput();
	return true;
}

bool Input::IsKeyDown(unsigned int key)
{
	switch (m_readingState)
	{
	case READ_KEYBOARDANDMOUSE:
	{
		return m_keys[key];
	}break;
	case READ_KEYBOARD:
	{
		return m_keys[key];
	}break;
	default: return false;
	}
	return false;
}



bool Input::IsKeyHit(unsigned int key)
{
	switch (m_readingState)
	{
	case READ_KEYBOARDANDMOUSE:
	{
		return m_keys[key] && !m_prevKeys[key];
	}break;
	case READ_KEYBOARD:
	{
		return m_keys[key] && !m_prevKeys[key];
	}break;
	default: return false;
	}
	return false;
}

void Input::GetMousePosition(int & x, int & y)
{
	switch (m_readingState)
	{
	case READ_KEYBOARDANDMOUSE:
	{
		x = m_mouseX;
		y = m_mouseY;
	}break;
	case READ_MOUSE:
	{
		x = m_mouseX;
		y = m_mouseY;
	}break;
	default:
	{
		x = 0;
		y = 0;
	}
	}
}

void Input::SetReadingState(DeviceReadingState readingState)
{
	m_readingState = readingState;
}

bool Input::ReadKeyboard()
{
	HRESULT result;
	result = m_keyboard->GetDeviceState(sizeof(m_keys), (LPVOID)&m_keys);
	if (FAILED(result))
	{ 
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool Input::ReadMouse()
{
	if (m_mouse == NULL)
	{
		(void)m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
		return false;
	}

	HRESULT result;

	result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}
	return true;
}

void Input::ProcessInput()
{
	switch (m_readingState)
	{
	case READ_KEYBOARDANDMOUSE:
	{
		m_mouseX += m_mouseState.lX*2;
		m_mouseY += m_mouseState.lY*2;
		if (m_mouseX < 0)m_mouseX = 0;
		if (m_mouseY < 0)m_mouseY = 0;
		if (m_mouseX > m_screenWidth)m_mouseX = m_screenWidth;
		if (m_mouseY > m_screenHeight)m_mouseY = m_screenHeight;
	}break;
	case READ_KEYBOARD:
	{

	}break;
	case READ_MOUSE:
	{
		m_mouseX += m_mouseState.lX * 2;
		m_mouseY += m_mouseState.lY * 2;
		if (m_mouseX < 0)m_mouseX = 0;
		if (m_mouseY < 0)m_mouseY = 0;
		if (m_mouseX > m_screenWidth)m_mouseX = m_screenWidth;
		if (m_mouseY > m_screenHeight)m_mouseY = m_screenHeight;
	}break;
	case READ_NOTHING: break;
	default: break;
	}
	


}

BYTE Input::GetMouseState(int index)
{
	return m_mouseState.rgbButtons[index];
}

bool Input::GetMousePressed(int32_t index)
{
	return m_mouseState.rgbButtons[index] && !m_prevMouseState[index];
}

void Input::Release()
{
	delete(this);
}
