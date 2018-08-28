#pragma once


#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

class Camera
{
public:
	Camera(void);
	~Camera(void);

	void InitializeOrthoMatrix(int screenwidth, int screenheight, float screennear, float screenfar);
	void InitializeProjectionMatrix(float fow,float screenaspect,float screennear,float screenfar);
	void SetPosition(float x, float y);
	void SetPosition(float x, float y, float z);
	void SetPosition(XMVECTOR position);
	void SetRotation(float x, float y, float z);
	void Release();
	static Camera* GetCurrentCamera();

	XMVECTOR   GetPosition();
	XMVECTOR   GetRotation();
	XMFLOAT4X4 GetView();
	XMFLOAT4X4 GetProjection();
	XMFLOAT4X4 GetOrtho();

	void Update();

private:

	XMFLOAT4X4 m_view;
	XMFLOAT4X4 m_projection;
	XMFLOAT4X4 m_ortho;
	XMVECTOR   m_position;
	XMVECTOR   m_rotation;

};

