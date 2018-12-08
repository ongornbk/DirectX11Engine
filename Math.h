#pragma once

using DirectX::XMFLOAT3;

inline XMFLOAT3 XM_CALLCONV XMFloat3Multiply (XMFLOAT3 Float3, float x);

inline XMFLOAT3 XM_CALLCONV XMFloat3Sum(XMFLOAT3 A, XMFLOAT3 B);

inline XMFLOAT3 XM_CALLCONV XMFloat3Sub(XMFLOAT3 A, XMFLOAT3 B);

inline float XM_CALLCONV XMFloat3Distance2D(XMFLOAT3 a, XMFLOAT3 b);

#include "Math.inl"