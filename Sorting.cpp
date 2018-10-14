#include "Sorting.h"
#include "Defines.h"
#include "Camera.h"
#include "IPP.h"
#include <thread>
#include <sstream>
#include <sal.h>

using std::thread;

constexpr float MAP_XEND = (TILE_MAP_SIZE / 2.0f)    * (80.0f * ipp::SQRT2);
constexpr float MAP_XBEG = (TILE_MAP_SIZE / 2.0f)    * (-80.0f* ipp::SQRT2);
constexpr float MAP_XENDd2 = (TILE_MAP_SIZE / 2.0f)  * (40.0f * ipp::SQRT2);
constexpr float MAP_XBEGd2 = (TILE_MAP_SIZE / 2.0f)  * (-40.0f* ipp::SQRT2);
constexpr float MAP_XENDd34 = (TILE_MAP_SIZE / 2.0f) * (60.0f * ipp::SQRT2);
constexpr float MAP_XBEGd34 = (TILE_MAP_SIZE / 2.0f) * (-60.0f* ipp::SQRT2);

constexpr float MAP_XENDd78 = (TILE_MAP_SIZE / 2.0f) * (70.0f * ipp::SQRT2);
constexpr float MAP_XBEGd78 = (TILE_MAP_SIZE / 2.0f) * (-70.0f* ipp::SQRT2);
constexpr float MAP_XENDd58 = (TILE_MAP_SIZE / 2.0f) * (50.0f * ipp::SQRT2);
constexpr float MAP_XBEGd58 = (TILE_MAP_SIZE / 2.0f) * (-50.0f* ipp::SQRT2);
constexpr float MAP_XENDd38 = (TILE_MAP_SIZE / 2.0f) * (30.0f * ipp::SQRT2);
constexpr float MAP_XBEGd38 = (TILE_MAP_SIZE / 2.0f) * (-30.0f* ipp::SQRT2);
constexpr float MAP_XENDd18 = (TILE_MAP_SIZE / 2.0f) * (10.0f * ipp::SQRT2);
constexpr float MAP_XBEGd18 = (TILE_MAP_SIZE / 2.0f) * (-10.0f* ipp::SQRT2);

constexpr float MAP_XENDd14 = (TILE_MAP_SIZE / 2.0f) * (20.0f* ipp::SQRT2 );
constexpr float MAP_XBEGd14 = (TILE_MAP_SIZE / 2.0f) * (-20.0f* ipp::SQRT2);

constexpr float MAP_YEND = (TILE_MAP_SIZE / 2.0f)    * (40.0f* ipp::SQRT2 );
constexpr float MAP_YBEG = (TILE_MAP_SIZE / 2.0f)    * (-40.0f* ipp::SQRT2);
constexpr float MAP_YENDd2 = (TILE_MAP_SIZE / 2.0f)  * (20.0f* ipp::SQRT2 );
constexpr float MAP_YBEGd2 = (TILE_MAP_SIZE / 2.0f)  * (-20.0f* ipp::SQRT2);
constexpr float MAP_YENDd34 = (TILE_MAP_SIZE / 2.0f) * (30.0f* ipp::SQRT2 );
constexpr float MAP_YBEGd34 = (TILE_MAP_SIZE / 2.0f) * (-30.0f* ipp::SQRT2);
constexpr float MAP_YENDd14 = (TILE_MAP_SIZE / 2.0f) * (10.0f* ipp::SQRT2 );
constexpr float MAP_YBEGd14 = (TILE_MAP_SIZE / 2.0f) * (-10.0f* ipp::SQRT2);

