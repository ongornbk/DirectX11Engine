#pragma once
#include "Unit.h"

class Global
{
public:
	Global(void);
	~Global(void);
	Unit* m_lastSelectedUnit;
	Unit* m_lastCreatedUnit;
	static Global* GetInstance();

};

