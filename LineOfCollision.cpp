#include "LineOfCollision.h"
#include "RendererManager.h"
#include "Timer.h"
#include "ActionRemoveObject.h"

LineOfCollision::LineOfCollision(const DirectX::XMFLOAT2 pA, const DirectX::XMFLOAT2 pB)
{
	pointA.make_handle((new LineOfCollisionAgent())->GetHandle());
	pointB.make_handle((new LineOfCollisionAgent())->GetHandle());

	class LineOfCollisionAgent* const A = (class LineOfCollisionAgent* const)pointA.get();
	class LineOfCollisionAgent* const B = (class LineOfCollisionAgent* const)pointB.get();

	A->Initialize(pA,this);
	B->Initialize(pB,this);

	XMVECTOR aV = {pA.x,pA.y,0.f,0.f};
	XMVECTOR bV = { pB.x,pB.y,0.f,0.f };

	BoundingBox::CreateFromPoints(m_rect, aV, bV);

	RendererManager::GetInstance()->PushLineOfCollisionAgent(A);
	RendererManager::GetInstance()->PushLineOfCollisionAgent(B);
}

LineOfCollision::~LineOfCollision()
{
	Timer::CreateInstantTimer(new class ActionRemoveObject((class LineOfCollisionAgent* const)pointA.get()));
	Timer::CreateInstantTimer(new class ActionRemoveObject((class LineOfCollisionAgent* const)pointB.get()));
}

LineOfCollisionAgent* const LineOfCollision::GetSecond(LineOfCollisionAgent* const first)
{
	class LineOfCollisionAgent* const A = (class LineOfCollisionAgent* const)pointA.get();
	class LineOfCollisionAgent* const B = (class LineOfCollisionAgent* const)pointB.get();
	if (first == A)
		return B;
	return A;
}

const modern_handle& LineOfCollision::GetHandle()
{
	return m_object;
}

volatile modern_handle& LineOfCollision::GetHandle() volatile
{
	return m_object;
}
