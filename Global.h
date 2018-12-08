#pragma once
#include "Unit.h"
#include "Stack.h"
#include "VariablesManager.h"
#include "Doodads.h"
#include <stack>

class Global
{
public:
	Global(void);
	~Global(void);
	Unit*                m_lastPickedUnit;
	Unit*                m_lastSelectedUnit;
	RenderContainer*     m_lastCreatedRenderContainer;
	RenderContainerFlags m_lastFlags{};
	Task*                m_lastTask;
	static Global*       GetInstance();
	XMFLOAT3             m_lastPoint;
	std::stack<Unit*>    m_stack;
	VariablesManager     m_variables;
	uint32_t             m_size;

	XMVECTOR camera_up;
	XMVECTOR camera_lookat;


};

