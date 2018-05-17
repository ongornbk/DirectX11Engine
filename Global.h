#pragma once
#include "Unit.h"

class Global
{
public:
	Global(void);
	~Global(void);
	Unit* m_lastSelectedUnit;
	Unit* m_lastCreatedUnit;
	Task* m_lastTask;
	static Global* GetInstance();
	XMFLOAT3 m_lastPoint;

};

