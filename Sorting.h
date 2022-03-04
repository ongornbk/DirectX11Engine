#pragma once
#include "RenderContainer.h"
#include "modern/modern.h"
#include "game_math.h"
#include "SortPair.h"
#include <forward_list>

namespace
{
	static int32 xta[MAP_DIVISION]{};
	static int32 yta[MAP_DIVISION]{};
}




struct __sort__SortByY {
	bool _cdecl operator()( class EObject* const a,  class EObject* const b) const noexcept;
};

struct  __sort__SortByX
{
	bool _cdecl operator()( class EObject *const a, class EObject * const b) const noexcept;
};

struct __sort__StaticSortByY {
	bool _cdecl operator()(class EObject* a, class EObject* b) const noexcept;
};

struct  __sort__StaticSortByX
{
	bool _cdecl operator()(class EObject* a, class EObject* b) const noexcept;
};

_Use_decl_annotations_
void _vectorcall SortByYV(class modern_array<class EObject*> vec[2][MAP_DIVISION]) noexcept;

_Use_decl_annotations_
void _vectorcall QSortByYV(class modern_array<class EObject*> vec[2][MAP_DIVISION]) noexcept;

_Use_decl_annotations_
void _vectorcall SortByXV(class modern_array<class EObject*> vec[2][MAP_DIVISION]) noexcept;

_Use_decl_annotations_
void _vectorcall QSortByXV(class modern_array<class EObject*> vec[2][MAP_DIVISION]) noexcept;

_Use_decl_annotations_
void _cdecl PostSort() noexcept;

_Use_decl_annotations_
void _cdecl PushPair(class EObject* const a, class EObject* const b) noexcept;

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