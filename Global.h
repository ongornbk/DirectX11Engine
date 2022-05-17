#pragma once
#include "Unit.h"
#include "VariablesManager.h"
#include "Doodads.h"
#include "gdef.h"
#include "modern/modern_handle.h"
#include "modern/modern_pack4.h"
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
	modern_handle                      m_triggeringRegion;
	modern_handle                      m_leavingObject;
	modern_handle                      m_enteringObject;
	MSVC_VOLATILE ObjectFlags          m_lastFlags{};
	MSVC_VOLATILE Task*                m_lastTask;
	static Global*       GetInstance();
	struct DirectX::XMFLOAT3             m_lastPoint;
	std::stack<Unit*>    m_stack;
	VariablesManager     m_variables;
	uint32               m_size;

	XMVECTOR camera_up;
	XMVECTOR camera_lookat;

	std::map<modern_pack4, int64> m_testMap;

	void getS(std::string name) const;
	void release();

	
};

