#pragma once
#include "Model.h"
#include "TaskQueue.h"

#pragma region

#pragma endregion

class Unit
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
	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader, ModelPaths paths,float size, float collision, XMFLOAT3 position,bool wander = true);
	void Update();
	void SetTask(Task* task);
	void GiveTask(Task* task);
	Model* GetModel();

	XMFLOAT3 GetPoint();
	float    GetCollisionRadius();
	XMFLOAT3 GetPosition();
	void SetSpeed(float speed = 0.0f);
	WalkingStance GetWalkingStance();
	void SetWalkingStance(WalkingStance stance);

#pragma region
	friend struct Task;
	friend struct TaskGotoPoint;
	friend struct TaskPatrol;
	friend struct TaskFollow;
	friend struct RenderObject;
	friend struct SortByX;
	friend struct SortByY;
#pragma endregion


private:
	Model*        m_model;
	float         m_speed;
	WalkingStance m_walkingStance;
	TaskQueue     m_tasks;
	bool          m_wanderingFlag;
};

