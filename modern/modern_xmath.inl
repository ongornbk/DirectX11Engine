#include "modern_xmath.h"

inline DirectX::XMFLOAT3 XM_CALLCONV modern_xfloat3_multiply(
	const struct DirectX::XMFLOAT3& Float3,
	const float x
)
{
	return DirectX::XMFLOAT3(Float3.x * x, Float3.y * x, Float3.z * x);
}

inline DirectX::XMFLOAT3 XM_CALLCONV modern_xfloat3_div(
	const struct DirectX::XMFLOAT3& Float3, const float x)
{
	return DirectX::XMFLOAT3(Float3.x / x, Float3.y / x, Float3.z / x);
}

inline DirectX::XMFLOAT3 XM_CALLCONV modern_xfloat3_sum(
	const struct DirectX::XMFLOAT3& A,
	const struct DirectX::XMFLOAT3& B
)
{
	return DirectX::XMFLOAT3(A.x + B.x, A.y + B.y, A.z + B.z);
}



inline DirectX::XMFLOAT3 XM_CALLCONV modern_xfloat3_sub(
	const struct DirectX::XMFLOAT3& A,
	const struct DirectX::XMFLOAT3& B
)
{
	return DirectX::XMFLOAT3(A.x - B.x, A.y - B.y, A.z - B.z);
}

inline float XM_CALLCONV modern_xfloat3_distance2(
	const struct DirectX::XMFLOAT3& a,
	const struct DirectX::XMFLOAT3& b
)
{
	const DirectX::XMFLOAT2 f = { (a.x - b.x),(a.y - b.y) };
	return sqrtf((f.x * f.x) + (f.y * f.y));
}

inline float XM_CALLCONV modern_xfloat3_distance2(
	const struct DirectX::XMFLOAT3& tip,
	const struct DirectX::XMFLOAT3& baseA,
	const struct DirectX::XMFLOAT3& baseB
)
{
	const DirectX::XMFLOAT3 di = {
	modern_xfloat3_distance2(baseA, tip) ,
	modern_xfloat3_distance2(baseB, tip) ,
	modern_xfloat3_distance2(baseA, baseB)
	};

	const float pl = (di.x + di.y + di.z) / 2.f;

	return 2.f * sqrtf((pl - di.x) * (pl - di.y) * (pl - di.z)) / di.z;
}

inline float XM_CALLCONV modern_xangle2_between_points3(
	const struct DirectX::XMFLOAT3& A,
	const struct DirectX::XMFLOAT3& B
)
{
	return modern_ragtodeg * atan2f(A.x - B.x, A.y - B.y);
}

inline void XM_CALLCONV modern_xfloat3_rotate_deg(DirectX::XMFLOAT3& A, const float deg)
{
	A.x = A.x * cosf(modern_degtorad * deg) - A.y * sinf(modern_degtorad * deg);
	A.y = A.x * sinf(modern_degtorad * deg) + A.y * cosf(modern_degtorad * deg);
}
