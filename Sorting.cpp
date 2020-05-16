#include "Sorting.h"
#include "Defines.h"
#include "Camera.h"
#include "Vector.h"
#include "ThreadPool.h"
#include "Math.h"
#include "Tile.h"
#include <thread>
#include <sstream>
#include <sal.h>
#include <omp.h>
#include <DirectXMath.h>


using std::thread;

namespace
{
#define HALF_MAP_SIZE (TILE_MAP_SIZE / 2.0f)
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
}



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
					return 0;
				}
				else
				{
					return 1;
				}
			}
			else
			{
				if (y < MAP_YBEGd58)
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

_Use_decl_annotations_
template <class T>
__forceinline constexpr int32 _Out_ _stdcall __validate_Xrendering__(const T& _In_ index) noexcept
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
__forceinline constexpr int32 _Out_ _stdcall __validate_Yrendering__(const T& _In_ index) noexcept
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

__forceinline void _stdcall __intersect_test__() noexcept
{
	float cameraPosition[4];
	_mm_store_ps(cameraPosition, Camera::GetCurrentCamera()->GetPosition());
	xp = GetXCell(cameraPosition[0]);
	yp = GetYCell(cameraPosition[1]);


for ( int32 i = 0u; i < 32; i++)
{
	xta[i] = __validate_Xrendering__(i);
	yta[i] = __validate_Yrendering__(i);
}
}

bool _stdcall __sort__SortByY::operator()(class EObject * const A,class EObject * const B) const noexcept
{



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

	if (Sdistance < Sradius)
	{
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

bool _stdcall __sort__SortByX::operator()(class EObject * const A,class EObject * const B) const noexcept
{
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
	}
	return Ax > Bx;
}


void _stdcall sortPyV(class EObject** _In_ const begin,class EObject** _In_ const end) noexcept
{
	_Sort_unchecked(begin, end, end - begin,__sort__SortByY());

	//	_Make_heap_unchecked(begin, end, __sort__SortByY());
	//	_Sort_heap_unchecked(begin, end, __sort__SortByY());

}


void _stdcall sortPxV(class EObject** _In_ const begin,class EObject** _In_ const end) noexcept
{
	_Sort_unchecked(begin, end, end - begin, __sort__SortByX());

	//_Make_heap_unchecked(begin, end, __sort__SortByX());
	//_Sort_heap_unchecked(begin, end, __sort__SortByX());
}


void _stdcall sortPxVTP(class EObject** _In_ const begin,class EObject** _In_ const end) noexcept
{
	_Sort_unchecked(begin, end, end - begin, __sort__SortByX());


}


void _stdcall sortPyVTP(class EObject** _In_ const begin,class EObject** _In_ const end) noexcept
{
	_Sort_unchecked(begin, end, end - begin, __sort__SortByY());
}

void _vectorcall SortByYV(class Vector<class EObject*> vec[2][32]) noexcept
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

#pragma omp for schedule(dynamic)
		for (int32 i = 0; i < 32; ++i)
			vec[1][i].clear();

		//#pragma omp pallalel for shedule(dynamic)
#pragma omp barrier
#pragma omp single

		for (int32 i = 0; i < 32; ++i)
		{
			for (auto&& object : vec[0][i])
			{
				vec[1][GetYCell(object->m_boundingSphere.Center.y)].push_back(object);
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
#pragma omp barrier
#pragma omp for schedule(dynamic)
		for (int32 i = 0; i < 32; ++i)
		{
			if (yta[i])
			{
				sortPyVTP(vec[1][i].begin(), vec[1][i].end());
			}
		
	}
}

void _vectorcall SortByXV(class Vector<class EObject*> vec[2][32]) noexcept
{
	__intersect_test__();

#pragma omp for schedule(dynamic)
	for (int32_t i = 0; i < 32; i++)
	{
		vec[0][i].clear();
		vec[1][i].shrink();
	}

#pragma omp barrier
#pragma omp single

		for (int32_t i = 0; i < 32; i++)
		{
			for (auto&& RC : vec[1][i])
			{
				vec[0][GetXCell(RC->m_boundingSphere.Center.x)].push_back(RC);
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
#pragma omp barrier

#pragma omp for schedule(dynamic)
		for (int32 i = 0; i < 32; i++)
		{
			if (xta[i])
			{
				sortPxVTP(vec[0][i].begin(), vec[0][i].end());
			}
		}

}


void _vectorcall __CleanUp(class Vector<class EObject*> vec[2][32]) noexcept
{
#pragma omp for schedule(dynamic)
	for (int32 i = 0; i < 32; ++i)
	{
	class Vector<class EObject*>& vectemp = vec[1][i];
	for (int32 j = 0; j < vectemp.size(); ++j)
	{
		class EObject* obj = vectemp[j];
		if (obj)
		{
			if (obj->isReleased())
			{
				delete obj;
				obj = nullptr;
				vectemp.remove(j);
				j--;
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

