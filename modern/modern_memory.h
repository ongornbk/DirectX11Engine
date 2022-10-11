#pragma once
#include "modern_def.h"


/*
Copyright(C) < 02.06.2020 > ongornbk@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE  ongornbk@gmail.com BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the ongornbk@gmail.com shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization from the ongornk@gmail.com.

modern is a trademark of ongornbk@gmail.com.
*/

template <class _Out_ ReturnType, class _In_ Type>
inline ReturnType& memory_cast(const Type& obj)
{
	return *(ReturnType*)(obj);
}

template <class _Out_ ReturnType,class _In_ Type>
inline constexpr ReturnType enum_cast(const Type obj)
{
	return static_cast<ReturnType>(obj);
}

template <class _Out_ ReturnType, class _In_ Type>
inline ReturnType* mmalloc(const Type nitems)
{
	return (ReturnType*)malloc((nitems) * sizeof(ReturnType));
}

template <class _Out_ ReturnType, class _In_ Type>
inline ReturnType* mcalloc(const Type nitems)
{
	return (ReturnType*)calloc(nitems, sizeof(ReturnType));
}

template <class ReturnType, class A, class _In_ Type>
inline ReturnType* mrealloc(A& ptr, const Type nitems)
{
	return (ReturnType*)realloc(ptr, (nitems) * sizeof(ReturnType));
}

template <class A>
inline void mfree(A& ptr)
{
	return free(ptr);
}

#define modern_offset_of(s,m) ((size_t)&reinterpret_cast<char const volatile&>((((s*)0)->m)))
#define modern_get_parent(parent,member_name,addr_of_member) (parent* const)(((size_t)addr_of_member) - (size_t)modern_offset_of(parent, member_name))
