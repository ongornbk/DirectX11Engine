#pragma once
#include "Camera.h"
#include "Unit.h"

class CameraControl
{
public:
	CameraControl();
	~CameraControl();

	void LockCameraPositionOnUnit(Unit* unit);
	void SetCurrentCamera(Camera* camera);
	void Update(float dt);
private:
	Camera * m_camera;
	bool     m_flags[1];
	Unit*    m_target;
};

