#pragma once
#include <DirectXMath.h>

using DirectX::XMFLOAT3;

inline XMFLOAT3 XM_CALLCONV XMFloat3Multiply(XMFLOAT3 Float3,const float x)
{
	return XMFLOAT3(Float3.x * x, Float3.y * x, Float3.z * x);
}

inline XMFLOAT3 XM_CALLCONV XMFloat3Sum(XMFLOAT3 A, XMFLOAT3 B)
{
	return XMFLOAT3(A.x + B.x, A.y + B.y, A.z + B.z);
}

inline XMFLOAT3 XM_CALLCONV XMFloat3SumX(XMFLOAT3 A,float x)
{
	return XMFLOAT3(A.x + x, A.y, A.z);
}

inline XMFLOAT3 XM_CALLCONV XMFloat3Sub(XMFLOAT3 A, XMFLOAT3 B)
{
	return XMFLOAT3(A.x - B.x, A.y - B.y, A.z - B.z);
}

inline XMFLOAT3 XM_CALLCONV XMFloat3SubX(XMFLOAT3 A, float x)
{
	return XMFLOAT3(A.x - x, A.y, A.z);
}

inline float XM_CALLCONV XMFloat3Distance2D(XMFLOAT3 a, XMFLOAT3 b)
{
	float f[2] = { (a.x - b.x),(a.y - b.y) };
	return (float)(sqrt((f[0] * f[0]) + (f[1] * f[1])));
}
