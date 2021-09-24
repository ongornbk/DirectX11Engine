#include "Sorting.h"
#include "Defines.h"
#include "Camera.h"
#include "Vector.h"
#include "ThreadPool.h"
#include "modern/modern_guard.h"
#include "modern/modern_shared_guard.h"
//#include "Math.h"
#include "Tile.h"
#include "game_math.h"
#include <sstream>
#include <sal.h>
#include <omp.h>
#include <DirectXMath.h>
#include <iostream>
#include <vector>

namespace
{


//DEPRECATED 25.05.2020 ongornbk
/*
	constexpr float MAP_XEND = HALF_MAP_SIZE * (80.0f  * Math::SQRT2);
	constexpr float MAP_XBEG = HALF_MAP_SIZE * (-80.0f * Math::SQRT2);
	constexpr float MAP_XENDd14 = HALF_MAP_SIZE * (20.0f  * Math::SQRT2);
	constexpr float MAP_XBEGd14 = HALF_MAP_SIZE * (-20.0f * Math::SQRT2);
	constexpr float MAP_XENDd2 = HALF_MAP_SIZE * (40.0f  * Math::SQRT2);
	constexpr float MAP_XBEGd2 = HALF_MAP_SIZE * (-40.0f * Math::SQRT2);
	constexpr float MAP_XENDd34 = HALF_MAP_SIZE * (60.0f  * Math::SQRT2);
	constexpr float MAP_XBEGd34 = HALF_MAP_SIZE * (-60.0f * Math::SQRT2);

	constexpr float MAP_XENDd78 = HALF_MAP_SIZE * (70.0f  * Math::SQRT2);
	constexpr float MAP_XBEGd78 = HALF_MAP_SIZE * (-70.0f * Math::SQRT2);
	constexpr float MAP_XENDd58 = HALF_MAP_SIZE * (50.0f  * Math::SQRT2);
	constexpr float MAP_XBEGd58 = HALF_MAP_SIZE * (-50.0f * Math::SQRT2);
	constexpr float MAP_XENDd38 = HALF_MAP_SIZE * (30.0f  * Math::SQRT2);
	constexpr float MAP_XBEGd38 = HALF_MAP_SIZE * (-30.0f * Math::SQRT2);
	constexpr float MAP_XENDd18 = HALF_MAP_SIZE * (10.0f  * Math::SQRT2);
	constexpr float MAP_XBEGd18 = HALF_MAP_SIZE * (-10.0f * Math::SQRT2);

	constexpr float MAP_XENDd1516 = HALF_MAP_SIZE * (75.0f  * Math::SQRT2);
	constexpr float MAP_XBEGd1516 = HALF_MAP_SIZE * (-75.0f * Math::SQRT2);
	constexpr float MAP_XENDd1316 = HALF_MAP_SIZE * (65.0f  * Math::SQRT2);
	constexpr float MAP_XBEGd1316 = HALF_MAP_SIZE * (-65.0f * Math::SQRT2);
	constexpr float MAP_XENDd1116 = HALF_MAP_SIZE * (55.0f  * Math::SQRT2);
	constexpr float MAP_XBEGd1116 = HALF_MAP_SIZE * (-55.0f * Math::SQRT2);
	constexpr float MAP_XENDd916 = HALF_MAP_SIZE * (45.0f  * Math::SQRT2);
	constexpr float MAP_XBEGd916 = HALF_MAP_SIZE * (-45.0f * Math::SQRT2);
	constexpr float MAP_XENDd716 = HALF_MAP_SIZE * (35.0f  * Math::SQRT2);
	constexpr float MAP_XBEGd716 = HALF_MAP_SIZE * (-35.0f * Math::SQRT2);
	constexpr float MAP_XENDd516 = HALF_MAP_SIZE * (25.0f  * Math::SQRT2);
	constexpr float MAP_XBEGd516 = HALF_MAP_SIZE * (-25.0f * Math::SQRT2);
	constexpr float MAP_XENDd316 = HALF_MAP_SIZE * (15.0f  * Math::SQRT2);
	constexpr float MAP_XBEGd316 = HALF_MAP_SIZE * (-15.0f * Math::SQRT2);
	constexpr float MAP_XENDd116 = HALF_MAP_SIZE * (5.0f  * Math::SQRT2);
	constexpr float MAP_XBEGd116 = HALF_MAP_SIZE * (-5.0f * Math::SQRT2);

	constexpr float MAP_YEND = HALF_MAP_SIZE * (40.0f  * Math::SQRT2);
	constexpr float MAP_YBEG = HALF_MAP_SIZE * (-40.0f * Math::SQRT2);
	constexpr float MAP_YENDd2 = HALF_MAP_SIZE * (20.0f  * Math::SQRT2);
	constexpr float MAP_YBEGd2 = HALF_MAP_SIZE * (-20.0f * Math::SQRT2);
	constexpr float MAP_YENDd34 = HALF_MAP_SIZE * (30.0f  * Math::SQRT2);
	constexpr float MAP_YBEGd34 = HALF_MAP_SIZE * (-30.0f * Math::SQRT2);
	constexpr float MAP_YENDd14 = HALF_MAP_SIZE * (10.0f  * Math::SQRT2);
	constexpr float MAP_YBEGd14 = HALF_MAP_SIZE * (-10.0f * Math::SQRT2);

	constexpr float MAP_YENDd78 = HALF_MAP_SIZE * (35.0f  * Math::SQRT2);
	constexpr float MAP_YBEGd78 = HALF_MAP_SIZE * (-35.0f * Math::SQRT2);
	constexpr float MAP_YENDd58 = HALF_MAP_SIZE * (25.0f  * Math::SQRT2);
	constexpr float MAP_YBEGd58 = HALF_MAP_SIZE * (-25.0f * Math::SQRT2);
	constexpr float MAP_YENDd38 = HALF_MAP_SIZE * (15.0f  * Math::SQRT2);
	constexpr float MAP_YBEGd38 = HALF_MAP_SIZE * (-15.0f * Math::SQRT2);
	constexpr float MAP_YENDd18 = HALF_MAP_SIZE * (5.0f   * Math::SQRT2);
	constexpr float MAP_YBEGd18 = HALF_MAP_SIZE * (-5.0f  * Math::SQRT2);

	constexpr float MAP_YENDd1516 = HALF_MAP_SIZE * (37.5f  * Math::SQRT2);
	constexpr float MAP_YBEGd1516 = HALF_MAP_SIZE * (-37.5f * Math::SQRT2);
	constexpr float MAP_YENDd1316 = HALF_MAP_SIZE * (32.5f  * Math::SQRT2);
	constexpr float MAP_YBEGd1316 = HALF_MAP_SIZE * (-32.5f * Math::SQRT2);
	constexpr float MAP_YENDd1116 = HALF_MAP_SIZE * (27.5f  * Math::SQRT2);
	constexpr float MAP_YBEGd1116 = HALF_MAP_SIZE * (-27.5f * Math::SQRT2);
	constexpr float MAP_YENDd916 = HALF_MAP_SIZE * (22.5f   * Math::SQRT2);
	constexpr float MAP_YBEGd916 = HALF_MAP_SIZE * (-22.5f  * Math::SQRT2);
	constexpr float MAP_YENDd716 = HALF_MAP_SIZE * (17.5f  * Math::SQRT2);
	constexpr float MAP_YBEGd716 = HALF_MAP_SIZE * (-17.5f * Math::SQRT2);
	constexpr float MAP_YENDd516 = HALF_MAP_SIZE * (12.5f  * Math::SQRT2);
	constexpr float MAP_YBEGd516 = HALF_MAP_SIZE * (-12.5f * Math::SQRT2);
	constexpr float MAP_YENDd316 = HALF_MAP_SIZE * (7.5f  * Math::SQRT2);
	constexpr float MAP_YBEGd316 = HALF_MAP_SIZE * (-7.5f * Math::SQRT2);
	constexpr float MAP_YENDd116 = HALF_MAP_SIZE * (2.5f   * Math::SQRT2);
	constexpr float MAP_YBEGd116 = HALF_MAP_SIZE * (-2.5f  * Math::SQRT2);

	*/
	
}

