#include "FloatVariableUnitDistanceFromCamera.h"
#include "Unit.h"
#include "Camera.h"
#include "modern/modern_xmath.h"
#include <cassert>

FloatVariableUnitDistanceFromCamera::FloatVariableUnitDistanceFromCamera(Unit* const __unit) : unit(__unit)
{
}

const float FloatVariableUnitDistanceFromCamera::get()
{
	assert(unit);
	if (unit)
	{
		return modern_xfloat3_distance2(unit->GetPosition(), DirectX::XMFLOAT3(Camera::GetCurrentCamera()->GetPosition().m128_f32));
	}
	return 0.f;
}
