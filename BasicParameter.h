#pragma once
#include "IParameter.h"
class BasicParameter :
	public IParameter
{
public:
	union BasicParameterValue
	{
		float type__float;
		double type__double;
		int8 type__int8;
		int16 type__int16;
		int32 type__int32;
		int64 type__int64;
		uint8 type__uint8;
		uint16 type__uint16;
		uint32 type__uint32;
		uint64 type__uint64;

	public:

		explicit BasicParameterValue()
		{
			type__int64 = 0;
		}
	};

protected:
	union BasicParameterValue m_value;
public:
	BasicParameter(const float value);
	BasicParameter(const double value);
	BasicParameter(const int8 value);
	BasicParameter(const int16 value);
	BasicParameter(const int32 value);
	BasicParameter(const int64 value);
	BasicParameter(const uint8 value);
	BasicParameter(const uint16 value);
	BasicParameter(const uint32 value);
	BasicParameter(const uint64 value);
	~BasicParameter();

	const union BasicParameterValue get();
	const enum class ParameterType get_type() const noexcept override;
};

