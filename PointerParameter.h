#pragma once
#include "IParameter.h"
#include "modern/modern_def.h"

class PointerParameter : public IParameter
{
	void* m_object;
public:
	PointerParameter(void* const object);
	~PointerParameter();

	void* const get();
	const enum class ParameterType get_type() const modern_except_state override;
};

