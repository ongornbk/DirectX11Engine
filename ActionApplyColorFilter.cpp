#include "ActionApplyColorFilter.h"

ActionApplyColorFilter::ActionApplyColorFilter(Unit* const object, DirectX::XMFLOAT4& color) : m_object(object), m_color(color)
{
}

ActionApplyColorFilter::~ActionApplyColorFilter()
{
}

void ActionApplyColorFilter::execute()
{
#pragma omp single
	if (m_object)
	{
		m_object->SetColorFilter(m_color);
	}
}
