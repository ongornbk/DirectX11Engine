#include "Global.h"

namespace
{
	Global* m_instance;
}

Global::Global()
{
	m_lastSelectedUnit = NULL;
	m_lastCreatedUnit = NULL;
	m_lastTask = NULL;
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

