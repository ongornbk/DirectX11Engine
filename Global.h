#pragma once
#include "Unit.h"
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
	EObject*             m_lastCreatedRenderContainer;
	class EObject*       m_pickedObject{};
	EObjectFlags         m_lastFlags{};
	Task*                m_lastTask;
	static Global*       GetInstance();
	struct DirectX::XMFLOAT3             m_lastPoint;
	std::stack<Unit*>    m_stack;
	VariablesManager     m_variables;
	uint32               m_size;

	XMVECTOR camera_up;
	XMVECTOR camera_lookat;

	void getS(std::string name) const;

	
};

