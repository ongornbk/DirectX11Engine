#include "Global.h"

namespace
{
	Global* m_instance;
}

Global::Global()
{
	m_lastPickedUnit = nullptr;
	m_lastSelectedUnit = nullptr;
	m_lastCreatedUnit = nullptr;
	m_lastTask = nullptr;
	m_instance = this;
	m_lastPoint = XMFLOAT3(0.0F, 0.0F, 0.0F);
}


Global::~Global()
{
}

Global* Global::GetInstance()
{
	return m_instance;
}

