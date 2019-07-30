#pragma once

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