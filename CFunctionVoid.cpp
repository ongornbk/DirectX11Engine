#include "CFunctionVoid.h"

CFunctionVoid::CFunctionVoid(void(*vfo)(void)) : ICFunction(vfo)
{
}

CFunctionVoid::~CFunctionVoid()
{
}

void CFunctionVoid::execute()
{
	reinterpret_cast<void(*)()> (m_f) ();
}
