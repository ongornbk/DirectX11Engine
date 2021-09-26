#include "modern_class.h"
#include <iostream>

modern_class::modern_class()
{
	m_object.make_handle(this);
	m_lock = {};
	//std::cout << "Tired";
}

modern_class::~modern_class()
{
	m_object.Release();
	//std::cout << "Tired";
}