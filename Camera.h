#pragma once

#include "gdef.h"

#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

class Camera
{
public:
	Camera(void);
	~Camera(void);

	void InitializeOrthoMatrix(const int32 screenwidth,const int32 screenheight,const float screennear,const float screenfar);
	void InitializeProjectionMatrix(const float fow,const float screenaspect,const float screennear,const float screenfar);
	void SetPosition(const float x, const float y);
	void SetPosition(const float x, const float y,const float z);
	void SetPosition(XMVECTOR position);
	void SetRotation(const float x,const float y,const float z);
	void Release();
	static Camera* GetCurrentCamera();

	XMVECTOR   GetPosition() const noexcept;
	XMVECTOR   GetRotation() const noexcept;
	XMFLOAT4X4 GetView() const noexcept;
	XMFLOAT4X4 GetProjection() const noexcept;
	XMFLOAT4X4 GetOrtho() const noexcept;

	void Update();

private:

	XMFLOAT4X4 m_view;
	XMFLOAT4X4 m_projection;
	XMFLOAT4X4 m_ortho;
	XMVECTOR   m_position;
	XMVECTOR   m_rotation;

};

