#pragma once
#include "LineOfCollisionAgent.h"
#include "Unit.h"
#include <set>

class LineOfCollision : public modern_class
{
	modern_handle pointA;
	modern_handle pointB;
protected:
	friend class LineOfCollisionAgent;
	std::set<modern_handle> m_objects;
	BoundingBox              m_rect;
public:
	LineOfCollision(const struct DirectX::XMFLOAT2 pA, const struct DirectX::XMFLOAT2 pB);
	~LineOfCollision();

	LineOfCollisionAgent* const GetSecond(LineOfCollisionAgent* const first);

	const modern_handle& GetHandle();
	volatile modern_handle& GetHandle() volatile;
};

