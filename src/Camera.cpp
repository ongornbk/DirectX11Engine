#include "Camera.h"
#include "Defines.h"


extern "C"
{
#define XMVECTORNULL XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)
}

namespace
{
	static Camera *   m_currentCamera = NULL;
}

Camera::Camera(void)
{
	m_position = XMVECTORNULL;
	m_rotation = XMVECTORNULL;
	m_currentCamera = this;
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
	m_position = XMVectorSet(x, y, z,0.0f);
}
void Camera::SetPosition(float x, float y)
{
	m_position = XMVectorSet(x, y,m_position.m128_f32[2], 0.0f);
}
void Camera::SetPosition(XMVECTOR position)
{
	m_position = position;
}
void Camera::SetRotation(float x, float y, float z)
{
	m_rotation = XMVectorSet(x*(float)XM_PI/180.0f, y*(float)XM_PI / 180.0f, z*(float)XM_PI / 180.0f, 0.0f);
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

namespace
{
	namespace local
	{
		static XMVECTOR up;
		static XMVECTOR lookat;
		static XMMATRIX rotationMatrix;
	}
}

void Camera::Update()
{
local::up     = XMVectorSet(0.0f, 1.0f, 0.0f,0.0f);
local::lookat = XMVectorSet(0.0f, 0.0f, 1.0f,0.0f);
local::rotationMatrix = XMMatrixRotationRollPitchYaw(m_rotation.m128_f32[0],m_rotation.m128_f32[1],m_rotation.m128_f32[2]);

local::lookat = XMVector3TransformCoord(local::lookat, local::rotationMatrix);
local::up = XMVector3TransformCoord(local::up, local::rotationMatrix);

local::lookat += m_position;
XMStoreFloat4x4(&m_view, XMMatrixLookAtLH(m_position, local::lookat, local::up));
}
