#pragma once
#include "RenderContainer.h"

#pragma region

#pragma endregion

class Unit : public Model, public RenderContainer
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

	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ShaderPackage &shader) override;
	void Update(float dt) override;
	void SetZ(float z = 0.0f) override;
	BoundingSphere* GetBoundingSphere() override;
	void Release() override;
	bool Flag(uint8_t index) override;
	void Flag(uint8_t index, bool boolean) override;

	void SetTask(Task* task);
	void GiveTask(Task* task);

	float    GetCollisionRadius();

	XMFLOAT3 GetPosition();
	float    GetSpeed();
	float GetZ();
	void SetSpeed(float speed = 0.0f);
	WalkingStance GetWalkingStance();
	void SetWalkingStance(WalkingStance stance);
	void ChangeWalkingStance();
	void SetRotations(float rotations);
	void DiscardTasks(); 
	void SetPosition(XMFLOAT3 position);

#pragma region
	friend class Task;
	friend class TaskGotoPoint;
	friend class TaskPatrol;
	friend class TaskFollow;
	friend struct RenderObject;
	friend struct SortByX;
	friend struct SortByY;
	friend struct UnitsVector;
#pragma endregion


private:

	float         m_speed[2];
	WalkingStance m_walkingStance;
	TaskQueue     m_tasks;
	bool          m_wanderingFlag;

public:
		
};

