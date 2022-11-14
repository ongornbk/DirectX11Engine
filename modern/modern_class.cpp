#include "modern_class.h"
#include <iostream>

modern_class::modern_class()
{
	this_handle.make_handle(this);

#ifdef MODERN_GUARDING_ENABLED
	m_lock = {};
#endif MODERN_GUARDING_ENABLED
}

modern_class::~modern_class()
{
	this_handle.Release();
}