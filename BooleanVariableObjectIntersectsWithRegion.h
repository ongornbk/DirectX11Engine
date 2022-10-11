#pragma once
#include "IBooleanVariable.h"
#include "modern/modern_handle.h"
#include "modern/modern_guard.h"

class GameObject;
class Region;

class BooleanVariableObjectIntersectsWithRegion :
	public IBooleanVariable
{
	class modern_handle object;
	class modern_handle region;
public:
	BooleanVariableObjectIntersectsWithRegion(const class modern_handle& __object, const class modern_handle& __region);
	BooleanVariableObjectIntersectsWithRegion(class GameObject* const __object, class Region* const __region);
	const bool get() override;
};

