#include "CameraControl.h"



CameraControl::CameraControl()
{
	m_camera = NULL;
	//m_target = NULL;
}


CameraControl::~CameraControl()
{
}

void CameraControl::LockCameraPositionOnUnit(Unit * unit)
{
	this->m_flags[0] = true;
	this->m_target.make_handle(unit->GetHandle());
}

void CameraControl::SetCurrentCamera(Camera * camera)
{
	this->m_camera = camera;
}

void CameraControl::Update(float dt)
{
	class Unit* const A = (class Unit*)m_target.get();
	if (A&&m_flags[0])
	{
		DirectX::XMFLOAT3 xvm = A->GetPosition();
		m_camera->SetPosition(xvm.x, xvm.y);
	}
	m_camera->Update();
}
