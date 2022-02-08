#pragma once
#include "modern_def.h"

/*
Copyright(C) < 02.06.2020 > ongornbk@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE  ongornbk@gmail.com BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the ongornbk@gmail.com shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization from the ongornk@gmail.com.

modern is a trademark of ongornbk@gmail.com.
*/

extern constexpr float modern_pi = 3.14159f;
extern constexpr float modern_phi = 1.61803f;
extern constexpr float modern_e = 2.71828f;
extern constexpr float modern_ragtodeg = 180.f / modern_pi;
extern constexpr float modern_degtorad = modern_pi / 180.f;

struct modern_float2
{
	float x;
	float y;

	modern_float2() = default;

	modern_float2(const modern_float2&) = default;
	modern_float2& operator=(const modern_float2&) = default;

	modern_float2(modern_float2&&) = default;
	modern_float2& operator=(modern_float2&&) = default;

	constexpr modern_float2(float _x, float _y) : x(_x), y(_y) {}
	explicit modern_float2(_In_reads_(2) const float* pArray) : x(pArray[0]), y(pArray[1]) {}
};

struct modern_float3
{
	float x;
	float y;
	float z;

	modern_float3() = default;

	modern_float3(const modern_float3&) = default;
	modern_float3& operator=(const modern_float3&) = default;

	modern_float3(modern_float3&&) = default;
	modern_float3& operator=(modern_float3&&) = default;

	constexpr modern_float3(float _x, float _y,float _z) : x(_x), y(_y), z(_z) {}
	explicit modern_float3(_In_reads_(3) const float* pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]) {}
};

struct modern_float4
{
	float x;
	float y;
	float z;
	float w;

	modern_float4() = default;

	modern_float4(const modern_float4&) = default;
	modern_float4& operator=(const modern_float4&) = default;

	modern_float4(modern_float4&&) = default;
	modern_float4& operator=(modern_float4&&) = default;

	constexpr modern_float4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
	explicit modern_float4(_In_reads_(4) const float* pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]), w(pArray[3]) {}
};

struct modern_point 
{ 
	union __declspec(intrin_type) __declspec(align(16))
	{
		float               f32[4];
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	}m_union;

	modern_point(const float _x, const float _y = 0.f, const float _z = 0.f, const float _w = 0.f)
	{
		m_union.x = _x;
		m_union.y = _y;
		m_union.z = _z;
		m_union.w = _w;
	}

	
};
template <class T> inline T modern_min(T a, T b);
template <class T> inline T modern_max(T a, T b);
template <class T> inline T modern_abs(T a);
template <class T> inline T modern_pow(T a,int32_t b);

inline const modern_Boolean modern_checkFloat32(const float f32) noexcept;

inline float modern_sin(float a);
inline float modern_cos(float a);
inline float modern_tan(float a);
inline float modern_asin(float a);
inline float modern_acos(float a);
inline float modern_atan(float a);
inline float modern_atan2(float a, float b);
inline float modern_angle_between_points2(modern_point& a, modern_point& b);
inline float modern_distance_between_points2(modern_point& a, modern_point& b);
inline modern_point modern_polar_projection2(modern_point& source, float distance, float angle);

inline int32_t modern_random(int32_t min, int32_t max);
inline uint32_t modern_random(uint32_t min, uint32_t max);
inline float modern_random(float min, float max);
inline float modern_random_direction_degrees();
inline float modern_random_percentage();
inline void  modern_seed(uint32_t seed);
inline uint32_t  modern_seed_malloc();
inline void modern_seed_malloc(uint32_t& seed);

template <class T>
T modern_sign(const T val)
{
	return (T(0) < val) - (val < T(0));
}

#include "modern_math.inl"