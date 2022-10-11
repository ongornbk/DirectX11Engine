#pragma once
#include "GameObject.h"
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
	bool _cdecl operator()( class GameObject* const a,  class GameObject* const b) const modern_except_state;
};

struct  __sort__SortByX
{
	bool _cdecl operator()( class GameObject *const a, class GameObject * const b) const modern_except_state;
};

struct __sort__StaticSortByY {
	bool _cdecl operator()(class GameObject* a, class GameObject* b) const modern_except_state;
};

struct  __sort__StaticSortByX
{
	bool _cdecl operator()(class GameObject* a, class GameObject* b) const modern_except_state;
};

_Use_decl_annotations_
void _vectorcall SortByYV(class modern_array<class GameObject*> vec[2][MAP_DIVISION]) modern_except_state;

_Use_decl_annotations_
void _vectorcall QSortByYV(class modern_array<class GameObject*> vec[2][MAP_DIVISION]) modern_except_state;

_Use_decl_annotations_
void _vectorcall SortByXV(class modern_array<class GameObject*> vec[2][MAP_DIVISION]) modern_except_state;

_Use_decl_annotations_
void _vectorcall QSortByXV(class modern_array<class GameObject*> vec[2][MAP_DIVISION]) modern_except_state;

_Use_decl_annotations_
void _cdecl PostSort() modern_except_state;

_Use_decl_annotations_
void _cdecl PushPair(class GameObject* const a, class GameObject* const b) modern_except_state;

//_Use_decl_annotations_
//void _vectorcall StaticSortByYV(class Vector<class GameObject*> _Inout_updates_all_(64) vec[2][32]) modern_except_state;
//
//_Use_decl_annotations_
//void _vectorcall StaticQSortByYV(class Vector<class GameObject*> _Inout_updates_all_(64) vec[2][32]) modern_except_state;
//
//_Use_decl_annotations_
//void _vectorcall StaticSortByXV(class Vector<class GameObject*> _Inout_updates_all_(64) vec[2][32]) modern_except_state;
//
//_Use_decl_annotations_
//void _vectorcall StaticQSortByXV(class Vector<class GameObject*> _Inout_updates_all_(64) vec[2][32]) modern_except_state;

	_Use_decl_annotations_
void _vectorcall __CleanUp(class modern_array<class GameObject*>* const vec) modern_except_state;