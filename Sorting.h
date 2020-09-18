#pragma once
#include "RenderContainer.h"
#include "modern/modern.h"
#include <forward_list>

namespace
{
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

struct __sort__StaticSortByY {
	bool operator()(class EObject* a, class EObject* b) const noexcept;
};

struct  __sort__StaticSortByX
{
	bool operator()(class EObject* a, class EObject* b) const noexcept;
};

_Use_decl_annotations_
void _vectorcall SortByYV(class modern_array<class EObject*> vec[2][32]) noexcept;

_Use_decl_annotations_
void _vectorcall QSortByYV(class modern_array<class EObject*> vec[2][32]) noexcept;

_Use_decl_annotations_
void _vectorcall SortByXV(class modern_array<class EObject*> vec[2][32]) noexcept;

_Use_decl_annotations_
void _vectorcall QSortByXV(class modern_array<class EObject*> vec[2][32]) noexcept;

//_Use_decl_annotations_
//void _vectorcall StaticSortByYV(class Vector<class EObject*> _Inout_updates_all_(64) vec[2][32]) noexcept;
//
//_Use_decl_annotations_
//void _vectorcall StaticQSortByYV(class Vector<class EObject*> _Inout_updates_all_(64) vec[2][32]) noexcept;
//
//_Use_decl_annotations_
//void _vectorcall StaticSortByXV(class Vector<class EObject*> _Inout_updates_all_(64) vec[2][32]) noexcept;
//
//_Use_decl_annotations_
//void _vectorcall StaticQSortByXV(class Vector<class EObject*> _Inout_updates_all_(64) vec[2][32]) noexcept;

	_Use_decl_annotations_
void _vectorcall __CleanUp(class modern_array<class EObject*>* const vec) noexcept;