//DEPRECATED 24.05.2020 ongornbk
/*
_Use_decl_annotations_
 __forceinline constexpr int32 _Out_ _stdcall GetXCell(const _In_ float x) noexcept
{

	if (x < 0.0f)
	{
		if (x < MAP_XBEGd2)
		{
			if (x < MAP_XBEGd34)
			{
				if (x < MAP_XBEGd78)
				{
					if (x < MAP_XBEGd1516)
					{
						return 0;
					}
					else
					{
						return 1;
					}
					
				}
				if (x < MAP_XBEGd1316)
				{
					return 2;
				}
				else
				{
					return 3;
				}
			}
			else
			{
				if (x < MAP_XBEGd58)
				{
					if (x < MAP_XBEGd1116)
					{
						return 4;
					}
					else
					{
						return 5;
					}
				}
				else
				{
					if (x < MAP_XBEGd916)
					{
						return 6;
					}
					else
					{
						return 7;
					}
				}
			}
		}
		else
		{
			if (x < MAP_XBEGd14)
			{
				if (x < MAP_XBEGd38)
				{
					if (x < MAP_XBEGd716)
					{
						return 8;
					}
					else
					{
						return 9;
					}
				}
				else
				{
					if (x < MAP_XBEGd516)
					{
						return 10;
					}
					else
					{
						return 11;
					}
				}
			}
			else
			{
				if (x < MAP_XBEGd18)
				{
					if (x < MAP_XBEGd316)
					{
						return 12;
					}
					else
					{
						return 13;
					}
				}
				else
				{
					if (x < MAP_XBEGd116)
					{
						return 14;
					}
					else
					{
						return 15;
					}
				}
			}
		}
	}
	else
	{
		if (x < MAP_XENDd2)
		{
			if (x < MAP_XENDd14)
			{
				if (x < MAP_XENDd18)
				{
					if (x < MAP_XENDd116)
					{
						return 16;
					}
					else
					{
						return 17;
					}
				}
				else
				{
					if (x < MAP_XENDd316)
					{
						return 18;
					}
					else
					{
						return 19;
					}
				}
			}
			else
			{
				if (x < MAP_XENDd38)
				{
					if (x < MAP_XENDd516)
					{
						return 20;
					}
					else
					{
						return 21;
					}
				}
				else
				{
					if (x < MAP_XENDd716)
					{
						return 22;
					}
					else
					{
						return 23;
					}
				}
			}
		}
		else
		{
			if (x < MAP_XENDd34)
			{
				if (x < MAP_XENDd58)
				{
					if (x < MAP_XENDd916)
					{
						return 24;
					}
					else
					{
						return 25;
					}
				}
				else
				{
					if (x < MAP_XENDd1116)
					{
						return 26;
					}
					else
					{
						return 27;
					}
				}
			}
			else
			{
				if (x < MAP_XENDd78)
				{
					if (x < MAP_XENDd1316)
					{
						return 28;
					}
					else
					{
						return 29;
					}
				}
				else
				{
					if (x < MAP_XENDd1516)
					{
						return 30;
					}
					else
					{
						return 31;
					}
				}
			}
		}
	}
}

_Use_decl_annotations_
__forceinline constexpr int32 _Out_ _stdcall GetYCell(const _In_ float y) noexcept
{
	if (y < 0.0f)
	{
		if (y < MAP_YBEGd2)
		{
			if (y < MAP_YBEGd34)
			{
				if (y < MAP_YBEGd78)
				{
					
					if (y < MAP_YBEGd1516)
					{
						return 0;
					}
					else
					{
						return 1;
					}
				}
				else
				{
					if (y < MAP_YBEGd1316)
					{
						return 2;
					}
					else
					{
						return 3;
					}
				}
			}
			else
			{
				if (y < MAP_YBEGd58)
				{
					if (y < MAP_YBEGd1116)
					{
						return 4;
					}
					else
					{
						return 5;
					}
				}
				else
				{
					return 3;
				}
			}
		}
		else
		{
			if (y < MAP_YBEGd14)
			{
				if (y < MAP_YBEGd38)
				{
					return 4;
				}
				else
				{
					return 5;
				}
			}
			else
			{
				if (y < MAP_YBEGd18)
				{
					return 6;
				}
				else
				{
					return 7;
				}
			}
		}
	}
	else
	{
		if (y < MAP_YENDd2)
		{
			if (y < MAP_YENDd14)
			{
				if (y < MAP_YENDd18)
				{
					return 8;
				}
				else
				{
					return 9;
				}
			}
			else
			{
				if (y < MAP_YENDd38)
				{
					return 10;
				}
				else
				{
					return 11;
				}
				
			}
		}
		else
		{
			if (y < MAP_YENDd34)
			{
				if (y < MAP_YENDd58)
				{
					return 12;
				}
				else
				{
					return 13;
				}
			}
			else
			{
				if (y < MAP_YENDd78)
				{
					return 14;
				}
				else
				{
					return 15;
				}
			}
		}

	}
}
*/ 





