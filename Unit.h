#pragma once
#include "RenderContainer.h"
#include "S_ModelPaths.h"
#include "Sprite.h"

#pragma region

#pragma endregion



class Unit : public RenderContainer, public BoundingSphere
{
public:

#define STANDARDSTANCE 4
#define DEFAULT_ROTATION       0.0f
#define DEFAULT_ROTATION_SPEED 0.01f

	enum WalkingStance
	{
		WS_WALK = 0,
		WS_RUN = 1
	};

	enum ModelStance
	{
		MS_TOWNWALK = 0,
		MS_TOWNNEUTRAL = 1,
		MS_SPECIALCAST = 2,
		MS_GETHIT = 3,
		MS_KICK = 4,
		MS_SPECIAL_1 = 5,
		MS_WALK = 6,
		MS_ATTACK_1 = 7,
		MS_NEUTRAL = 8,
		MS_ATTACK_2 = 9,
		MS_RUN = 10,
		MS_SPECIAL_3 = 11,
		MS_SPECIAL_4 = 12,
	};

	struct ModelVariant
	{
		ModelVariant()
		{

		}

		ID3D11ShaderResourceView* GetTexture()
		{
			return m_textures[m_variant]->GetTexture();
		}
		int32_t GetVariant()
		{
			return m_variant;
		}
		float GetMaxFrames()
		{
			return m_maxFrames[m_variant];
		}
		void SetVariant(ModelStance variant)
		{
			this->m_variant = variant;
		}
		void SetVariant(int32_t variant)
		{
			this->m_variant = variant;
		}

		Texture*             m_textures[13];
		float                m_maxFrames[13] = { 8,16,15,5,0,0,8,16,8,0,8,0,0 };
	private:
		int32_t               m_variant;

	};

	Unit();
	~Unit();

	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader, WCHAR* paths,float size, float collision, XMFLOAT3 position,RenderContainerFlags flags,bool wander = true);
	void Resize(ID3D11Device * device, Shader * shader, float resize);
	void PlayAnimation(ModelStance animation);
	void SetAnimation(ModelStance animation);
	void SetAnimationSpeed(float speed);


	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ShaderPackage &shader) override;
	void Update(float dt) override;
	void SetZ(float z = 0.0f) override;
	BoundingSphere* GetBoundingSphere() override;
	void Release() override;

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
	void SetRotations(int32_t rotations);
	void SetRotation(float rotation);
	void SetVelocity(float x, float y, float z);
	void DiscardTasks(); 
	void SetPosition(XMFLOAT3 position);
	void GoBack();

	friend class Task;
	friend class TaskGotoPoint;
	friend class TaskPatrol;
	friend class TaskFollow;
	friend struct RenderObject;
	friend struct SortByX;
	friend struct SortByY;
	friend struct UnitsVector;

private:

	void InitializeModel(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader, ModelPaths* paths);

	float         m_speed[2];
	WalkingStance m_walkingStance;
	TaskQueue     m_tasks;
	bool          m_wanderingFlag;

	ID3D11DeviceContext * m_deviceContext;
	float m_currentFrame;
	float m_previousFrame;

	XMFLOAT4X4   m_worldMatrix;
	XMFLOAT3     m_floats[2];
	float        m_size;
	float        m_lastSize;


	float         m_animationSpeed;
	float         m_currentSpeed;
	float         m_framesPerSecond;
	bool          m_isLooping;
	float         m_rotation;
	VertexBuffer* m_vertexBuffer;
	ModelVariant  m_modelVariant;
	float         m_previousSpeed;
	float         m_rotations;
	int           m_stopped;
	bool          m_stop;		
};

