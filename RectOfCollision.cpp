#include "RectOfCollision.h"
#include "RendererManager.h"
#include "RectOfCollisionAgentFirst.h"
#include "RectOfCollisionAgentSecond.h"
#include "Timer.h"
#include "ActionRemoveObject.h"

RectOfCollision::RectOfCollision(const DirectX::XMFLOAT2 pA, const DirectX::XMFLOAT2 pB)
{
	pointA.make_handle((new RectOfCollisionAgentFirst())->GetHandle());
	pointB.make_handle((new RectOfCollisionAgentSecond())->GetHandle());

	class RectOfCollisionAgentFirst* const A = (class RectOfCollisionAgentFirst* const)pointA.get();
	class RectOfCollisionAgentSecond* const B = (class RectOfCollisionAgentSecond* const)pointB.get();

	//A->Initialize(pA, this);
	//B->Initialize(pB, this);

	XMVECTOR aV = { pA.x,pA.y,0.f,0.f };
	XMVECTOR bV = { pB.x,pA.y,0.f,0.f };
	XMVECTOR cV = { pB.x,pB.y,0.f,0.f };
	XMVECTOR dV = { pA.x,pB.y,0.f,0.f };

	BoundingBox::CreateFromPoints(m_rect, aV, bV);

	RendererManager::GetInstance()->PushRectOfCollisionAgent(A);
	RendererManager::GetInstance()->PushRectOfCollisionAgent(B);
}

RectOfCollision::~RectOfCollision()
{
	Timer::CreateInstantTimer(new class ActionRemoveObject((class RectOfCollisionAgentFirst* const)pointA.get()));
	Timer::CreateInstantTimer(new class ActionRemoveObject((class RectOfCollisionAgentSecond* const)pointA.get()));
}

RectOfCollisionAgentSecond* const RectOfCollision::GetSecond()
{
	return (class RectOfCollisionAgentSecond* const)pointB.get();
}

const modern_handle& RectOfCollision::GetHandle()
{
	return m_object;
}

volatile modern_handle& RectOfCollision::GetHandle() volatile
{
	return m_object;
}
