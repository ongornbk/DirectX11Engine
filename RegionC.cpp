#include "RegionC.h"

void RegionC::OnEnter(const class modern_handle& enteringObject)
{
	Global::GetInstance()->m_triggeringRegion.make_handle(this_handle);
	Global::GetInstance()->m_enteringObject.make_handle(enteringObject);
	m_eventEnters();
}

void RegionC::OnLeave(const class modern_handle& leavingObject)
{
	Global::GetInstance()->m_triggeringRegion.make_handle(this_handle);
	Global::GetInstance()->m_leavingObject.make_handle(leavingObject);
	m_eventLeaves();
}


	RegionC::RegionC(
		const struct DirectX::XMFLOAT2 pA,
		const struct DirectX::XMFLOAT2 pB,
		void (*cscript_enter)(void),
		void (*cscript_leave)(void))
		: Region(pA, pB)
	{
		m_eventEnters = cscript_enter;
		m_eventLeaves = cscript_leave;
	}
	RegionC::RegionC(
		const float x1,
		const float y1,
		const float x2,
		const float y2,
		void (*cscript_enter)(void),
		void (*cscript_leave)(void))
		: Region(x1, y1, x2, y2)
	{
		m_eventEnters = cscript_enter;
		m_eventLeaves = cscript_leave;
	}

	void RegionC::SetParent(const class modern_handle& parent)
	{
		m_parent.make_handle(parent);
	}

	class modern_handle& RegionC::GetParent()
	{
		return m_parent;
	}

	RegionC::~RegionC()
	{

	}

