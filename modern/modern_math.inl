#include "modern_math.h"
#include <cmath>
#pragma once

template <class T>
inline T modern_min(T a, T b)
{
	if (a < b)
		return a;
	return b;
}

template <class T>
inline T modern_max(T a, T b)
{
	if (a > b)
		return a;
	return b;
}

template <class T>
inline T modern_abs(T a)
{
	if (a >= 0)
		return a;
	return a*(-1);
}

template<class T>
inline T modern_ceil(T a)
{
	return std::ceil(a);
}

template<class T>
inline T modern_floor(T a)
{
	return std::floor(a);
}

template<class T>
inline T modern_round(T a)
{
	return std::round(a);
}

template<class T>

inline T modern_pow(T a,int32_t b)
{
		if (b == 0)
			return 1;
		else if ((b % 2) == 0)
			return modern_pow(a, b / 2) * modern_pow(a, b / 2);
		else
			return a * modern_pow(a, b / 2) * modern_pow(a, b / 2);
}

template<class T>
inline T modern_clamp(T value, T min, T max)
{
		if (value > max)
		{
			return max;
		}
		if (value < min)
		{
			return min;
		}
		return value;
}

template<class T>
inline T modern_clamp_reverse_div(T value, T min, T max)
{
	assert(max > 0);
	if (max - value >= max)
	{
		return max;
	}
	if ((max - value) <= min)
	{
		return min;
	}
	return (max-value) / max;
}

template<class T>
inline T modern_clamp_div(T value, T min, T max)
{
	assert(max > 0);
	if (value > max)
	{
		return max;
	}
	if (value < min)
	{
		return min;
	}
	return value / max;
}

inline int32_t modern_random(int32_t min, int32_t max)
{
	assert(max >= min);
	return min + (rand() % int32_t(max - min + 1));
}

inline uint32_t modern_random(uint32_t min, uint32_t max)
{
	assert(max > min);
	return min + (((uint32_t)rand()) % uint32_t(max - min + 1));
}

inline float modern_random(float min, float max)
{
	assert(max > min);
	return min + (rand() / (RAND_MAX / (max - min)));
}

inline float modern_random_direction_degrees()
{
	return modern_random(0.f, 360.f);
}

inline float modern_random_percentage()
{
	return modern_random(0.f, 100.f);
}

inline void modern_seed(uint32_t seed)
{
	srand(seed);
}

inline uint32_t modern_seed_malloc()
{
#pragma warning(disable : 4311)
#pragma warning(disable : 4302)
	void* addr = malloc(4);
	uint32_t seed = (uint32_t)(addr);
	free(addr);
	modern_seed(seed);
	return seed;
}

inline void modern_seed_malloc(uint32_t& seed)
{
#pragma warning(disable : 4311)
#pragma warning(disable : 4302)
	void* addr = malloc(4);
	seed = (uint32_t)(addr);
	free(addr);
	modern_seed(seed);
}

inline const modern_Boolean modern_checkFloat32(const float f32) noexcept
{
	return  !(isnormal(f32) || isnan(f32));
}

inline float modern_sin(float a)
{
	return sinf(a * modern_degtorad);
}

inline float modern_cos(float a)
{
	return cosf(a * modern_degtorad);
}

inline float modern_tan(float a)
{
	return tanf(a * modern_degtorad);
}

inline float modern_asin(float a)
{
	return asinf(a) * modern_ragtodeg;
}

inline float modern_acos(float a)
{
	return acosf(a) * modern_ragtodeg;
}

inline float modern_atan(float a)
{
	return atanf(a) * modern_ragtodeg;
}

inline float modern_atan2(float a, float b)
{
	return atan2f(a, b) * modern_ragtodeg;
}

inline float modern_angle_between_points2(modern_point& a, modern_point& b)
{
	return modern_ragtodeg * atan2f(a.m_union.x - b.m_union.x, a.m_union.y - b.m_union.y);
}

inline float modern_radians_between_points2(modern_point& a, modern_point& b)
{
	return atan2f(a.m_union.x - b.m_union.x, a.m_union.y - b.m_union.y);
}

inline float modern_distance_between_points2(modern_point& a, modern_point& b)
{
	float dx = a.m_union.x - b.m_union.x;
	float dy = a.m_union.y - b.m_union.y;
	return sqrtf((dx * dx) + (dy * dy));
}

inline modern_point modern_polar_projection2(modern_point& source, float distance, float angle)
{
	float x = source.m_union.x + (distance * cosf(angle * modern_degtorad));
	float y = source.m_union.y + (distance * sinf(angle * modern_degtorad));
	return modern_point(x, y);
}
