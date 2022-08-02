#pragma once

#include "gdef.h"

#include <d3d11.h>
#include <directxmath.h>
#include "modern/modern_def.h"

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

	const DirectX::XMVECTOR   GetPosition() const modern_except_state;
	const DirectX::XMVECTOR   GetRotation() const modern_except_state;
	const struct DirectX::XMFLOAT4X4& GetView() modern_except_state;
	const struct DirectX::XMFLOAT4X4& GetProjection() modern_except_state;
	const struct DirectX::XMFLOAT4X4&  GetOrtho() modern_except_state;
	const struct DirectX::XMFLOAT4X4& GetInterfaceOrtho() modern_except_state;

	void Update();

	void ZoomIn() const modern_except_state;
	void ZoomOut() const modern_except_state;

	const int64_t GetZoom() const modern_except_state;

private:

	struct DirectX::XMFLOAT4X4 m_view;
	struct DirectX::XMFLOAT4X4 m_projection;
	struct DirectX::XMFLOAT4X4 m_ortho;
	struct DirectX::XMFLOAT4X4 m_interfaceOrtho;
	DirectX::XMVECTOR   m_position;
	DirectX::XMVECTOR   m_rotation;

};

