#include "BooleanVariableObjectIntersectsWithRegion.h"
#include "Region.h"
#include "GameObject.h"

BooleanVariableObjectIntersectsWithRegion::BooleanVariableObjectIntersectsWithRegion(const modern_handle& __object, const modern_handle& __region)
{
    object.make_handle(__object);
    region.make_handle(__region);
}

BooleanVariableObjectIntersectsWithRegion::BooleanVariableObjectIntersectsWithRegion(GameObject* const __object, Region* const __region)
{
	object.make_handle(__object->GetHandle());
	region.make_handle(__region->GetHandle());
}

const bool BooleanVariableObjectIntersectsWithRegion::get()
{
	class GameObject* const A = (class GameObject* const)object.get();
	class Region* const B = (class Region* const)region.get();
	if (A&&B)
	{
		modern_shared_guard g0(A);
		modern_shared_guard g1(B);
		return B->Intersects(A);
	}
	return false;
}
