#pragma once
#include "Unit.h"
#include "Stack.h"
#include <stack>

class Global
{
public:
	Global(void);
	~Global(void);
	Unit* m_lastPickedUnit;
	Unit* m_lastSelectedUnit;
	Unit* m_lastCreatedUnit;
	Task* m_lastTask;
	static Global* GetInstance();
	XMFLOAT3 m_lastPoint;
	std::stack<Unit*> m_stack;
	uint32_t      m_size;

};

