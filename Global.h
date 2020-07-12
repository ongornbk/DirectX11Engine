#pragma once
#include "Unit.h"
#include "VariablesManager.h"
#include "Doodads.h"
#include "gdef.h"
#include <stack>

class Global
{
	
public:
	Global(void);
	~Global(void);
	MSVC_VOLATILE Unit*                m_lastPickedUnit;
	MSVC_VOLATILE Unit*                m_lastSelectedUnit;
	MSVC_VOLATILE EObject*             m_lastCreatedRenderContainer;
	MSVC_VOLATILE class EObject*       m_pickedObject{};
	MSVC_VOLATILE EObjectFlags         m_lastFlags{};
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

