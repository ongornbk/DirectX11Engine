#include "CollisionCircle.h"



CollisionCircle::CollisionCircle() : BoundingSphere()
{
	Center = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	Radius = 0.0f;
}


CollisionCircle::~CollisionCircle()
{
}
