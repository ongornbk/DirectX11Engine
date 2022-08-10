#pragma once
#include "modern_def.h"


struct modern_element
{
	struct modern_element*          next;
	void*                    data;

	constexpr modern_element(struct modern_element* const __next, void* __data)
		: next(__next),data(__data)
	{

	}
};