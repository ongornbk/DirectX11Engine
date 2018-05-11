#pragma once
#include "DXManager.h"
#include "Defines.h"



class Graphics
{
public:
	Graphics(void);
	~Graphics(void);

	bool InitializeDX(HWND hwnd);
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

private:

	DXManager* m_dxManager;
	HWND m_hwnd;
};