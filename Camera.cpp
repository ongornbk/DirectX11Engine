#include "Camera.h"
#include "Defines.h"
#include "Global.h"
#include <DirectXMath.h>

namespace
{
	static Camera*   m_currentCamera = nullptr;
	static Global*   m_global = nullptr;
}

Camera::Camera(void)
{
	m_position = _mm_set_ps(0.0f, 0.0f, 0.0f, 0.0f);
	m_rotation = _mm_set_ps(0.0f, 0.0f, 0.0f, 0.0f);
	m_currentCamera = this;
	m_global = Global::GetInstance();
}
Camera::~Camera(void)
{

}

void Camera::Release()
{
	delete(this);
}

Camera * Camera::GetCurrentCamera()
{
	return m_currentCamera;
}



void Camera::InitializeOrthoMatrix(int screenwidth, int screenheight, float screennear, float screenfar)
{
	XMStoreFloat4x4(&m_ortho, XMMatrixOrthographicLH((float)screenwidth, (float)screenheight, screennear, screenfar));
}

void Camera::InitializeProjectionMatrix(float fow, float screenaspect, float screennear, float screenfar)
{
	XMStoreFloat4x4(&m_projection, XMMatrixPerspectiveFovLH(fow,screenaspect,screennear,screenfar));
}

void Camera::SetPosition(float x, float y, float z)
{
	m_position = _mm_set_ps(x, y, z, 0.f);
}
void Camera::SetPosition(float x, float y)
{
	m_position = _mm_set_ps(x, y, 0.f, 0.f);
}
void Camera::SetPosition(XMVECTOR position)
{
	m_position = position;
}
void Camera::SetRotation(float x, float y, float z)
{
	m_rotation = _mm_set_ps(x*(float)XM_PI/180.0f, y*(float)XM_PI / 180.0f, z*XM_PI / 180.0f, 0.0f);
}
XMVECTOR Camera::GetPosition()
{
	return m_position;
}
XMVECTOR Camera::GetRotation()
{
	return m_rotation;
}
XMFLOAT4X4 Camera::GetView()
{
	return m_view;
}
XMFLOAT4X4 Camera::GetProjection()
{
	return m_projection;
}
XMFLOAT4X4 Camera::GetOrtho()
{
	return m_ortho;
}


void Camera::Update()
{

XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(m_rotation.m128_f32[0],m_rotation.m128_f32[1],m_rotation.m128_f32[2]);

XMVECTOR lookat = XMVector3TransformCoord(m_global->camera_lookat, rotationMatrix);
XMVECTOR up = XMVector3TransformCoord(m_global->camera_up, rotationMatrix);

lookat += m_position;
XMStoreFloat4x4(&m_view, XMMatrixLookAtLH(m_position,lookat,up));
}
