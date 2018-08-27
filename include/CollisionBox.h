#pragma once
#include <DirectXCollision.h>

using namespace DirectX;

class CollisionBox : public BoundingSphere
{
public:
	CollisionBox(XMFLOAT3 position,float radius);
	~CollisionBox();

	bool         m_pushable;
};

