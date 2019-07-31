#pragma once
#include "RenderContainer.h"
#include "Vector.h"
#include <forward_list>

namespace
{
	 int32 yp{};
	 int32 xp{};

	static int32 xta[32]{};
	static int32 yta[32]{};
}




struct __sort__SortByY {
	bool operator()(class EObject* a,class EObject* b) const noexcept;
};

struct  __sort__SortByX
{
	bool operator()(class EObject *a,class EObject *b) const noexcept;
};

void _vectorcall SortByYV(class Vector<EObject*> vec[2][32]) noexcept;
void _vectorcall SortByXV(class Vector<EObject*> vec[2][32]) noexcept;

void _vectorcall __CleanUp(class Vector<EObject*> vec[2][32]) noexcept;