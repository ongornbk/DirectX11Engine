#include "Graphics.h"
#include "SettingsC.h"



Graphics::Graphics(void)
{
	m_dxManager = NULL;
}

Graphics::~Graphics(void)
{

}

bool Graphics::InitializeDX(HWND hwnd)
{
	m_dxManager = new DXManager();
	if (!m_dxManager->Initialize(*(Settings::get()->REALRESOLUTION_X),*(Settings::get()->REALRESOLUTION_Y), VSYNC_ENABLED, hwnd, FULL_SCREEN))
	{
		return false;
	}
	return true;
}

void Graphics::Initialize()
{
}

void Graphics::BeginScene(float r, float g, float b, float a)
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
	m_dxManager->Release();
}



DXManager * Graphics::GetDXManager()
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
