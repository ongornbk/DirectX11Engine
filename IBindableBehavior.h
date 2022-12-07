#pragma once

#include <modern__.h>

class IBindableBehavior
{
protected:
	int64_t m_key = (-1);
public:
	virtual void Bind(const class modern_cstring& option) = 0;
};

