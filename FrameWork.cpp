#include "FrameWork.h"
#include "Defines.h"
#include "IPP.h"
#include "GlobalUtilities.h"
#include "SettingsC.h"
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
	
	if (!CreateDXWindow("USiA",0,0,Settings::GetResolutionX(),Settings::GetResolutionY()))
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
			ipp::Timer::Update();
			Engine::GetEngine()->Run();
		}
	}
}

bool FrameWork::CreateDXWindow(char* windowTitle, int x, int y, int width, int height)
{
	ShowCursor(false);
	WNDCLASSEX wc;
	m_applicationName = windowTitle;
	m_hInstance = GetModuleHandle(NULL);

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL,"IDI_ICON1");
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

	int screenWidth = ipp::System::GetScreenWidth();
	int screenHeight = ipp::System::GetScreenHeight();

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

	int nStyle = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX;

	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, windowTitle, windowTitle,nStyle,x,y,screenWidth,screenHeight,NULL,NULL,m_hInstance,NULL);

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
	//case WM_COMMAND:
	//{
	//	switch (LOWORD(wParam))
	//	{
	//	case Menu::MenuEvents::MENU_EXIT:
	//	{
			//PostQuitMessage(WM_COMMAND);
			//break;
	//	}
	//	}
	//	break;
//	}
	case WM_QUIT:
		if (Instance)
		{
			delete Instance;
			Instance = NULL;
		}
		break;
	case WM_CLOSE:
		PostQuitMessage(WM_CLOSE);
		break;
	case WM_ACTIVATEAPP:
		class Graphics* const gfx = Engine::GetEngine()->GetGraphics();
		if(gfx)
		gfx->SetFullScreen((bool)wParam);
		break;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);

}