#include "Global.h"
#include "ActionMap.h"
#include <map>
namespace
{
	Global* m_instance;
	std::map<std::string, void*> m_gmap;
}

Global::Global()
{
	//m_lastPickedUnit = nullptr;
	//m_lastSelectedUnit = nullptr;
	m_lastTask = nullptr;
	m_instance = this;
	//m_lastCreatedRenderContainer = nullptr;
	m_lastPoint = XMFLOAT3(0.0F, 0.0F, 0.0F);
	camera_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	camera_lookat = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	m_gmap["pickedObject"] = (void*)m_pickedObject.get();
}


Global::~Global()
{
}

Global* Global::GetInstance()
{
	if(m_instance)
	return m_instance;
	else return new Global();
}

void Global::getS(std::string name) const
{
	ActionMap::GetInstance()->PushPointer(m_gmap[name]);
}

