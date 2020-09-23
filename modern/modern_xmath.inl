#include "modern_xmath.h"

inline DirectX::XMFLOAT3 XM_CALLCONV modern_xfloat3_multiply(
	const struct DirectX::XMFLOAT3& Float3,
	const float x
)
{
	return DirectX::XMFLOAT3(Float3.x * x, Float3.y * x, Float3.z * x);
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
	float f[2] = { (a.x - b.x),(a.y - b.y) };
	return (float)(sqrt((f[0] * f[0]) + (f[1] * f[1])));
}

inline float XM_CALLCONV modern_xangle2_between_points3(
	const struct DirectX::XMFLOAT3& A,
	const struct DirectX::XMFLOAT3& B
)
{
	return modern_ragtodeg * atan2f(A.x - B.x, A.y - B.y);
}
