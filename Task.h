#pragma once
#include <d3d11_1.h>
#include <directxmath.h>
#include <atomic>

using std::atomic;
using namespace DirectX;

#pragma region
class  Unit;
#pragma endregion

struct TaskFleeFromPoint
{
	TaskFleeFromPoint() = default;
	~TaskFleeFromPoint() = default;
	bool     Update();
	Unit*    object;
	XMFLOAT3 pointA;
};

struct TaskFleeFromUnit
{
	TaskFleeFromUnit() = default;
	~TaskFleeFromUnit() = default;
	bool          Update();
	Unit*         object;
	atomic<Unit*> target;
};

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
			TaskFleeFromUnit*  taskFleeFromUnit;
			TaskFleeFromPoint* taskFleeFromPoint;
			//TaskAttack*        taskAttack;
			//TaskDefendUnit*    taskDefendUnit;
		};
	
		enum Type
		{
			TASKGOTOPOINT = 0,
			TASKPATROL = 1,
			TASKFOLLOW = 2,
			TASKFLEEFROMUNIT = 3,
			TASKFLEEFROMPOINT = 4,
			TASKATTACK = 5,
			TASKDEFENDUNIT = 6
		};
	
		Type    m_type;
		Content m_content;
#pragma endregion

	bool Update();
};
