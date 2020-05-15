#include "SPointerParameter.h"
#include "UserInterfaceGame.h"

SPointerParameter::SPointerParameter(void*& object)
{
	m_object = &(volatile void*)object;
}

SPointerParameter::~SPointerParameter()
{
}

volatile void* const SPointerParameter::get()
{
	return *m_object;
}

const enum class ParameterType SPointerParameter::get_type() const noexcept
{
	return ParameterType::SPOINTER;
}
