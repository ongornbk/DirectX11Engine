#pragma once
#include "modern_math.h"
#include <DirectXMath.h>

inline DirectX::XMFLOAT3 XM_CALLCONV modern_xfloat3_multiply(
	const struct XMFLOAT3& Float3,
	const float x
);

inline DirectX::XMFLOAT3 XM_CALLCONV modern_xfloat3_div(
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

inline float XM_CALLCONV modern_xfloat3_distance2(
	const DirectX::XMVECTOR& aV,
	const struct DirectX::XMFLOAT3& b
);

inline float XM_CALLCONV modern_xfloat3_distance2(
	const struct XMFLOAT3& tip,
	const struct XMFLOAT3& baseA,
	const struct XMFLOAT3& baseB
);

inline float XM_CALLCONV modern_xangle2_between_points3(
	const struct XMFLOAT3& A,
	const struct XMFLOAT3& B
);

inline void XM_CALLCONV modern_xfloat3_rotate_deg(
	struct DirectX::XMFLOAT3& A,
	const float deg
);

inline struct DirectX::XMMATRIX XM_CALLCONV modern_xmatrix_translation_and_size(
	const float OffsetX,
	const float OffsetY,
	const float OffsetZ,
	const float sizeW
);

inline DirectX::XMFLOAT3 XM_CALLCONV modern_xpolar_projection2(DirectX::XMFLOAT3& source,const float distance,const float angle);

#include "modern_xmath.inl"