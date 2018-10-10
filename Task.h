#pragma once
#include <d3d11_1.h>
#include <directxmath.h>
#include <atomic>

using std::atomic;
using namespace DirectX;

#pragma region
class  Unit;
#pragma endregion

class Task
{

public:

virtual bool Update() = 0;
virtual void Release() = 0;

enum Type
{
	TASKGOTOPOINT,
	TASKPATROL,
	TASKFOLLOW
} m_type;

};

class TaskGotoPoint : public Task
{
public:
	TaskGotoPoint();
	~TaskGotoPoint() = default;

	bool     Update() override;
	void     Release() override;
	Unit*    object;
	XMFLOAT3 destination;
};

class TaskPatrol : public Task
{
public:
	TaskPatrol();
	~TaskPatrol() = default;

	bool     Update() override;
	void     Release() override;
	Unit*    object;
	XMFLOAT3 pointA;
	XMFLOAT3 pointB;
private:
	bool m_target;
};

class TaskFollow : public Task
{
public:

	TaskFollow();
	~TaskFollow() = default;
#define FOLLOWDISTANCE 200.0f

	bool          Update() override;
	void          Release() override;
	Unit*         object;
	Unit*         target;
};


