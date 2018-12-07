#include "Sorting.h"
#include "Defines.h"
#include "Camera.h"
#include "IPP.h"
#include "Vector.h"
#include "ThreadPool.h"
#include <thread>
#include <sstream>
#include <sal.h>
#include <forward_list>


using std::thread;

namespace
{
using ipp::SQRT2;
#define HALF_MAP_SIZE (TILE_MAP_SIZE / 2.0f)
	constexpr float MAP_XEND = HALF_MAP_SIZE * (80.0f  * SQRT2);
	constexpr float MAP_XBEG = HALF_MAP_SIZE * (-80.0f * SQRT2);
	constexpr float MAP_XENDd14 = HALF_MAP_SIZE * (20.0f  * SQRT2);
	constexpr float MAP_XBEGd14 = HALF_MAP_SIZE * (-20.0f * SQRT2);
	constexpr float MAP_XENDd2 = HALF_MAP_SIZE * (40.0f  * SQRT2);
	constexpr float MAP_XBEGd2 = HALF_MAP_SIZE * (-40.0f * SQRT2);
	constexpr float MAP_XENDd34 = HALF_MAP_SIZE * (60.0f  * SQRT2);
	constexpr float MAP_XBEGd34 = HALF_MAP_SIZE * (-60.0f * SQRT2);

	constexpr float MAP_XENDd78 = HALF_MAP_SIZE * (70.0f  * SQRT2);
	constexpr float MAP_XBEGd78 = HALF_MAP_SIZE * (-70.0f * SQRT2);
	constexpr float MAP_XENDd58 = HALF_MAP_SIZE * (50.0f  * SQRT2);
	constexpr float MAP_XBEGd58 = HALF_MAP_SIZE * (-50.0f * SQRT2);
	constexpr float MAP_XENDd38 = HALF_MAP_SIZE * (30.0f  * SQRT2);
	constexpr float MAP_XBEGd38 = HALF_MAP_SIZE * (-30.0f * SQRT2);
	constexpr float MAP_XENDd18 = HALF_MAP_SIZE * (10.0f  * SQRT2);
	constexpr float MAP_XBEGd18 = HALF_MAP_SIZE * (-10.0f * SQRT2);

	constexpr float MAP_XENDd1516 = HALF_MAP_SIZE * (75.0f  * SQRT2);
	constexpr float MAP_XBEGd1516 = HALF_MAP_SIZE * (-75.0f * SQRT2);
	constexpr float MAP_XENDd1316 = HALF_MAP_SIZE * (65.0f  * SQRT2);
	constexpr float MAP_XBEGd1316 = HALF_MAP_SIZE * (-65.0f * SQRT2);
	constexpr float MAP_XENDd1116 = HALF_MAP_SIZE * (55.0f  * SQRT2);
	constexpr float MAP_XBEGd1116 = HALF_MAP_SIZE * (-55.0f * SQRT2);
	constexpr float MAP_XENDd916 = HALF_MAP_SIZE * (45.0f  * SQRT2);
	constexpr float MAP_XBEGd916 = HALF_MAP_SIZE * (-45.0f * SQRT2);
	constexpr float MAP_XENDd716 = HALF_MAP_SIZE * (35.0f  * SQRT2);
	constexpr float MAP_XBEGd716 = HALF_MAP_SIZE * (-35.0f * SQRT2);
	constexpr float MAP_XENDd516 = HALF_MAP_SIZE * (25.0f  * SQRT2);
	constexpr float MAP_XBEGd516 = HALF_MAP_SIZE * (-25.0f * SQRT2);
	constexpr float MAP_XENDd316 = HALF_MAP_SIZE * (15.0f  * SQRT2);
	constexpr float MAP_XBEGd316 = HALF_MAP_SIZE * (-15.0f * SQRT2);
	constexpr float MAP_XENDd116 = HALF_MAP_SIZE * (5.0f  * SQRT2);
	constexpr float MAP_XBEGd116 = HALF_MAP_SIZE * (-5.0f * SQRT2);

