#include "FloatVariableDistanceBetweenObjects.h"
#include "Unit.h"


FloatVariableDistanceBetweenObjects::FloatVariableDistanceBetweenObjects(GameObject* const A, GameObject* const B)
{
	object_A.make_handle(A->GetHandle());
	object_B.make_handle(B->GetHandle());
}

const float FloatVariableDistanceBetweenObjects::get()
{
	//assert(object_A && object_B);
	class GameObject* const A = (class GameObject*)object_A.get();
	class GameObject* const B = (class GameObject*)object_B.get();
	if (A && B)
	{
		return modern_xfloat3_distance2(A->m_boundingSphere.Center,B->m_boundingSphere.Center);
	}
	return 0.f;
}
