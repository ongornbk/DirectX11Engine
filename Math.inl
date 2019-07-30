#pragma once
#include <DirectXMath.h>

using DirectX::XMFLOAT3;

inline XMFLOAT3 XM_CALLCONV XMFloat3Multiply(
	const struct XMFLOAT3& Float3,
	const float x
)
{
	return XMFLOAT3(Float3.x * x, Float3.y * x, Float3.z * x);
}

inline XMFLOAT3 XM_CALLCONV XMFloat3Sum(
	const struct XMFLOAT3& A,
	const struct XMFLOAT3& B
)
{
	return XMFLOAT3(A.x + B.x, A.y + B.y, A.z + B.z);
}

inline XMFLOAT3 XM_CALLCONV XMFloat3SumX(
	const struct XMFLOAT3& A,
	const float x
)
{
	return XMFLOAT3(A.x + x, A.y, A.z);
}

inline XMFLOAT3 XM_CALLCONV XMFloat3Sub(
	const struct XMFLOAT3& A,
	const struct XMFLOAT3& B
)
{
	return XMFLOAT3(A.x - B.x, A.y - B.y, A.z - B.z);
}

inline XMFLOAT3 XM_CALLCONV XMFloat3SubX(
	const struct XMFLOAT3& A,
	const float x
)
{
	return XMFLOAT3(A.x - x, A.y, A.z);
}

inline float XM_CALLCONV XMFloat3Distance2D(
	const struct XMFLOAT3& a,
	const struct XMFLOAT3& b
)
{
	float f[2] = { (a.x - b.x),(a.y - b.y) };
	return (float)(sqrt((f[0] * f[0]) + (f[1] * f[1])));
}
