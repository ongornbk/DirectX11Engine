#pragma once
#include <sal.h>
#include <cstdint>

struct lua64int
{
	explicit lua64int(const _In_ int32_t f, const int32_t s) : first(f), second(s) {}

	int32_t first;
	int32_t second;
};

union LuaPointer
{
	LuaPointer(void* _In_ v)
	{
		ptr = v;
	}
	LuaPointer(int32_t _In_ first, int32_t _In_ second)
	{
		lua = lua64int(first, second);
	}
	LuaPointer(uint64_t _In_ i)
	{
		value = i;
	}
	LuaPointer(lua64int _In_ l)
	{
		lua = l;
	}
	/*__unaligned */ void* ptr;
	uint64_t          value;
	lua64int         lua;
};