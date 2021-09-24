#include "modern_class.h"
#include <iostream>

modern_class::modern_class() : m_object(this)
{
	m_lock = {};
}

modern_class::~modern_class()
{
	m_object.Release();
	//std::cout << "Tired";
}