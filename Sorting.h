#pragma once
#include "RenderContainer.h"

struct __sort__SortByY {
	bool operator()(RenderContainer* a, RenderContainer* b) const noexcept;
};

struct  __sort__SortByX
{
	bool operator()(RenderContainer *a, RenderContainer *b) const noexcept;
};

void _vectorcall SortByY(std::vector<RenderContainer*> vec[4], std::vector<RenderContainer*> vecG[4]) noexcept;

void _vectorcall SortByX(std::vector<RenderContainer*> vec[4], std::vector<RenderContainer*> vecG[4]) noexcept;