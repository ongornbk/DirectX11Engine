#include "BooleanVariableObjectIntersectsWithRegion.h"
#include "modern/modern_shared_guard.h"
#include "Region.h"
#include "RenderContainer.h"

BooleanVariableObjectIntersectsWithRegion::BooleanVariableObjectIntersectsWithRegion(const modern_handle& __object, const modern_handle& __region)
{
    object.make_handle(__object);
    region.make_handle(__region);
}

BooleanVariableObjectIntersectsWithRegion::BooleanVariableObjectIntersectsWithRegion(EObject* const __object, Region* const __region)
{
	object.make_handle(__object->GetHandle());
	region.make_handle(__region->GetHandle());
}

const bool BooleanVariableObjectIntersectsWithRegion::get()
{
	class EObject* const A = (class EObject* const)object.get();
	class Region* const B = (class Region* const)region.get();
	if (A&&B)
	{
		modern_shared_guard g0(A);
		modern_shared_guard g1(B);
		return B->Intersects(A);
	}
	return false;
}