	constexpr float MAP_YEND = HALF_MAP_SIZE * (40.0f  * SQRT2);
	constexpr float MAP_YBEG = HALF_MAP_SIZE * (-40.0f * SQRT2);
	constexpr float MAP_YENDd2 = HALF_MAP_SIZE * (20.0f  * SQRT2);
	constexpr float MAP_YBEGd2 = HALF_MAP_SIZE * (-20.0f * SQRT2);
	constexpr float MAP_YENDd34 = HALF_MAP_SIZE * (30.0f  * SQRT2);
	constexpr float MAP_YBEGd34 = HALF_MAP_SIZE * (-30.0f * SQRT2);
	constexpr float MAP_YENDd14 = HALF_MAP_SIZE * (10.0f  * SQRT2);
	constexpr float MAP_YBEGd14 = HALF_MAP_SIZE * (-10.0f * SQRT2);

	constexpr float MAP_YENDd78 = HALF_MAP_SIZE * (35.0f  * SQRT2);
	constexpr float MAP_YBEGd78 = HALF_MAP_SIZE * (-35.0f * SQRT2);
	constexpr float MAP_YENDd58 = HALF_MAP_SIZE * (25.0f  * SQRT2);
	constexpr float MAP_YBEGd58 = HALF_MAP_SIZE * (-25.0f * SQRT2);
	constexpr float MAP_YENDd38 = HALF_MAP_SIZE * (15.0f  * SQRT2);
	constexpr float MAP_YBEGd38 = HALF_MAP_SIZE * (-15.0f * SQRT2);
	constexpr float MAP_YENDd18 = HALF_MAP_SIZE * (5.0f   * SQRT2);
	constexpr float MAP_YBEGd18 = HALF_MAP_SIZE * (-5.0f  * SQRT2);

	constexpr float MAP_YENDd1516 = HALF_MAP_SIZE * (37.5f  * SQRT2);
	constexpr float MAP_YBEGd1516 = HALF_MAP_SIZE * (-37.5f * SQRT2);
	constexpr float MAP_YENDd1316 = HALF_MAP_SIZE * (32.5f  * SQRT2);
	constexpr float MAP_YBEGd1316 = HALF_MAP_SIZE * (-32.5f * SQRT2);
	constexpr float MAP_YENDd1116 = HALF_MAP_SIZE * (27.5f  * SQRT2);
	constexpr float MAP_YBEGd1116 = HALF_MAP_SIZE * (-27.5f * SQRT2);
	constexpr float MAP_YENDd916 = HALF_MAP_SIZE * (22.5f   * SQRT2);
	constexpr float MAP_YBEGd916 = HALF_MAP_SIZE * (-22.5f  * SQRT2);
	constexpr float MAP_YENDd716 = HALF_MAP_SIZE * (17.5f  * SQRT2);
	constexpr float MAP_YBEGd716 = HALF_MAP_SIZE * (-17.5f * SQRT2);
	constexpr float MAP_YENDd516 = HALF_MAP_SIZE * (12.5f  * SQRT2);
	constexpr float MAP_YBEGd516 = HALF_MAP_SIZE * (-12.5f * SQRT2);
	constexpr float MAP_YENDd316 = HALF_MAP_SIZE * (7.5f  * SQRT2);
	constexpr float MAP_YBEGd316 = HALF_MAP_SIZE * (-7.5f * SQRT2);
	constexpr float MAP_YENDd116 = HALF_MAP_SIZE * (2.5f   * SQRT2);
	constexpr float MAP_YBEGd116 = HALF_MAP_SIZE * (-2.5f  * SQRT2);

	std::atomic<void*> tp_p_one;
	std::atomic<void*> tp_p_two;
}


