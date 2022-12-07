#include "FrameWork.h"
#include "Defines.h"
#include "IPP.h"
#include "GlobalUtilities.h"
#include "SettingsC.h"
#include "MPManager.h"
#include <omp.h>

LRESULT CALLBACK WndProc(HWND hwnd, uint32_t message, WPARAM wParam, LPARAM lParam);

namespace
{
	static FrameWork* Instance = nullptr;
}

FrameWork::FrameWork(void)
{
	Instance = this;
	m_hDC = NULL;
	//m_menu = nullptr;
}

FrameWork::~FrameWork(void)
{
	if (Settings::GetFullscreen())
	{
		ChangeDisplaySettings(NULL,0);
	}
	//if (m_menu)
	//{
	//	delete m_menu;
	//	m_menu = nullptr;
	//}
	Engine::GetEngine()->Release();
	//UnregisterClass(m_applicationName, m_hInstance);
	//m_hInstance = NULL;
}

bool FrameWork::Initialize(GameComponent* gameComponent)
{
	
	if (!CreateDXWindow("Legion",0,0,Settings::GetResolutionX(),Settings::GetResolutionY()))
	{
		return false;
	}

	Engine::GetEngine()->SetGameComponent(gameComponent);

	if (!Engine::GetEngine()->Initialize(m_hInstance, Engine::GetEngine()->GetGraphics()->GetHwnd(),this))
	{
		return false;
	}

	//if (true/*Settings::Menu*/)
	//{
		//m_menu = new Menu(m_hwnd,m_hInstance);
	//}

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
			
			Engine::GetEngine()->Run();
		}
	}

}

void FrameWork::SetComponent(GameComponent* gameComponent)
{
	Engine::GetEngine()->SetGameComponent(gameComponent);
}

HINSTANCE FrameWork::GetHInstance()
{
	return m_hInstance;
}

bool FrameWork::CreateDXWindow(char* windowTitle, int x, int y, int width, int height)
{
	ShowCursor(false);
	WNDCLASSEX wc;
	m_applicationName = windowTitle;
	m_hInstance = GetModuleHandle(NULL);
	m_icon = LoadIcon(m_hInstance, MAKEINTRESOURCE("favicon.ico"));

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DROPSHADOW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = m_icon;
	wc.hIconSm = m_icon;
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

	int32_t screenWidth = modern_system_get_screen_width();
	int32_t screenHeight = modern_system_get_screen_height();

	if (Settings::GetFullscreen())
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

	DWORD nStyle = WS_OVERLAPPEDWINDOW;
	DWORD extStyle = 0;

	m_hwnd = CreateWindowEx(extStyle, windowTitle, windowTitle,nStyle,x,y,screenWidth,screenHeight,NULL,NULL,m_hInstance,NULL);
	//SetWindowLong(m_hwnd, GWL_STYLE, WS_CAPTION);

	if (m_hwnd == NULL)
	{
		MessageBox(NULL, "CreateWindowEx() failed", "Error", MB_OK);
		Engine::GetEngine()->Release();
		PostQuitMessage(0);
		return false;
	}

	m_hDC = GetDC(m_hwnd);

	if (!Engine::GetEngine()->InitializeGraphics(m_hwnd))
	{
		MessageBox(m_hwnd, "Could not initialize DirectX 11", "Error", MB_OK);
		Engine::GetEngine()->Release();
		PostQuitMessage(0);
		UnregisterClass(m_applicationName, m_hInstance);
		m_hInstance = NULL;
		DestroyWindow(m_hwnd);
		return false;
	}

	Engine::GetEngine()->GetGraphics()->SetHwnd(m_hwnd);

	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);
	return true;
}



LRESULT CALLBACK WndProc(HWND hwnd, uint32_t message, WPARAM wParam, LPARAM lParam)
{
	
	switch (message)
	{
	case WM_CREATE:
	{
		//SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(NULL, "favicon.ico"));
		break;
	}

	case WM_QUIT:
		if (Instance)
		{
			delete Instance;
			Instance = NULL;
		}
		break;
	case WM_CLOSE:
		MPManager::Get()->barrier();
		PostQuitMessage(WM_CLOSE);
		break;
	case WM_ACTIVATEAPP:
		class Graphics* const gfx = Engine::GetEngine()->GetGraphics();
		const bool fullscreen = (bool)wParam;
		if(gfx)
		gfx->SetFullScreen((bool)wParam);
		if (fullscreen)
		{
			MoveWindow(hwnd, 0, 0, 1920, 1080, TRUE);
			//Input* input = Engine::GetEngine()->GetInput();
		//	if (Instance && input)
		//	{
		//		input->Refresh(Instance->GetHInstance(), hwnd, 1920, 1080);
		//	}
		}
		else
		{
			MoveWindow(hwnd, 0, 0, 640, 480, TRUE);
		//	Input* input = Engine::GetEngine()->GetInput();
		//	if (Instance && input)
		//	{
		//		input->Refresh(Instance->GetHInstance(), hwnd, 640, 480);
		//	}
		}
		break;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);

}