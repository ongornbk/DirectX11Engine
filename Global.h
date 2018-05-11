#pragma once
#include "Unit.h"

class Global
{
public:
	Global(void);
	~Global(void);
	Unit* m_lastSelectedUnit;
	static Global* GetInstance();

};

