#pragma once
#include <d3d11_1.h>
#include <directxmath.h>
#include <atomic>

using std::atomic;
using namespace DirectX;

#pragma region
class  Unit;
class  EObject;
#pragma endregion

class Task
{

public:

virtual bool Update() = 0;
virtual void Release() = 0;

enum Type
{
	NONE,
	TASKGOTOPOINT,
	TASKPATROL,
	TASKFOLLOW,
	TASKATTACK
} m_type;

enum Stance
{
	TSRUNNING,
	TSATTACKING,
	TSNEUTRAL
} m_stance;

};

class TaskGotoPoint : public Task
{
public:
	TaskGotoPoint();
	~TaskGotoPoint() = default;

	bool     Update() override;
	void     Release() override;
	class Unit*    object;
	DirectX::XMFLOAT3 destination;
};

class TaskPatrol : public Task
{
public:
	TaskPatrol();
	~TaskPatrol() = default;

	bool     Update() override;
	void     Release() override;
	class Unit*    object;
	DirectX::XMFLOAT3 pointA;
	DirectX::XMFLOAT3 pointB;
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
	class Unit*         object;
	class Unit*         target;
};

class TaskAttack : public Task
{
public:

	TaskAttack();
	~TaskAttack() = default;

	void Initialize();

	bool          Update() override;
	void          Release() override;
	class  Unit*         object{};
	class  EObject*      target{};

	bool inrange;
};


