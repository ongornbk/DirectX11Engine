#include "modern_class.h"
#include <iostream>

modern_class::modern_class()
{
	this_handle.make_handle(this);
	m_lock = {};
}

modern_class::~modern_class()
{
	this_handle.Release();
}