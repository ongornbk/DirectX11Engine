#include "CollisionBox.h"



CollisionBox::CollisionBox(XMFLOAT3 position,float radius)
{
	this->Center = position;
	this->Radius = radius;
	m_pushable = false;
}


CollisionBox::~CollisionBox()
{
}
