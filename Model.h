#pragma once
#include "SpriteModel.h"
#include <DirectXCollision.h>


using namespace DirectX;

class Model : public BoundingSphere
{
protected:
#pragma region
#define COLLISION_DISABLED_OR_NULL 0.0f
#define POSITION_ZERO_POINT_X 0.0f
#define POSITION_ZERO_POINT_Y 0.0f
#define POSITION_ZERO_POINT_Z 0.0f
#pragma endregion
public:
	Model(void);
	Model(const Model&);
	~Model(void);

	void InitializeSpriteModel(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader,ModelPaths paths, float spriteSize);


	void Update(float dt);
	void UpdatePosition();

	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix,Shader* shader);

	void SetCollisionRadius(float radius = COLLISION_DISABLED_OR_NULL);
	void SetPosition(float x = POSITION_ZERO_POINT_X, float y = POSITION_ZERO_POINT_Y,float z = POSITION_ZERO_POINT_Z);
	void SetPosition(XMFLOAT3 position);
	void SetVelocity(float x = 0.0f, float y = 0.0f,float z = 0.0f);
	void SetVelocity(XMFLOAT3 velocity);
	void Translate(float x = 0.0f, float y = 0.0f,float z = 0.0f);
	void SetRotation(int rotation);
	void SetAnimation(SpriteModel::ModelStance animation,bool lock = false,bool force = false);
	void SetAnimationSpeed(float speed = 1.0f);
	void PlayAnimation(SpriteModel::ModelStance animation);
	void PlayAnimation(SpriteModel::ModelStance animation, SpriteModel::ModelStance after);
	void Resize(ID3D11Device * device, Shader * shader, float resize);
	void SetRenderingStance(bool render = true);
	void Block(bool block = true);
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetVelocity();
	void GoBack();

private:

	XMFLOAT4X4   m_worldMatrix;
	XMFLOAT3     m_lastPosition;
//	XMVECTOR     m_position;
	XMFLOAT3     m_velocity;
	SpriteModel* m_spriteModel;

public:
	bool m_flags[4];
	//bool         m_enabledRendering;
	//bool         m_selectedStance;
	//bool         m_pushable;


};