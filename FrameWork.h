#pragma once
#define WIN32_LEAN_AND_MEAN

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "Engine.h"
#include "WindowHandle.h"
#include "Menu.h"


class FrameWork : WindowHandle
{
public:
	FrameWork(void);
	~FrameWork(void);

	bool Initialize(GameComponent* gameComponent);
	void Run();
	void SetComponent(GameComponent* component);

protected:
private:
	bool CreateDXWindow(char* windowTitle, int x, int y, int width, int height);
	char* m_applicationName;

	Menu*     m_menu;
	HINSTANCE m_hInstance;
	HDC       m_hDC;
};