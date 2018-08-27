#pragma once
#include <d3d11_1.h>
#include <directxmath.h>
#include <atomic>

using std::atomic;
using namespace DirectX;

#pragma region
class  Unit;
#pragma endregion

struct TaskGotoPoint // works correctly ;)
{
public:
	TaskGotoPoint() = default;
	~TaskGotoPoint() = default;
	bool     Update();
	Unit*    object;
	XMFLOAT3 destination;
};

struct TaskPatrol  //aint workin correctly
{
	TaskPatrol();
	~TaskPatrol() = default;
	bool     Update();
	Unit*    object;
	XMFLOAT3 pointA;
	XMFLOAT3 pointB;
private:
	bool m_target;
};

struct TaskFollow
{
#define FOLLOWDISTANCE 200.0f
	bool          Update();
	Unit*         object;
	atomic<Unit*> target;
};


struct Task
{
	Task() = default;
	~Task();

#pragma region
		union Content
		{
			TaskGotoPoint*     taskGotoPoint;
			TaskPatrol*        taskPatrol;
			TaskFollow*        taskFollow;
			//TaskAttack*        taskAttack;
			//TaskFleeFromUnit*  taskFleeFromUnit;
			//TaskFleeFromPoint* taskFleeFromPoint;
			//TaskDefendUnit*    taskDefendUnit;
		};
	
		enum Type
		{
			TASKGOTOPOINT = 0,
			TASKPATROL = 1,
			TASKFOLLOW = 2,
			TASKATTACK = 3,
			TASKFLEEFROMUNIT = 4,
			TASKFLEEFROMPOINT = 5,
			TASKDEFENDUNIT = 6
		};
	
		Type    m_type;
		Content m_content;
#pragma endregion

	bool Update();
};
