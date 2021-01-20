#pragma once

#include "DXManager.h"
#include "Defines.h"



class Graphics
{
public:
	Graphics(void);
	~Graphics(void);

	bool InitializeDirectX(HWND hwnd);
	void Initialize();
	void BeginScene(const float r,const float g,const float b,const float a);
	void BeginScene(float* color);
	void EndScene();
	void SetFullScreen(bool fullscreen);

	void EnableAlphaBlending(bool enable);
	void EnableZBuffer(bool enable);
	void Release();



	DXManager* GetDirectXManager();
	HWND GetHwnd();
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void SetHwnd(HWND hwnd);


private:

	bool           m_fullscreen;
	DXManager*     m_dxManager;

	HWND m_hwnd;
};