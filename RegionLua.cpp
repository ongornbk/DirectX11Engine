#include "RegionLua.h"


void RegionLua::OnEnter(const class modern_handle& enteringObject)
{
	if (m_eventEntersBindStatus)
	{
		Global::GetInstance()->m_triggeringRegion.make_handle(this_handle);
		Global::GetInstance()->m_enteringObject.make_handle(enteringObject);
		EventManager::GetInstance()->EventRegionEntering();
	}
}

void RegionLua::OnLeave(const class modern_handle& leavingObject)
{
	if (m_eventLeavesBindStatus)
	{
		Global::GetInstance()->m_triggeringRegion.make_handle(this_handle);
		Global::GetInstance()->m_leavingObject.make_handle(leavingObject);
		EventManager::GetInstance()->EventRegionLeaving();
	}
}

	void RegionLua::Bind(std::string enters, std::string leaves)
	{
		m_eventEntersBindStatus++;
		m_eventLeavesBindStatus++;
		m_eventEnters = enters;
		m_eventLeaves = leaves;
	}
	void RegionLua::BindEnters(std::string enters)
	{
		m_eventEntersBindStatus++;
		m_eventEnters = enters;
	}
	void RegionLua::BindLeaves(std::string leaves)
	{
		m_eventLeavesBindStatus++;
		m_eventLeaves = leaves;
	}
	void RegionLua::Unbind()
	{
		m_eventEntersBindStatus = modern_false;
		m_eventLeavesBindStatus = modern_false;
		m_eventEnters.clear();
		m_eventLeaves.clear();
	}

	RegionLua::RegionLua(
		const struct DirectX::XMFLOAT2 pA,
		const struct DirectX::XMFLOAT2 pB)
		: Region(pA, pB)
	{

	}
	RegionLua::RegionLua(
		const float x1,
		const float y1,
		const float x2,
		const float y2
	) : Region(x1, y1, x2, y2)
	{

	}

