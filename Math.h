#pragma once

namespace Math
{
	constexpr double     PI_extended = 3.14159265358979323844;
	constexpr float      PI = 3.14159f;
	constexpr float      SQRT2 = 1.41421f;
	constexpr float      E = 2.71828f;
}

using DirectX::XMFLOAT3;

inline XMFLOAT3 XM_CALLCONV XMFloat3Multiply (
	const struct XMFLOAT3& Float3,
	const float x
);

inline XMFLOAT3 XM_CALLCONV XMFloat3Sum(
	const struct XMFLOAT3& A,
	const struct XMFLOAT3& B
);

inline XMFLOAT3 XM_CALLCONV XMFloat3Sub(
	const struct XMFLOAT3& A,
	const struct XMFLOAT3& B
);

inline float XM_CALLCONV XMFloat3Distance2D(
	const struct XMFLOAT3& a,
	const struct XMFLOAT3& b
);

#include "Math.inl"