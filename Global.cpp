#include "Global.h"

namespace
{
	Global* m_instance;
}

Global::Global()
{
	m_lastPickedUnit = nullptr;
	m_lastSelectedUnit = nullptr;
	m_lastTask = nullptr;
	m_instance = this;
	m_lastCreatedRenderContainer = nullptr;
	m_lastPoint = XMFLOAT3(0.0F, 0.0F, 0.0F);
	camera_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	camera_lookat = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
}


Global::~Global()
{
}

Global* Global::GetInstance()
{
	return m_instance;
}

