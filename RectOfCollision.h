#pragma once
#include "Unit.h"
#include <set>

class RectOfCollision : public modern_class
{
protected:
	modern_handle pointA;
	modern_handle pointB;
	modern_handle pointC;
	modern_handle pointD;

	friend class RectOfCollisionAgentFirst;
	friend class RectOfCollisionAgentSecond;

	std::set<modern_handle> m_objects;
	BoundingBox              m_rect;
public:
	RectOfCollision(const struct DirectX::XMFLOAT2 pA, const struct DirectX::XMFLOAT2 pB);
	~RectOfCollision();

	class RectOfCollisionAgentSecond* const GetSecond();

	const modern_handle& GetHandle();
	volatile modern_handle& GetHandle() volatile;
};

