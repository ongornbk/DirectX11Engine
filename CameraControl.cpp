#include "CameraControl.h"



CameraControl::CameraControl()
{
	m_camera = NULL;
	m_target = NULL;
}


CameraControl::~CameraControl()
{
}

void CameraControl::LockCameraPositionOnUnit(Unit * unit)
{
	this->m_flags[0] = true;
	this->m_target = unit;
}

void CameraControl::SetCurrentCamera(Camera * camera)
{
	this->m_camera = camera;
}

void CameraControl::Update(float dt)
{
	if (m_flags[0])
	{
		XMFLOAT3 xvm = m_target->GetPosition();
		m_camera->SetPosition(xvm.x, xvm.y);
	}
	m_camera->Update();
}