constexpr float MAP_YENDd78 = (TILE_MAP_SIZE / 2.0f) * (35.0f * ipp::SQRT2);
constexpr float MAP_YBEGd78 = (TILE_MAP_SIZE / 2.0f) * (-35.0f* ipp::SQRT2);
constexpr float MAP_YENDd58 = (TILE_MAP_SIZE / 2.0f) * (25.0f * ipp::SQRT2);
constexpr float MAP_YBEGd58 = (TILE_MAP_SIZE / 2.0f) * (-25.0f* ipp::SQRT2);
constexpr float MAP_YENDd38 = (TILE_MAP_SIZE / 2.0f) * (15.0f * ipp::SQRT2);
constexpr float MAP_YBEGd38 = (TILE_MAP_SIZE / 2.0f) * (-15.0f* ipp::SQRT2);
constexpr float MAP_YENDd18 = (TILE_MAP_SIZE / 2.0f) * (5.0f * ipp::SQRT2 );
constexpr float MAP_YBEGd18 = (TILE_MAP_SIZE / 2.0f) * (-5.0f* ipp::SQRT2 );

int8_t GetXCell(float x)
{
	int8_t r{};
	if (x < 0.0f)
	{
		if (x < MAP_XBEGd2)
		{
			if (x < MAP_XBEGd34)
			{
				if (x < MAP_XBEGd78)
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
				if (x < MAP_XBEGd58)
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
			if (x < MAP_XBEGd14)
			{
				if (x < MAP_XBEGd38)
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
				if (x < MAP_XBEGd18)
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
		if (x < MAP_XENDd2)
		{
			if (x < MAP_XENDd14)
			{
				if (x < MAP_XENDd18)
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
				if (x < MAP_XENDd38)
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
			if (x < MAP_XENDd34)
			{
				if (x < MAP_XENDd58)
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
				if (x < MAP_XENDd78)
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
int8_t GetYCell(float y)
{
	int8_t r{};

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

template <class T>
bool __validate_Xrendering__(const T index) noexcept
{
	int8_t t0 = xp - index;
	if (t0 <= (RENDER_CELLS_RANGE) && t0 >= (-RENDER_CELLS_RANGE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <class T>
bool __validate_Yrendering__(const T index) noexcept
{
	int8_t t0 = yp - index;
	if (t0 <= (RENDER_CELLS_RANGE) && t0 >= (-RENDER_CELLS_RANGE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void __intersect_test__()
{
	Camera* cam = Camera::GetCurrentCamera();
	DirectX::XMVECTOR pvx = cam->GetPosition();


xp = GetXCell(pvx.m128_f32[0]);
yp = GetYCell(pvx.m128_f32[1]);

for (uint16_t i = 0u; i < 16u; i++)
{
	xta[i] = __validate_Xrendering__(i);
	yta[i] = __validate_Yrendering__(i);
}
}



bool __sort__SortByY::operator()(RenderContainer * a, RenderContainer * b) const noexcept
{
	BoundingSphere* bsa = a->GetBoundingSphere();
	BoundingSphere* bsb = b->GetBoundingSphere();

	bool af2 = a->Flag(2u);
	bool bf2 = b->Flag(2u);

	float radius[3];
	float ax, ay, bx, by;

	radius[0] = bsa->Radius;
	radius[1] = bsb->Radius;
	ax = bsa->Center.x;
	ay = bsa->Center.y;

	bx = bsb->Center.x;
	by = bsb->Center.y;

	radius[2] = radius[0] + radius[1];
	float distance = 0.0f;
	float distanceX = 0.0f, distanceY = 0.0f;
	float collision = 0.0f;

	distanceX = ax - bx;
	distanceY = ay - by;
	distance = XMVector2Length({ distanceX,distanceY }).m128_f32[0];
	if (distance < radius[2])
	{
		collision = distance - radius[2];
		if (af2)
		{
			if (bf2)
			{
				collision /= 2.0f;
				if (ax < bx)
				{
					bsa->Center.x += collision;
					bsb->Center.x -= collision;
				}
				else
				{
					bsa->Center.x -= collision;
					bsa->Center.x += collision;
				}
			}
			else
			{
				if (ax < bx) bsa->Center.x += collision;
				else         bsa->Center.x -= collision;
			}
		}
		else
		{
			if (bf2)
			{
				if (ax < bx) bsb->Center.x -= collision;
				else         bsb->Center.x += collision;
			}
		}
	}
	return ay > by;
}

bool __sort__SortByX::operator()(RenderContainer * a, RenderContainer * b) const noexcept
{
	BoundingSphere* bsa = a->GetBoundingSphere();
	BoundingSphere* bsb = b->GetBoundingSphere();

	bool af2 = a->Flag(2u);
	bool bf2 = b->Flag(2u);

	float radius[3];
	float ax, ay, bx, by;

	radius[0] = bsa->Radius;
	radius[1] = bsb->Radius;

	ax = bsa->Center.x;
	ay = bsa->Center.y;

	bx = bsb->Center.x;
	by = bsb->Center.y;

	radius[2] = radius[0] + radius[1];
	float distance = 0.0f;
	float distanceX = 0.0f, distanceY = 0.0f;
	float collision = 0.0f;

	distanceX = ax - bx;
	distanceY = ay - by;
	distance = XMVector2Length({ distanceX,distanceY }).m128_f32[0];
	if (distance < radius[2])
	{
		collision = distance - radius[2];
		if (af2)
		{
			if (bf2)
			{
				collision /= 2.0f;
				if (ay < by)
				{
					bsa->Center.y += collision;
					bsb->Center.y -= collision;
				}
				else
				{
					bsa->Center.y -= collision;
					bsb->Center.y += collision;
				}
			}
			else
			{
				if (ay < by) bsa->Center.y += collision;
				else         bsa->Center.y -= collision;

			}
		}
		else
		{
			if (bf2)
			{
				if (ay < by) bsb->Center.y -= collision;
				else         bsb->Center.y += collision;
			}

		}

	}

	return ax > bx;
}

void _cdecl sortPy(std::vector<RenderContainer*>::iterator begin, std::vector<RenderContainer*>::iterator end) noexcept
{
	std::sort(begin, end, __sort__SortByY());
}

void _cdecl sortPx(std::vector<RenderContainer*>::iterator begin, std::vector<RenderContainer*>::iterator end) noexcept
{
	std::sort(begin, end, __sort__SortByX());
}

void _vectorcall SortByY(std::vector<RenderContainer*> vec[16], std::vector<RenderContainer*> vecG[16]) noexcept
{


	for (uint32_t i = 0u; i < 16u; i++)
		vec[i].clear();

	for (uint32_t i = 0u; i < 16u; i++)
	{
		for (auto && RC : vecG[i])
		{
			vec[GetYCell(RC->GetBoundingSphere()->Center.y)].push_back(RC);
		}
	}

	std::vector<std::thread*> threads;

	for (uint32_t i = 0u; i < 16u; i++)
	{
		if (yta[i])
		{
			std::thread* t = new thread(sortPy, vec[i].begin(), vec[i].end());
			threads.push_back(t);
		}
	}

	for (auto && thread : threads)
	{
		if (thread)
		{
			thread->join();
			delete thread;
			thread = nullptr;
		}
	}

	threads.clear();
}

void _vectorcall SortByX(std::vector<RenderContainer*> vec[16], std::vector<RenderContainer*> vecG[16]) noexcept
{
	__intersect_test__();

	for (uint32_t i = 0u; i < 16u; i++)
	vec[i].clear();

	for (uint32_t i = 0u; i < 16u; i++)
	{
		for (auto && RC : vecG[i])
		{
		vec[GetXCell(RC->GetBoundingSphere()->Center.x)].push_back(RC);
		}	
	}



	std::vector<std::thread*> threads;

	for (uint32_t i = 0u; i < 16u; i++)
	{
		if (xta[i])
		{
			std::thread* t = new thread(sortPx, vec[i].begin(), vec[i].end());
			threads.push_back(t);
		}
	}

	for (auto && thread : threads)
	{
		if (thread)
		{
			thread->join();
			delete thread;
			thread = nullptr;
		}
	}

	threads.clear();
}




