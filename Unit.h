#pragma once
#include "AttackTarget.h"
#include "S_ModelPaths.h"
#include "Sprite.h"
#include "Sound.h"
#include "Attack.h"

#pragma region

#pragma endregion

#define COLOR_FILTER_NOCHANGE -1.f

class Unit : public EObject
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
			ZeroMemory(m_textures, sizeof(Texture*) * 13);
			m_variant = 0;
		}

		ID3D11ShaderResourceView* GetTexture() const
		{
			return m_textures[m_variant]->GetTexture();
		}
		int32 GetVariant() const noexcept
		{
			return m_variant;
		}
		float GetMaxFrames() const noexcept
		{
			return m_maxFrames[m_variant];
		}
		void SetVariant(const enum ModelStance variant = ModelStance::MS_NEUTRAL)const noexcept
		{
			this->m_variant = variant;
		}
		void SetVariant(const int32 variant) const
		{
			this->m_variant = variant;
		}

		Texture*             m_textures[13];
		float                m_maxFrames[13] = { 8,16,15,5,0,0,8,16,8,0,8,0,0 };
	private:
		mutable int32                m_variant;

	};

	Unit();
	~Unit();

	void Initialize(
		struct ID3D11Device* const device,
		struct ID3D11DeviceContext* const deviceContext,
		class Shader* const shader,
		WCHAR* paths,
		const float size,
		const float collision,
		const struct DirectX::XMFLOAT3 &position,
		const bool wander = true
	);
	void Resize(struct ID3D11Device * const device,class Shader * const shader,const float resize);
	void PlayAnimation(const enum ModelStance animation);
	void SetAnimation(const enum ModelStance animation);
	void SetAnimationSpeed(float speed);
	int32 isReleased() const noexcept override;

	void Render(
		struct ID3D11DeviceContext* const deviceContext,
		const struct XMFLOAT4X4& viewMatrix,
		const struct XMFLOAT4X4& projectionMatrix,
		const struct ShaderPackage &shader
	) override;
	void PreRender(
		struct ID3D11DeviceContext* const deviceContext,
		const struct DirectX::XMFLOAT4X4& viewMatrix,
		const struct DirectX::XMFLOAT4X4& projectionMatrix,
		const struct ShaderPackage &shader
	) override;
	void Update(const float dt) override;
	void SetZ(const float z = 0.0f) override;
	void Release() override;

	void SetTask(class Task* const task);
	void GiveTask(class Task* const task);

	float    GetCollisionRadius() const noexcept;

	DirectX::XMFLOAT3 GetPosition() const noexcept;
	float    GetSpeed() const noexcept;
	float GetZ() const noexcept;
	void SetSpeed(const float speed = 0.0f);
	WalkingStance GetWalkingStance() const noexcept;
	void SetWalkingStance(const enum WalkingStance stance = WalkingStance::WS_RUN);
	void ChangeWalkingStance();
	void SetRotations(const int32 rotations);
	void SetRotation(const float rotation);
	void SetVelocity(const float x,const float y,const float z);
	void SetColorFilter(const float redfilter, const float greenfilter, const float bluefilter, const float alphafilter) noexcept;
	void SetColorFilter(const struct DirectX::XMFLOAT4& color) noexcept;
	void DiscardTasks(); 
	void SetPosition(const XMFLOAT3 position);
	void GoBack();

	Attack& GetAttack();

	enum Task::Type GetTaskType() const noexcept;
	class Task* GetTask() const noexcept;

	bool IsAttacking() const noexcept;

	bool Attack(class EObject* const target);
	bool GetAttacked(class EObject* const attacker);
	bool StartCasting(const DirectX::XMFLOAT2 target);

	void SetFootstepsSound(class Sound* sound);

	void BeginRunning();
	void EndRunning();

	void LoadSounds(WCHAR* path);
	void LoadSounds(std::string* path);

	class Sound* GetFootstepsSound() const noexcept;

	friend class Task;
	friend class TaskGotoPoint;
	friend class TaskPatrol;
	friend class TaskFollow;
	friend class TaskAttack;
	friend struct RenderObject;
	friend struct SortByX;
	friend struct SortByY;
	friend struct UnitsVector;

private:

	void InitializeModel(
		ID3D11Device* device,
		ID3D11DeviceContext* deviceContext,
		class Shader* shader,
		struct ModelPaths* paths
	);

	float               m_speed[2];
	enum  WalkingStance m_walkingStance;
	class TaskQueue     m_tasks;
	bool                m_wanderingFlag;
	class Sound*        m_footstepsSound{};
	class sf::Sound*    m_footstepsHandle{};

	struct ID3D11DeviceContext * m_deviceContext;
	struct DirectX::XMFLOAT4     m_colorFilter;;
	float m_currentFrame;
	float m_previousFrame;

	struct DirectX::XMFLOAT4X4   m_worldMatrix;
	struct DirectX::XMFLOAT3     m_floats[2];
	struct DirectX::XMFLOAT4     m_scale;
	float        m_size;
	float        m_lastSize;


	float         m_animationSpeed;
	float         m_currentSpeed;
	float         m_framesPerSecond;
	bool          m_isLooping;
	float         m_rotation;
	class VertexBuffer* m_vertexBuffer;
	struct ModelVariant  m_modelVariant;
	float         m_previousSpeed;
	float         m_rotations;
	int           m_stopped;
	bool          m_stop;		

	struct Attack        m_attack;

	//class UnitSounds m_sounds;
};

