#include "RenderContainer.h"
#include <iostream>

const modern_handle& EObject::GetHandle()
{
    return m_object;
}

volatile modern_handle& EObject::GetHandle() volatile
{
    return m_object;
}

EObject::~EObject()
{
   // std::cout << "Wazzup!";
}
