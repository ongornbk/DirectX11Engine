#include "FloatVariableDistanceBetweenObjects.h"
#include "Unit.h"
#include "modern/modern_xmath.h"


FloatVariableDistanceBetweenObjects::FloatVariableDistanceBetweenObjects(EObject* const A, EObject* const B)
{
	object_A.make_handle(A);
	object_B.make_handle(B);
}

const float FloatVariableDistanceBetweenObjects::get()
{
	//assert(object_A && object_B);
	class EObject* const A = (class EObject*)object_A.get();
	class EObject* const B = (class EObject*)object_B.get();
	if (A && B)
	{
		return modern_xfloat3_distance2(A->m_boundingSphere.Center,B->m_boundingSphere.Center);
	}
	return 0.f;
}
