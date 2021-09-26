#pragma once
#include "modern/modern_guard.h"
#include "modern/modern_shared_guard.h"
#include "modern/modern_handle.h"

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
	class modern_handle    object;
	DirectX::XMFLOAT3 destination;
};

class TaskPatrol : public Task
{
public:
	TaskPatrol();
	~TaskPatrol() = default;

	bool     Update() override;
	void     Release() override;
	class modern_handle    object;
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
	class modern_handle         object;
	class modern_handle         target;
};

class TaskAttack : public Task
{
public:

	TaskAttack();
	~TaskAttack() = default;

	void Initialize();

	bool          Update() override;
	void          Release() override;
	class  modern_handle        object{};
	class  modern_handle      target{};

	bool inrange;
};

class TaskCastAtPoint : public Task
{
public:

	//TaskCastAtPoint();
	//~TaskCastAtPoint() = default;
	//
	//void Initialize();
	//
	//bool              Update() override;
	//void              Release() override;
	//class  Unit*      object{};
	//DirectX::XMFLOAT3 pointA;
	//
	//bool inrange;
};


