#pragma once
#include "modern/modern_cstring.h"
#include "modern/modern_handle.h"

class IBindableBehavior
{
protected:
	int64_t m_key = (-1);
public:
	virtual void Bind(const modern_cstring& option) = 0;
};

