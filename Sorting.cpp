#include "Sorting.h"
#include "Defines.h"
#include <thread>

using std::thread;



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

void _vectorcall SortByY(std::vector<RenderContainer*> vec[4], std::vector<RenderContainer*> vecG[4]) noexcept
{
	constexpr float MAP_YEND = (TILE_MAP_SIZE / 2.0f) * 80.0f;
	constexpr float MAP_YBEG = (TILE_MAP_SIZE / 2.0f) * -80.0f;
	constexpr float MAP_YENDd2 = (TILE_MAP_SIZE / 2.0f) * 40.0f;
	constexpr float MAP_YBEGd2 = (TILE_MAP_SIZE / 2.0f) * -40.0f;

	for (uint32_t i = 0u; i < 4; i++)
		vec[i].clear();

	for (uint32_t i = 0u; i < 4; i++)
	{

		for (auto && RC : vecG[i])
		{
			if (RC->GetBoundingSphere()->Center.y < 0.0f)
			{
				if (RC->GetBoundingSphere()->Center.y < MAP_YBEGd2)
				{
					vec[0].push_back(RC);
				}
				else
				{
					vec[1].push_back(RC);
				}
			}
			else
			{
				if (RC->GetBoundingSphere()->Center.y < MAP_YENDd2)
				{
					vec[2].push_back(RC);
				}
				else
				{
					vec[3].push_back(RC);
				}
			}
		}
	}
	std::thread t0(sortPy, vec[0].begin(), vec[0].end());
	std::thread t1(sortPy, vec[1].begin(), vec[1].end());
	std::thread t2(sortPy, vec[2].begin(), vec[2].end());
	std::thread t3(sortPy, vec[3].begin(), vec[3].end());

	t0.join();
	t1.join();
	t2.join();
	t3.join();
}

void _vectorcall SortByX(std::vector<RenderContainer*> vec[4], std::vector<RenderContainer*> vecG[4]) noexcept
{
	constexpr float MAP_YEND = (TILE_MAP_SIZE / 2.0f) * 80.0f;
	constexpr float MAP_YBEG = (TILE_MAP_SIZE / 2.0f) * -80.0f;
	constexpr float MAP_YENDd2 = (TILE_MAP_SIZE / 2.0f) * 40.0f;
	constexpr float MAP_YBEGd2 = (TILE_MAP_SIZE / 2.0f) * -40.0f;

	vec[0].clear();
	vec[1].clear();
	vec[2].clear();
	vec[3].clear();

	for (uint32_t i = 0u; i < 4; i++)
	{
		for (auto && RC : vecG[i])
		{
			if (RC->GetBoundingSphere()->Center.x < 0.0f)
			{
				if (RC->GetBoundingSphere()->Center.x < MAP_YBEGd2)
				{
					vec[0].push_back(RC);
				}
				else
				{
					vec[1].push_back(RC);
				}
			}
			else
			{
				if (RC->GetBoundingSphere()->Center.x < MAP_YENDd2)
				{
					vec[2].push_back(RC);
				}
				else
				{
					vec[3].push_back(RC);
				}
			}
		}
	}

	std::thread t0(sortPx, vec[0].begin(), vec[0].end());
	std::thread t1(sortPx, vec[1].begin(), vec[1].end());
	std::thread t2(sortPx, vec[2].begin(), vec[2].end());
	std::thread t3(sortPx, vec[3].begin(), vec[3].end());

	t0.join();
	t1.join();
	t2.join();
	t3.join();
}