_Use_decl_annotations_
int8_t _Out_opt_ GetXCell(const _In_opt_ float x) noexcept
{
	int8_t r;
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
						r = 0;
					}
					else
					{
						r = 1;
					}
					
				}
				if (x < MAP_XBEGd1316)
				{
					r = 2;
				}
				else
				{
					r = 3;
				}
			}
			else
			{
				if (x < MAP_XBEGd58)
				{
					if (x < MAP_XBEGd1116)
					{
						r = 4;
					}
					else
					{
						r = 5;
					}
				}
				else
				{
					if (x < MAP_XBEGd916)
					{
						r = 6;
					}
					else
					{
						r = 7;
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
						r = 8;
					}
					else
					{
						r = 9;
					}
				}
				else
				{
					if (x < MAP_XBEGd516)
					{
						r = 10;
					}
					else
					{
						r = 11;
					}
				}
			}
			else
			{
				if (x < MAP_XBEGd18)
				{
					if (x < MAP_XBEGd316)
					{
						r = 12;
					}
					else
					{
						r = 13;
					}
				}
				else
				{
					if (x < MAP_XBEGd116)
					{
						r = 14;
					}
					else
					{
						r = 15;
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
						r = 16;
					}
					else
					{
						r = 17;
					}
				}
				else
				{
					if (x < MAP_XENDd316)
					{
						r = 18;
					}
					else
					{
						r = 19;
					}
				}
			}
			else
			{
				if (x < MAP_XENDd38)
				{
					if (x < MAP_XENDd516)
					{
						r = 20;
					}
					else
					{
						r = 21;
					}
				}
				else
				{
					if (x < MAP_XENDd716)
					{
						r = 22;
					}
					else
					{
						r = 23;
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
						r = 24;
					}
					else
					{
						r = 25;
					}
				}
				else
				{
					if (x < MAP_XENDd1116)
					{
						r = 26;
					}
					else
					{
						r = 27;
					}
				}
			}
			else
			{
				if (x < MAP_XENDd78)
				{
					if (x < MAP_XENDd1316)
					{
						r = 28;
					}
					else
					{
						r = 29;
					}
				}
				else
				{
					if (x < MAP_XENDd1516)
					{
						r = 30;
					}
					else
					{
						r = 31;
					}
				}
			}
		}
	}
	return r;
}
int8_t GetYCell(float y)
{
	int8_t r;

	if (y < 0.0f)
	{
		if (y < MAP_YBEGd2)
		{
			if (y < MAP_YBEGd34)
			{
				if (y < MAP_YBEGd78)
				{
					r = 0;
				}
				else
				{
					r = 1;
				}
			}
			else
			{
				if (y < MAP_YBEGd58)
				{
					r = 2;
				}
				else
				{
					r = 3;
				}
			}
		}
		else
		{
			if (y < MAP_YBEGd14)
			{
				if (y < MAP_YBEGd38)
				{
					r = 4;
				}
				else
				{
					r = 5;
				}
			}
			else
			{
				if (y < MAP_YBEGd18)
				{
					r = 6;
				}
				else
				{
					r = 7;
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
					r = 8;
				}
				else
				{
					r = 9;
				}
			}
			else
			{
				if (y < MAP_YENDd38)
				{
					r = 10;
				}
				else
				{
					r = 11;
				}
				
			}
		}
		else
		{
			if (y < MAP_YENDd34)
			{
				if (y < MAP_YENDd58)
				{
					r = 12;
				}
				else
				{
					r = 13;
				}
			}
			else
			{
				if (y < MAP_YENDd78)
				{
					r = 14;
				}
				else
				{
					r = 15;
				}
			}
		}
	}

	return r;
}

