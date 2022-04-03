#pragma once
#include <emmintrin.h>
#include <xmmintrin.h>
#include <smmintrin.h>

struct modern_bpair
{
	struct
	{
		__unaligned volatile void* first;
		__unaligned volatile void* second;
	};
	

	modern_bpair(void* __A, void* __B) : first(__A),second(__B)
	{

	}

int operator ==(const modern_bpair& other) const
{
	return (_mm_testc_si128(_mm_load_si128(reinterpret_cast<const __m128i*>(this)), _mm_load_si128(reinterpret_cast<const __m128i*>(&other)))) == 1;
}
};

