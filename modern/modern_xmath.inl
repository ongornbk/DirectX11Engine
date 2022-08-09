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

inline float XM_CALLCONV modern_xfloat3_distance2(const DirectX::XMVECTOR& aV, const DirectX::XMFLOAT3& b)
{
	const DirectX::XMVECTOR bV = DirectX::XMLoadFloat3(&b);
	return DirectX::XMVector3Length(DirectX::XMVectorSubtract(aV,bV)).m128_f32[0];
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

inline DirectX::XMFLOAT3 XM_CALLCONV modern_xpolar_projection2(DirectX::XMFLOAT3& source, const float distance, const float angle)
{
	float x = source.x + (distance * cosf(angle * modern_degtorad));
	float y = source.y + (distance * sinf(angle * modern_degtorad));
	return DirectX::XMFLOAT3(x, y,source.z);
}

inline struct DirectX::XMMATRIX XM_CALLCONV modern_xmatrix_translation_and_size
(
	const float OffsetX,
	const float OffsetY,
	const float OffsetZ,
	const float sizeW
)
{
#if defined(_XM_NO_INTRINSICS_)

	XMMATRIX M;
	M.m[0][0] = 1.0f;
	M.m[0][1] = 0.0f;
	M.m[0][2] = 0.0f;
	M.m[0][3] = 0.0f;

	M.m[1][0] = 0.0f;
	M.m[1][1] = 1.0f;
	M.m[1][2] = 0.0f;
	M.m[1][3] = 0.0f;

	M.m[2][0] = 0.0f;
	M.m[2][1] = 0.0f;
	M.m[2][2] = 1.0f;
	M.m[2][3] = 0.0f;

	M.m[3][0] = OffsetX;
	M.m[3][1] = OffsetY;
	M.m[3][2] = OffsetZ;
	M.m[3][3] = sizeW;
	return M;

#elif defined(_XM_SSE_INTRINSICS_) || defined(_XM_ARM_NEON_INTRINSICS_)
	{
		struct DirectX::XMMATRIX M;
		M.r[0] = DirectX::g_XMIdentityR0.v;
		M.r[1] = DirectX::g_XMIdentityR1.v;
		M.r[2] = DirectX::g_XMIdentityR2.v;
		M.r[3] = DirectX::XMVectorSet(OffsetX * sizeW, OffsetY * sizeW, OffsetZ * sizeW, sizeW);
		return M;
	}
	
#endif
}