#pragma once
#include "modern_math.h"
#include <DirectXMath.h>

inline DirectX::XMFLOAT3 XM_CALLCONV modern_xfloat3_multiply(
	const struct XMFLOAT3& Float3,
	const float x
);

inline DirectX::XMFLOAT3 XM_CALLCONV modern_xfloat3_sum(
	const struct XMFLOAT3& A,
	const struct XMFLOAT3& B
);

inline DirectX::XMFLOAT3 XM_CALLCONV modern_xfloat3_sub(
	const struct XMFLOAT3& A,
	const struct XMFLOAT3& B
);

inline float XM_CALLCONV modern_xfloat3_distance2(
	const struct XMFLOAT3& a,
	const struct XMFLOAT3& b
);

#include "modern_xmath.inl"