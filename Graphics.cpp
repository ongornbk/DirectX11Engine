#include "Graphics.h"
#include "SettingsC.h"
#include "LUAManager.h"
#include "LuaCallback.cpp"

Graphics::Graphics(void)
{
	m_dxManager = nullptr;
	m_vulcanManager = nullptr;
	m_direct2D = nullptr;
	m_gfxEngine = DIRECTX11;
}

Graphics::~Graphics(void)
{

}

bool Graphics::InitializeDX(HWND hwnd)
{
	m_dxManager = new DXManager();
	if (!m_dxManager->Initialize(*(Settings::get()->REALRESOLUTION_X),*(Settings::get()->REALRESOLUTION_Y),FULL_SCREEN, hwnd,VSYNC_ENABLED))
	{
		return false;
	}
	return true;
}

bool Graphics::InitializeVulcan(HWND hwnd)
{
	//m_vulcanManager = new VulcanManager();
	//return m_vulcanManager->Initialize(*(Settings::get()->REALRESOLUTION_X), *(Settings::get()->REALRESOLUTION_Y), FULL_SCREEN, hwnd, VSYNC_ENABLED);
	return true;
}

bool Graphics::InitializeDirect2D()
{
	//m_direct2D = new Direct2D();
	//return (bool)m_direct2D->CreateFactory();
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
	if(m_dxManager)
	m_dxManager->Release();
	//if(m_vulcanManager)
	//m_vulcanManager->Release();
	//if (m_direct2D)
	//	delete m_direct2D;
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
