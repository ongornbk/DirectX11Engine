#include "FloatVariableDistanceBetweenObjects.h"
#include "Unit.h"
#include "modern/modern_xmath.h"


FloatVariableDistanceBetweenObjects::FloatVariableDistanceBetweenObjects(EObject* const A, EObject* const B) : object_A(A), object_B(B)
{
}

const float FloatVariableDistanceBetweenObjects::get()
{
	assert(object_A && object_B);
	if (object_A && object_B)
	{
		return modern_xfloat3_distance2(object_A->m_boundingSphere.Center,object_B->m_boundingSphere.Center);
	}
	return 0.f;
}
