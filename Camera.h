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
	void Translate(
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
	const struct DirectX::XMFLOAT4X4& GetView() noexcept;
	const struct DirectX::XMFLOAT4X4& GetProjection() noexcept;
	const struct DirectX::XMFLOAT4X4&  GetOrtho() noexcept;
	const struct DirectX::XMFLOAT4X4& GetInterfaceOrtho() noexcept;

	void Update();

	void ZoomIn() const noexcept;
	void ZoomOut() const noexcept;

	const int64_t GetZoom() const noexcept;

private:

	struct DirectX::XMFLOAT4X4 m_view;
	struct DirectX::XMFLOAT4X4 m_projection;
	struct DirectX::XMFLOAT4X4 m_ortho;
	struct DirectX::XMFLOAT4X4 m_interfaceOrtho;
	DirectX::XMVECTOR   m_position;
	DirectX::XMVECTOR   m_rotation;

};

