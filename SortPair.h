#pragma once
#include "GameObject.h"
class SortPair
{
public:
	SortPair(class GameObject* const A, class GameObject* const B);
	class GameObject* m_A;
	class GameObject* m_B;
};

