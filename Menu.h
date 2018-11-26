#pragma once
#include <Windows.h>

#pragma comment(lib,"comctl32.lib")

class Menu
{
public:

	enum MenuEvents
	{
	MENU_EXIT = 100
	};

	Menu(HWND parent, HINSTANCE hInstance);
	~Menu();

private:
	HWND m_toolbar;
};

