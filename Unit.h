#pragma once
#include "Model.h"
#include "SuperModel.h"
#include "TaskQueue.h"
#include "Types.h"

#pragma region

#pragma endregion

class Unit : public Model
{
public:
#pragma region
	enum WalkingStance
	{
		WALK = 0,
		RUN = 1
	};
#pragma endregion
	Unit();
	~Unit();
	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader, WCHAR* paths,float size, float collision, XMFLOAT3 position,bool wander = true);
	void Update(float dt);
	void SetTask(Task* task);
	void GiveTask(Task* task);
	float    GetCollisionRadius();
	XMFLOAT3 GetPosition();
	float    GetSpeed();
	void SetSpeed(float speed = 0.0f);
	WalkingStance GetWalkingStance();
	void SetWalkingStance(WalkingStance stance);
	void ChangeWalkingStance();
	void SetRotations(float rotations);
	void DiscardTasks(); 
	void SetPosition(XMFLOAT3 position);

#pragma region
	friend struct Task;
	friend struct TaskGotoPoint;
	friend struct TaskPatrol;
	friend struct TaskFollow;
	friend struct RenderObject;
	friend struct SortByX;
	friend struct SortByY;
	friend struct UnitsVector;
#pragma endregion


private:

    uint32_t      m_index;
	float         m_speed[2];
	WalkingStance m_walkingStance;
	TaskQueue     m_tasks;
	bool          m_wanderingFlag;

public:
		
};

