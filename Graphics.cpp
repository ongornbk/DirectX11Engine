#include "Graphics.h"
#include "SettingsC.h"
#include "LUAManager.h"
#include "LuaCallback.cpp"

extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}

Graphics::Graphics(void)
{
	m_dxManager = nullptr;
	m_fullscreen = true;
}

Graphics::~Graphics(void)
{

}

bool Graphics::InitializeDirectX(HWND hwnd)
{
	m_dxManager = new DXManager();
	if (!m_dxManager->Initialize(Settings::GetResolutionX(),Settings::GetResolutionY(),Settings::GetFullscreen(), hwnd,Settings::GetVsync()))
	{
		return false;
	}
	return true;
}

void Graphics::Initialize()
{
}

void Graphics::BeginScene(const float r,const float g,const float b,const float a)
{
	m_dxManager->BeginScrene(r, g, b, a);
}

void Graphics::BeginScene(float* color)
{
	m_dxManager->BeginScrene(color);
}

void Graphics::EndScene()
{
	m_dxManager->EndScene();
}

void Graphics::SetFullScreen(bool fullscreen)
{
	m_fullscreen = fullscreen;
	m_dxManager->SetFullScreen(fullscreen);
}

void Graphics::EnableAlphaBlending(bool enable)
{
	m_dxManager->EnableAlphaBlending(enable);
}

void Graphics::EnableZBuffer(bool enable)
{
	m_dxManager->EnableZBuffer(enable);
}

void Graphics::Release()
{
	if(m_dxManager)
	m_dxManager->Release();
}



DXManager * Graphics::GetDirectXManager()
{
	return m_dxManager;
}

HWND Graphics::GetHwnd()
{
	return m_hwnd;
}

ID3D11Device * Graphics::GetDevice()
{
	return m_dxManager->GetDevice();
}

ID3D11DeviceContext * Graphics::GetDeviceContext()
{
	return m_dxManager->GetDeviceContext();
}

void Graphics::SetHwnd(HWND hwnd)
{
	m_hwnd = hwnd;
}
