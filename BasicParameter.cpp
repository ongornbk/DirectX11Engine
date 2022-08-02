#include "BasicParameter.h"

const BasicParameter::BasicParameterValue BasicParameter::get()
{
	return m_value;
}

const enum class ParameterType BasicParameter::get_type() const modern_except_state
{
	return ParameterType::BASIC;
}

BasicParameter::BasicParameter(const float value)
{
	m_value.type__float = value;
}

BasicParameter::BasicParameter(const double value)
{
	m_value.type__double = value;
}

BasicParameter::BasicParameter(const int8 value)
{
	m_value.type__int8 = value;
}

BasicParameter::BasicParameter(const int16 value)
{
	m_value.type__int16 = value;
}

BasicParameter::BasicParameter(const int32 value)
{
	m_value.type__int32 = value;
}

BasicParameter::BasicParameter(const int64 value)
{
	m_value.type__int64 = value;
}

BasicParameter::BasicParameter(const uint8 value)
{
	m_value.type__uint8 = value;
}

BasicParameter::BasicParameter(const uint16 value)
{
	m_value.type__uint16 = value;
}

BasicParameter::BasicParameter(const uint32 value)
{
	m_value.type__uint32 = value;
}

BasicParameter::BasicParameter(const uint64 value)
{
	m_value.type__uint64 = value;
}

BasicParameter::~BasicParameter()
{
}
