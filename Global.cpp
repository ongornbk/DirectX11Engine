#include "Global.h"

namespace
{
	Global* m_instance;
}

Global::Global()
{
	m_lastSelectedModel = NULL;
	m_instance = this;
}


Global::~Global()
{
}

Global* Global::GetInstance()
{
	return m_instance;
}

