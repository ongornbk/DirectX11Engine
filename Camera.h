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

	void InitializeOrthoMatrix(
		const int32 screenwidth,
		const int32 screenheight,
		const float screennear,
		const float screenfar
	);
	void InitializeProjectionMatrix(
		const float fow,
		const float screenaspect,
		const float screennear,
		const float screenfar
	);
	void SetPosition(
		const float x,
		const float y
	);
	void SetPosition(
		const float x,
		const float y,
		const float z
	);
	void SetPosition(
		const DirectX::XMVECTOR position
	);
	void SetRotation(
		const float x,
		const float y,
		const float z
	);
	void Release();

	static class Camera* GetCurrentCamera();

	const DirectX::XMVECTOR   GetPosition() const noexcept;
	const DirectX::XMVECTOR   GetRotation() const noexcept;
	const struct XMFLOAT4X4&  GetView() noexcept;
	const struct XMFLOAT4X4&  GetProjection() noexcept;
	const struct XMFLOAT4X4&  GetOrtho() noexcept;

	void Update();

private:

	struct DirectX::XMFLOAT4X4 m_view;
	struct DirectX::XMFLOAT4X4 m_projection;
	struct DirectX::XMFLOAT4X4 m_ortho;
	DirectX::XMVECTOR   m_position;
	DirectX::XMVECTOR   m_rotation;

};

