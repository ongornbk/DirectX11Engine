#pragma once
#include "Camera.h"
#include "Unit.h"

#include <modern__.h>

class CameraControl
{
public:
	CameraControl();
	~CameraControl();

	void LockCameraPositionOnUnit(class Unit* const unit);
	void SetCurrentCamera(class Camera* const camera);
	void Update(const float dt);
private:
	class Camera * m_camera;
	bool     m_flags[1];
	class modern_handle   m_target;
};

