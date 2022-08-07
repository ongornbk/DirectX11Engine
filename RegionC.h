#pragma once
#include "Region.h"

class RegionC : public Region
{
	void OnEnter(const class modern_handle& enteringObject) override;
	void OnLeave(const class modern_handle& leavingObject) override;

	void (*m_eventEnters)(void);
	void (*m_eventLeaves)(void);

	modern_handle m_parent;

	RegionC();

public:

	RegionC(const struct DirectX::XMFLOAT2 pA, const struct DirectX::XMFLOAT2 pB, void (*cscript_enter)(void), void (*cscript_leave)(void));
	RegionC(const float x1, const float y1, const float x2, const float y2, void (*cscript_enter)(void), void (*cscript_leave)(void));

	void SetParent(const class modern_handle& parent);

	class modern_handle& GetParent();

	~RegionC();
};
