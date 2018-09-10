#pragma once
#include "VulcanManager.h"
#include "DXManager.h"
#include "2D/Direct2D.h"
#include "Defines.h"



class Graphics
{
public:
	Graphics(void);
	~Graphics(void);

	bool InitializeDX(HWND hwnd);
	bool InitializeVulcan(HWND hwnd);
	bool InitializeDirect2D();
	void Initialize();
	void BeginScene(float r, float g, float b, float a);
	void BeginScene(float* color);
	void EndScene();

	void EnableAlphaBlending(bool enable);
	void EnableZBuffer(bool enable);
	void Release();



	DXManager* GetDXManager();
	HWND GetHwnd();
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void SetHwnd(HWND hwnd);

	enum GraphicsEngine
	{
		VULCAN,
		DIRECTX11
	} m_gfxEngine;

private:

	DXManager*     m_dxManager;
	VulcanManager* m_vulcanManager;
	Direct2D*      m_direct2D;
	HWND m_hwnd;
};