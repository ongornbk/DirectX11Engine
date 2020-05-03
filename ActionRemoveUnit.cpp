#include "ActionRemoveUnit.h"

ActionRemoveUnit::ActionRemoveUnit(Unit* const unit) : m_unit(unit)
{
}

ActionRemoveUnit::~ActionRemoveUnit()
{
}

void ActionRemoveUnit::execute()
{
	if (m_unit)
	{
		m_unit->Release();
		CleanupFrame();
		class Global* const global = Global::GetInstance();
		if (m_unit == global->m_lastSelectedUnit)
			global->m_lastSelectedUnit = nullptr;
	}
}
