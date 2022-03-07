#include "Camera.h"
#include "Defines.h"
#include "Global.h"
#include <DirectXMath.h>

namespace
{
	static class Camera*   m_currentCamera = nullptr;
	static class Global*   m_global = nullptr;

	static float m_zoom[10] = { 0.33f,0.66f,1.f,1.33f,1.5f,1.66f,1.75f,2.f,2.5f,3.f };
	static int64_t m_currentZoom = 2;
}

Camera::Camera(void)
{
	m_position = _mm_set_ps(0.0f, 0.0f, 0.0f, 0.0f);
	m_rotation = _mm_set_ps(0.0f, 0.0f, 0.0f, 0.0f);
	m_currentCamera = this;
	m_global = Global::GetInstance();
	DirectX::XMStoreFloat4x4(&m_interfaceOrtho, DirectX::XMMatrixOrthographicLH(1920.f, 1080.f, 10, 100));
}
Camera::~Camera(void)
{

}

void Camera::Release()
{
	delete(this);
}

class Camera * Camera::GetCurrentCamera()
{
	return m_currentCamera;
}



void Camera::InitializeOrthoMatrix(
	const int32 screenwidth,
	const int32 screenheight,
	const float screennear,
	const float screenfar
)
{
	DirectX::XMStoreFloat4x4(&m_ortho, DirectX::XMMatrixOrthographicLH((float)screenwidth, (float)screenheight, screennear, screenfar));
}

void Camera::InitializeProjectionMatrix(
	const float fow,
	const float screenaspect,
	const float screennear,
	const float screenfar
)
{
	DirectX::XMStoreFloat4x4(&m_projection, DirectX::XMMatrixPerspectiveFovLH(fow,screenaspect,screennear,screenfar));
}

void Camera::SetPosition(
	const float x,
	const float y,
	const float z
)
{
	m_position = _mm_set_ps(x, y, z, 0.f);
}
void Camera::SetPosition(
	const float x,
	const float y
)
{
	m_position = _mm_set_ps(x, y, 0.f, 0.f);
}
void Camera::SetPosition(
	const DirectX::XMVECTOR position
)
{
	m_position = position;
}
void Camera::Translate(const DirectX::XMVECTOR position)
{
	m_position += position;
}
void Camera::SetRotation(
	const float x,
	const float y,
	const float z
)
{
	m_rotation = _mm_set_ps(x*(float)XM_PI/180.f, y*(float)XM_PI / 180.f, z*XM_PI / 180.f, 0.f);
}
const DirectX::XMVECTOR Camera::GetPosition() const noexcept
{
	return m_position;
}
const DirectX::XMVECTOR Camera::GetRotation()const noexcept
{
	return m_rotation;
}
const struct DirectX::XMFLOAT4X4& Camera::GetView() noexcept
{
	return m_view;
}
const struct DirectX::XMFLOAT4X4& Camera::GetProjection() noexcept
{
	return m_projection;
}
const struct DirectX::XMFLOAT4X4& Camera::GetOrtho() noexcept
{
	return m_ortho;
}

const DirectX::XMFLOAT4X4& Camera::GetInterfaceOrtho() noexcept
{
	return m_interfaceOrtho;
}


void Camera::Update()
{
	DirectX::XMStoreFloat4x4(&m_ortho, DirectX::XMMatrixOrthographicLH(1920.f*m_zoom[m_currentZoom], 1080.f * m_zoom[m_currentZoom], 10, 100));
const struct DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(
	m_rotation.m128_f32[0],
	m_rotation.m128_f32[1],
	m_rotation.m128_f32[2]
);

DirectX::XMVECTOR lookat = DirectX::XMVector3TransformCoord(m_global->camera_lookat, rotationMatrix);
DirectX::XMVECTOR up = DirectX::XMVector3TransformCoord(m_global->camera_up, rotationMatrix);

lookat += m_position;
DirectX::XMStoreFloat4x4(&m_view, XMMatrixLookAtLH(m_position,lookat,up));
}

void Camera::ZoomIn() const noexcept
{
	if (m_currentZoom > 0)
		m_currentZoom -= 1;
}

void Camera::ZoomOut() const noexcept
{
	if (m_currentZoom < 9)
		m_currentZoom += 1;
}

const int64_t Camera::GetZoom() const noexcept
{
	return m_currentZoom;
}
