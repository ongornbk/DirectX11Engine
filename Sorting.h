#pragma once
#include "RenderContainer.h"

namespace
{
	int8_t yp{};
	int8_t xp{};

	static bool xta[16]{};
	static bool yta[16]{};
}

struct __sort__SortByY {
	bool operator()(RenderContainer* a, RenderContainer* b) const noexcept;
};

struct  __sort__SortByX
{
	bool operator()(RenderContainer *a, RenderContainer *b) const noexcept;
};

void _vectorcall SortByY(std::vector<RenderContainer*> vec[16], std::vector<RenderContainer*> vecG[16]) noexcept;

void _vectorcall SortByX(std::vector<RenderContainer*> vec[16], std::vector<RenderContainer*> vecG[16]) noexcept;