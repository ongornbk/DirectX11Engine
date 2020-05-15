#include "PointerParameter.h"

PointerParameter::PointerParameter(void* const object)
{
	m_object = object;
}

PointerParameter::~PointerParameter()
{

}

void* const PointerParameter::get()
{
	return m_object;
}

const enum class ParameterType PointerParameter::get_type() const noexcept
{
	return ParameterType::POINTER;
}
