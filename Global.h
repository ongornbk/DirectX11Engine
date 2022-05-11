#pragma once
#include "Unit.h"
#include "VariablesManager.h"
#include "Doodads.h"
#include "gdef.h"
#include "modern/modern_handle.h"
#include <stack>

class Global
{
	
public:
	Global(void);
	~Global(void);
	modern_handle                      m_lastPickedUnit;
	modern_handle                      m_dyingUnit;
	modern_handle                      m_killingUnit;
	modern_handle                      m_triggeringUnit;
	modern_handle                      m_lastSelectedUnit;
	modern_handle                      m_lastCreatedRenderContainer;
	modern_handle                      m_pickedObject;
	MSVC_VOLATILE ObjectFlags          m_lastFlags{};
	MSVC_VOLATILE Task*                m_lastTask;
	static Global*       GetInstance();
	struct DirectX::XMFLOAT3             m_lastPoint;
	std::stack<Unit*>    m_stack;
	VariablesManager     m_variables;
	uint32               m_size;

	XMVECTOR camera_up;
	XMVECTOR camera_lookat;

	void getS(std::string name) const;

	
};