_Use_decl_annotations_
template <class T>
bool _Out_opt_ _fastcall __validate_Xrendering__(const T& _In_opt_ index) noexcept
{
	const int8_t t0 = xp - index;
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
bool _Out_opt_ _fastcall __validate_Yrendering__(const T& _In_opt_ index) noexcept
{
	const int8_t t0 = yp - index;
	if (t0 <= (RENDER_CELLS_RANGE) && t0 >= (-RENDER_CELLS_RANGE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void _cdecl __intersect_test__() noexcept
{
	Camera* cam = Camera::GetCurrentCamera();
	DirectX::XMVECTOR pvx = cam->GetPosition();


xp = GetXCell(pvx.m128_f32[0]);
yp = GetYCell(pvx.m128_f32[1]);

for (uint16_t i = 0u; i < 32u; i++)
{
	xta[i] = __validate_Xrendering__(i);
	yta[i] = __validate_Yrendering__(i);
}
}

bool _stdcall __sort__SortByY::operator()(RenderContainer * A, RenderContainer * B) const noexcept
{

	const bool Apushable = A->m_pushable;
	const bool Bpushable = B->m_pushable;
	const float Aradius = A->Radius;
	const float Bradius = B->Radius;
	const float Ax = A->Center.x;
	const float Ay = A->Center.y;
	const float Bx = B->Center.x;
	const float By = B->Center.y;
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
			Scollision /= 2.0f;
			if (Ax < Bx)
			{
				A->Center.x += Scollision;
				B->Center.x -= Scollision;
			}
			else
			{
				A->Center.x -= Scollision;
				B->Center.x += Scollision;
			}
		}
		else
		{
			if (Apushable)
			{
			if (Ax < Bx) A->Center.x += Scollision;
			else         A->Center.x -= Scollision;
			}
			else
			{
			if (Ax < Bx) B->Center.x -= Scollision;
			else         B->Center.x += Scollision;
			}
		}
	}
	return Ay > By;
}

bool _stdcall __sort__SortByX::operator()(RenderContainer * A, RenderContainer * B) const noexcept
{
	const bool Apushable = A->m_pushable;
	const bool Bpushable = B->m_pushable;
	const float Aradius = A->Radius;
	const float Bradius = B->Radius;
	const float Ax = A->Center.x;
	const float Ay = A->Center.y;
	const float Bx = B->Center.x;
	const float By = B->Center.y;
	const float Sradius = Aradius + Bradius;
	const float Xdistance = Ax - Bx;
	const float Ydistance = Ay - By;
	const float Sdistance = XMVector2Length({ Xdistance,Ydistance }).m128_f32[0];

	if (Sdistance < Sradius)
	{
		float Scollision = Sdistance - Sradius;
		if (Apushable == Bpushable)
		{
			Scollision /= 2.0f;
			if (Ay < By)
			{
				A->Center.y += Scollision;
				B->Center.y -= Scollision;
			}
			else
			{
				A->Center.y -= Scollision;
				B->Center.y += Scollision;
			}
		}
		else
		{
			if (Apushable)
			{
				if (Ay < By) A->Center.y += Scollision;
				else         A->Center.y -= Scollision;
			}
			else
			{
				if (Ay < By) B->Center.y -= Scollision;
				else         B->Center.y += Scollision;	
			}
		}
	}
	return Ax > Bx;
}

void _cdecl sortPyV(RenderContainer** begin, RenderContainer** end) noexcept
{
	std::sort(begin, end, __sort__SortByY());
}

void _cdecl sortPxV(RenderContainer** begin, RenderContainer** end) noexcept
{
	std::sort(begin, end, __sort__SortByX());
}

void _stdcall sortPxVTP(RenderContainer** begin, RenderContainer** end) noexcept
{
	std::sort(begin, end, __sort__SortByX());
}

void _stdcall sortPyVTP(RenderContainer** begin, RenderContainer** end) noexcept
{
	std::sort(begin, end, __sort__SortByY());
}

void _vectorcall SortByYV(Vector<RenderContainer*> vec[2][32]) noexcept
{
	for (uint32_t i = 0u; i < 32u; i++)
		vec[1][i].clear();

	for (uint32_t i = 0u; i < 32u; i++)
	{
		for (auto && RC : vec[0][i])
		{
			if(RC)
			vec[1][GetYCell(RC->Center.y)].push_back(RC);
		}
	}

	ThreadPoolHandle pool;

	//Vector<std::thread*> threads;
	//
	for (uint32_t i = 0u; i < 32u; i++)
	{
		if (yta[i])
		{
			pool.pool->push([vec, i]() { sortPyVTP(vec[1][i].begin(), vec[1][i].end()); });
		}
	}

	pool.pool->wait();

	//Vector<std::thread*> threads;
	//
	//for (uint32_t i = 0u; i < 32u; i++)
	//{
	//	if (yta[i])
	//	{
	//		threads.push_back(new thread(sortPyV, vec[1][i].begin(), vec[1][i].end()));
	//	}
	//}
	//
	//for (auto && thread : threads)
	//{
	//	if (thread)
	//	{
	//		thread->join();
	//		delete thread;
	//		thread = nullptr;
	//	}
	//}
	//
	//threads.clear();
}

void _vectorcall SortByXV(Vector<RenderContainer*> vec[2][32]) noexcept
{
	__intersect_test__();

	for (uint32_t i = 0u; i < 32u; i++)
		vec[0][i].clear();

	for (uint32_t i = 0u; i < 32u; i++)
	{
		for (auto && RC : vec[1][i])
		{
			if(RC)
			vec[0][GetXCell(RC->Center.x)].push_back(RC);
		}
	}

	ThreadPoolHandle pool;

	

	//Vector<std::thread*> threads;
	//
	for (uint32_t i = 0u; i < 32u; i++)
	{
		if (xta[i])
		{
			pool.pool->push([vec,i]() { sortPxVTP(vec[0][i].begin(), vec[0][i].end()); });
		}
	}

	pool.pool->wait();
	
	//for (auto && thread : threads)
	//{
	//	if (thread)
	//	{
	//		thread->join();
	//		delete thread;
	//		thread = nullptr;
	//	}
	//}
	//
	//threads.clear();


}
