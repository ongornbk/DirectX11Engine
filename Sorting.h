#pragma once
#include "RenderContainer.h"
#include "Vector.h"
#include <forward_list>

namespace
{
	int8_t yp{};
	int8_t xp{};

	static bool xta[32]{};
	static bool yta[32]{};
}


struct __sort__SortByY {
	bool operator()(RenderContainer* a, RenderContainer* b) const noexcept;
};

struct  __sort__SortByX
{
	bool operator()(RenderContainer *a, RenderContainer *b) const noexcept;
};

void _vectorcall SortByYV(Vector<RenderContainer*> vec[2][32]) noexcept;
void _vectorcall SortByXV(Vector<RenderContainer*> vec[2][32]) noexcept;