_Use_decl_annotations_
template <class T>
__forceinline constexpr int32 _Out_ _stdcall __validate_Xrendering__(const T& _In_ index, const int32 xp) noexcept
{
	const int32 t0 = xp - index;
	if (t0 <= (RENDER_CELLS_RANGE) && t0 >= (-RENDER_CELLS_RANGE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

_Use_decl_annotations_
template <class T>
__forceinline constexpr int32 _Out_ _stdcall __validate_Yrendering__(const T& _In_ index,const int32 yp) noexcept
{
	const int32 t0 = yp - index;
	if (t0 <= (RENDER_CELLS_RANGE) && t0 >= (-RENDER_CELLS_RANGE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

__forceinline void _stdcall __intersect_test__(int32& xp,int32& yp) noexcept
{
	float cameraPosition[4];
	_mm_store_ps(cameraPosition, Camera::GetCurrentCamera()->GetPosition());
	xp = GetXCell(cameraPosition[0]);
	yp = GetYCell(cameraPosition[1]);


for ( int32 i = 0u; i < MAP_DIVISION; i++)
{
	xta[i] = __validate_Xrendering__(i,xp);
	yta[i] = __validate_Yrendering__(i,yp);
}
}

bool _cdecl __sort__SortByY::operator()(class EObject * const A,class EObject * const B) const noexcept
{
	//IT FIXED SOME GLITCHES LIKE A MAGIC WAND 
	//try
	//{
		const volatile class modern_guard AG(A);
		const volatile class modern_guard BG(B);
	//}
	//catch (...)
	//{
	//	return true;
	//}

	const bool Apushable = A->m_flags.m_pushable;
	const bool Bpushable = B->m_flags.m_pushable;
	const float Aradius = A->m_boundingSphere.Radius;
	const float Bradius = B->m_boundingSphere.Radius;
	const float Ax = A->m_boundingSphere.Center.x;
	const float Ay = A->m_boundingSphere.Center.y;
	const float Bx = B->m_boundingSphere.Center.x;
	const float By = B->m_boundingSphere.Center.y;
	const float Sradius = Aradius + Bradius;
	const float Xdistance = Ax - Bx;
	const float Ydistance = Ay - By;
	const float Sdistance = XMVector2Length({Xdistance,Ydistance}).m128_f32[0];
	//const float Sdistance = sqrt((Xdistance*Xdistance) + (Ydistance*Ydistance));
//
	//if (A->m_boundingSphere.Intersects(B->m_boundingSphere))
//	{
	//	A->Intersect(B);
	//	B->Intersect(A);
//	}

	if (Sdistance < Sradius)
	{

		//A->Intersect(B);
		//B->Intersect(A);

		float Scollision = Sdistance - Sradius;
		if (Apushable == Bpushable)
		{
			if (A->collisionPriority == B->collisionPriority)
			{
				Scollision /= 2.0f;
				if (Ax < Bx)
				{
					A->m_boundingSphere.Center.x += Scollision;
					B->m_boundingSphere.Center.x -= Scollision;

				}
				else
				{
					A->m_boundingSphere.Center.x -= Scollision;
					B->m_boundingSphere.Center.x += Scollision;
				}
			}
			else if (A->collisionPriority < B->collisionPriority)
			{
				if (Ax < Bx) A->m_boundingSphere.Center.x += Scollision;
				else         A->m_boundingSphere.Center.x -= Scollision;
			}
			else
			{
				if (Ax < Bx) B->m_boundingSphere.Center.x -= Scollision;
				else         B->m_boundingSphere.Center.x += Scollision;
			}
		}
		else
		{
			if (Apushable)
			{
			if (Ax < Bx) A->m_boundingSphere.Center.x += Scollision;
			else         A->m_boundingSphere.Center.x -= Scollision;
			}
			else
			{
			if (Ax < Bx) B->m_boundingSphere.Center.x -= Scollision;
			else         B->m_boundingSphere.Center.x += Scollision;
			}
		}
	}
	return Ay > By;
}

bool _cdecl __sort__SortByX::operator()(class EObject * const A,class EObject * const B) const noexcept
{

	const class modern_guard AG(A);
	const class modern_guard BG(B);

	const bool Apushable = A->m_flags.m_pushable;
	const bool Bpushable = B->m_flags.m_pushable;
	const float Aradius = A->m_boundingSphere.Radius;
	const float Bradius = B->m_boundingSphere.Radius;
	const float Ax = A->m_boundingSphere.Center.x;
	const float Ay = A->m_boundingSphere.Center.y;
	const float Bx = B->m_boundingSphere.Center.x;
	const float By = B->m_boundingSphere.Center.y;
	const float Sradius = Aradius + Bradius;
	const float Xdistance = Ax - Bx;
	const float Ydistance = Ay - By;
	const float Sdistance = XMVector2Length({ Xdistance,Ydistance }).m128_f32[0];

	//if (A->m_boundingSphere.Intersects(B->m_boundingSphere))
	//{
	//	A->Intersect(B);
	//	B->Intersect(A);
	//}

	if (Sdistance < Sradius)
	{

		float Scollision = Sdistance - Sradius;
		if (Apushable == Bpushable)
		{
			if (A->collisionPriority == B->collisionPriority)
			{
				Scollision /= 2.0f;
				if (Ay < By)
				{
					A->m_boundingSphere.Center.y += Scollision;
					B->m_boundingSphere.Center.y -= Scollision;
				}
				else
				{
					A->m_boundingSphere.Center.y -= Scollision;
					B->m_boundingSphere.Center.y += Scollision;
				}
			}
			else if (A->collisionPriority < B->collisionPriority)
			{
				if (Ay < By) A->m_boundingSphere.Center.y += Scollision;
				else         A->m_boundingSphere.Center.y -= Scollision;
			}
			else
			{
				if (Ay < By) B->m_boundingSphere.Center.y -= Scollision;
				else         B->m_boundingSphere.Center.y += Scollision;
			}
		}
		else
		{
			if (Apushable)
			{
				if (Ay < By) A->m_boundingSphere.Center.y += Scollision;
				else         A->m_boundingSphere.Center.y -= Scollision;
			}
			else
			{
				if (Ay < By) B->m_boundingSphere.Center.y -= Scollision;
				else         B->m_boundingSphere.Center.y += Scollision;
			}
		}
		A->Intersect(B);
		B->Intersect(A);
			//CRITICAL
		return 	A->m_boundingSphere.Center.x > B->m_boundingSphere.Center.x;
	}

	return Ax > Bx;
}

bool _cdecl __sort__StaticSortByY::operator()(class EObject* const A, class EObject* const B) const noexcept
{
	if (A && B)
	{
		A->Intersect(B);
		B->Intersect(A);
	}
	else return false;
}

bool _cdecl __sort__StaticSortByX::operator()(class EObject* const A, class EObject* const B) const noexcept
{
	if (A && B)
	{
		A->Intersect(B);
		B->Intersect(A);
		return (A->m_boundingSphere.Center.x) > (B->m_boundingSphere.Center.x);
	}
	else return false;
}


void sortPxVTP(class modern_array<class EObject*>& vector) noexcept
{
	_Sort_unchecked(vector.begin(), vector.end(),vector.size(), __sort__SortByX());
	//std::sort(vector.begin(), vector.end(), __sort__SortByX());
}


void sortPyVTP(class modern_array<class EObject*>& vector) noexcept
{
	_Sort_unchecked(vector.begin(), vector.end(), vector.size(), __sort__SortByY());
	//std::sort(vector.begin(), vector.end(), __sort__SortByY());
}

void _stdcall _static_sortPxVTP(class EObject** _In_ const begin, class EObject** _In_ const end) noexcept
{
	_Sort_unchecked(begin, end, end - begin, __sort__StaticSortByX());
}

void _stdcall _static_sortPyVTP(class EObject** _In_ const begin, class EObject** _In_ const end) noexcept
{
	_Sort_unchecked(begin, end, end - begin, __sort__StaticSortByY());
}

void _vectorcall SortByYV(class modern_array<class EObject*> vec[2][MAP_DIVISION]) noexcept
{
	//for (int32 i = 0; i < 32; ++i)
	//	vec[1][i].clear();
	//
	//for (int32 i = 0; i < 32; ++i)
	//{
	//	for (auto && object : vec[0][i])
	//	{
	//		vec[1][GetYCell(object->m_boundingSphere.Center.y)].push_back(object);
	//	}
	//}
//#pragma omp single
	{
		for (int32 i = 0; i < MAP_DIVISION; ++i)
			vec[1][i].clear();

		//#pragma omp pallalel for shedule(dynamic)


	//	{
		for (int32 i = 0; i < MAP_DIVISION; ++i)
		{
			for (auto object : vec[0][i])
			{
				vec[1][GetYCell(object->m_boundingSphere.Center.y)].push_back(object);
			}
		}
	}
		//struct ThreadPoolHandle pool;

		//for (int32 i = 0; i < 32; ++i)
		//{
		//	if (yta[i])
		//	{
		//		pool<<([vec, i]() { sortPyVTP(vec[1][i].begin(), vec[1][i].end()); });
		//	}
		//}
//#pragma omp for schedule(dynamic)
//		for (int32 i = 0; i < 32; ++i)
//		{
//			if (yta[i])
//			{
//				sortPyVTP(vec[1][i].begin(), vec[1][i].end());
//			}
//		
//	}
}

void _vectorcall QSortByYV(class modern_array<class EObject*> vec[2][MAP_DIVISION]) noexcept
{

//#pragma omp parallel
//#pragma omp for schedule(dynamic)
		for (int32 i = 0; i < MAP_DIVISION; ++i)
		{
			if (yta[i])
			{
				sortPyVTP(vec[1][i]);
			}

		}
//#pragma omp barrier
}

void _vectorcall SortByXV(class modern_array<class EObject*> vec[2][MAP_DIVISION]) noexcept
{
//#pragma omp single
	{
		int32 xp, yp;

		__intersect_test__(xp, yp);


		for (int32 i = 0; i < MAP_DIVISION; ++i)
		{
			vec[0][i].clear();
			//vec[1][i].shrink();
		}


		{
			for (int32 i = 0; i < MAP_DIVISION; ++i)
			{				for (auto RC : vec[1][i])
				{
					vec[0][GetXCell(RC->m_boundingSphere.Center.x)].push_back(RC);
				}
			}
		}
	}
		//struct ThreadPoolHandle pool;
		//
		//for (int32 i = 0; i < 32; i++)
		//{
		//	if (xta[i])
		//	{
		//		pool<<([vec,i]() { sortPxVTP(vec[0][i].begin(), vec[0][i].end()); });
		//	}
		//}

//
//#pragma omp for schedule(dynamic)
//		for (int32 i = 0; i < 32; i++)
//		{
//			if (xta[i])
//			{
//				sortPxVTP(vec[0][i].begin(), vec[0][i].end());
//			}
//		}

}

void _vectorcall QSortByXV(class modern_array<class EObject*> vec[2][MAP_DIVISION]) noexcept
{
//#pragma omp parallel
//#pragma omp for schedule(dynamic)
	for (int32 i = 0; i < MAP_DIVISION; ++i)
	{
		if (xta[i])
		{
			sortPxVTP(vec[0][i]);
		}
	}
//#pragma omp barrier
}

//BUGGED
/*
void _vectorcall StaticSortByYV(class Vector<class EObject*> vec[2][32]) noexcept
{
	for (int32 i = 0; i < 32; ++i)
		vec[1][i].clear();


		for (int32 i = 0; i < 32; ++i)
		{
			for (auto&& object : vec[0][i])
			{
				vec[1][GetYCell(object->m_boundingSphere.Center.y)].push_back(object);
			}
		}

}

void _vectorcall StaticQSortByYV(Vector<class EObject*> vec[2][32]) noexcept
{
	for (int32 i = 0; i < 32; ++i)
	{
		if (yta[i])
		{
			_static_sortPyVTP(vec[1][i].begin(), vec[1][i].end());
		}

	}
}

void _vectorcall StaticSortByXV(class Vector<class EObject*> vec[2][32]) noexcept
{
	__intersect_test__();

	for (int32_t i = 0; i < 32; i++)
	{
		vec[0][i].clear();
		vec[1][i].shrink();
	}

	{
		for (int32_t i = 0; i < 32; i++)
		{
			for (auto&& RC : vec[1][i])
			{
				vec[0][GetXCell(RC->m_boundingSphere.Center.x)].push_back(RC);
			}
		}
	}

}

void _vectorcall StaticQSortByXV(Vector<class EObject*> vec[2][32]) noexcept
{

	for (int32 i = 0; i < 32; i++)
	{
		if (xta[i])
		{
			_static_sortPxVTP(vec[0][i].begin(), vec[0][i].end());
		}
	}

}
*/

void _vectorcall __CleanUp(class modern_array<class EObject*>* const vec) noexcept
{
	class GarbageCollector* const collector = GarbageCollector::GetInstance();
	for (int32 i = 0; i < MAP_DIVISION; ++i)
	{
	class modern_array<class EObject*>& vectemp = vec[i];
	for (int32 j = 0; j < vectemp.size(); ++j)
	{
		class EObject* obj = vectemp[j];
		if (obj)
		{
			modern_guard guard(obj);
			switch (obj->m_managementType)
			{
			case ObjectManagementType::OBJECT_MANAGEMENT_DISABLED:
				break;
			case ObjectManagementType::OBJECT_MANAGEMENT_REMOVE:
				obj->m_managementType = ObjectManagementType::OBJECT_MANAGEMENT_DISABLED;
				vectemp.remove(j);
				j--;
				break;
			case ObjectManagementType::OBJECT_MANAGEMENT_DELETE:
				collector->AsyncDelete(obj);
				//delete obj;
				obj = nullptr;
				vectemp.remove(j);
				j--;
				break;
				}
				
			
		}
		else
		{
			vectemp.remove(j);
			j--;
		}
	}	
	}
}

