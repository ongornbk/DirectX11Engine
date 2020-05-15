#pragma once
#include "IAction.h"
#include "Vector.h"
class ITrigger
{
	class Vector<class IAction*> m_actions;
	bool m_active;
public:
};

