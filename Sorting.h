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

_Use_decl_annotations_
void _vectorcall SortByYV(class Vector<class EObject*> _Inout_updates_all_(64) vec[2][32]) noexcept;

_Use_decl_annotations_
void _vectorcall QSortByYV(class Vector<class EObject*> _Inout_updates_all_(64) vec[2][32]) noexcept;

_Use_decl_annotations_
void _vectorcall SortByXV(class Vector<class EObject*> _Inout_updates_all_(64) vec[2][32]) noexcept;

_Use_decl_annotations_
void _vectorcall QSortByXV(class Vector<class EObject*> _Inout_updates_all_(64) vec[2][32]) noexcept;

	_Use_decl_annotations_
void _vectorcall __CleanUp(class Vector<class EObject*> _Inout_updates_all_(64) vec[2][32]) noexcept;