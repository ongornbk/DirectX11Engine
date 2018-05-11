#include "FrameWork.h"
#include "Defines.h"
#include "Timer.h"
#include "GlobalUtilities.h"
#include <iostream>
#include "SettingsC.h"

using namespace std;


LRESULT CALLBACK WndProc(HWND hwnd, unsigned int message, WPARAM wParam, LPARAM lParam);

namespace
{
	static FrameWork* Instance = nullptr;
}

FrameWork::FrameWork(void)
{
	Instance = this;
	m_hDC = NULL;
}

FrameWork::~FrameWork(void)
{
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL,0);
	}
	Engine::GetEngine()->Release();
	//UnregisterClass(m_applicationName, m_hInstance);
	//m_hInstance = NULL;
}

bool FrameWork::Initialize(GameComponent* gameComponent)
{
	
	if (!CreateDXWindow("USiA",WINDOW_POS_X,WINDOW_POS_Y, (*(Settings::get()->RESOLUTION_X)), (*(Settings::get()->RESOLUTION_Y))))
	{
		return false;
	}

	Engine::GetEngine()->SetGameComponent(gameComponent);

	if (!Engine::GetEngine()->Initialize(m_hInstance, Engine::GetEngine()->GetGraphics()->GetHwnd(),this))
	{
		return false;
	}

	return true;
}

void FrameWork::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0u, 0u, PM_REMOVE))
		{
			(void)TranslateMessage(&msg);
			(void)DispatchMessage(&msg);
		}
		else
		{
			Timer::Update();
			Engine::GetEngine()->Run();
		}
	}
}

bool FrameWork::CreateDXWindow(char* windowTitle, int x, int y, int width, int height)
{
	ShowCursor(false);
	HWND hwnd;
	WNDCLASSEX wc;
	m_applicationName = windowTitle;
	m_hInstance = GetModuleHandle(NULL);

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "RegisterClassEx() failed", "Error", MB_OK);
		return false;
	}

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight= GetSystemMetrics(SM_CYSCREEN);

	if (FULL_SCREEN)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}
	else
	{
		screenWidth = width;
		screenHeight = height;
	}

	int nStyle = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX;

	hwnd = CreateWindowEx(WS_EX_APPWINDOW, windowTitle, windowTitle,nStyle,x,y,screenWidth,screenHeight,NULL,NULL,m_hInstance,NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "CreateWindowEx() failed", "Error", MB_OK);
		Engine::GetEngine()->Release();
		PostQuitMessage(0);
		return false;
	}

	m_hDC = GetDC(hwnd);

	if (!Engine::GetEngine()->InitializeGraphics(hwnd))
	{
		MessageBox(hwnd, "Could not initialize DirectX 11", "Error", MB_OK);
		Engine::GetEngine()->Release();
		PostQuitMessage(0);
		UnregisterClass(m_applicationName, m_hInstance);
		m_hInstance = NULL;
		DestroyWindow(hwnd);
		return false;
	}

	Engine::GetEngine()->GetGraphics()->SetHwnd(hwnd);

	ShowWindow(hwnd, SW_SHOW);
	(void)SetForegroundWindow(hwnd);
	(void)SetFocus(hwnd);
	cout << "FrameWork : Window has been created" << endl;
	return true;
}



LRESULT CALLBACK WndProc(HWND hwnd, unsigned int message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	
	switch (message)
	{
	case WM_QUIT:
		if (Instance)
		{
			delete Instance;
			Instance = NULL;
		}
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		
	}break;
	case WM_CLOSE:
	{
		if (Instance)
		{
			delete Instance;
			Instance = NULL;
		}
		break;
	}break;
	
	default:
	{
		
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
	}
}