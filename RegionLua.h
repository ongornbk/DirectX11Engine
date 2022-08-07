#pragma once
#include "Region.h"

class RegionLua : public Region
{
	friend class EventManager;

	void OnEnter(const class modern_handle& enteringObject) override;

	void OnLeave(const class modern_handle& leavingObject) override;

	modern_Boolean m_eventEntersBindStatus = modern_false;
	modern_Boolean m_eventLeavesBindStatus = modern_false;

	std::string m_eventEnters;
	std::string m_eventLeaves;

public:

	void Bind(std::string enters, std::string leaves);
	void BindEnters(std::string enters);
	void BindLeaves(std::string leaves);
	void Unbind();

	RegionLua(const struct DirectX::XMFLOAT2 pA, const struct DirectX::XMFLOAT2 pB);
	RegionLua(const float x1, const float y1, const float x2, const float y2);
};