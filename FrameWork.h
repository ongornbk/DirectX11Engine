#pragma once
#define WIN32_LEAN_AND_MEAN
#include "Engine.h"
#include "WindowHandle.h"


class FrameWork : WindowHandle
{
public:
	FrameWork(void);
	~FrameWork(void);

	bool Initialize(GameComponent* gameComponent);
	void Run();
	HDC  GetHDC();

protected:
private:
	bool CreateDXWindow(char* windowTitle, int x, int y, int width, int height);
	char* m_applicationName;


	HINSTANCE m_hInstance;
	HDC       m_hDC;
};