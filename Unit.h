#pragma once
#include "AttackTarget.h"
#include "S_ModelPaths.h"
#include "Sprite.h"
#include "Sound.h"
#include "Attack.h"
#include "UnitStats.h"

#include "WalkingStance.h"
#include "ModelStance.h"
#include "UnitDefaults.h"
#include "UnitDecay.h"
#include "ColorFilter.h"
#include "ModelVariant.h"

#define COLOR_FILTER_NOCHANGE -1.f

class UnitTemplate;

class Unit : public EObject, public ColorFilter
{
public:

	Unit();
	explicit Unit(class Unit* const other);
	~Unit();

	[[DEPRECATED]]
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

	void Initialize(
		struct ID3D11Device* const device,
		struct ID3D11DeviceContext* const deviceContext,
		class Shader* const shader,
		const char* const paths,
		const float size,
		const float collision,
		const struct DirectX::XMFLOAT3& position,
		const bool wander = true
	);

	void Initialize(class Unit* const other);

	void Resize(struct ID3D11Device * const device,class Shader * const shader,const float resize);
	void PlayAnimation(const enum ModelStance animation);
	void SetAnimation(const enum ModelStance animation);
	void ForceAnimation(const enum ModelStance animation);
	void SetAnimationSpeed(float speed);
	int32 isReleased() const modern_except_state override;
	
	_Use_decl_annotations_
	void _fastcall Render(
		struct _In_ ID3D11DeviceContext* const deviceContext,
		const struct _In_ DirectX::XMFLOAT4X4& viewMatrix,
		const struct _In_ DirectX::XMFLOAT4X4& projectionMatrix,
		const struct _In_ ShaderPackage &shader
	) override;

	_Use_decl_annotations_
	void _fastcall PreRender(
		struct ID3D11DeviceContext* const deviceContext,
		const struct _In_ DirectX::XMFLOAT4X4& viewMatrix,
		const struct _In_ DirectX::XMFLOAT4X4& projectionMatrix,
		const struct ShaderPackage &shader
	) override;
	void Update(const float dt) override;
	void SetZ(const float z = 0.0f) override;
	void Release() override;
	void Intersect(class EObject* const other) override;
	const enum class RenderLayerType GetLayerType() const modern_except_state override;
	void Remove() override;
	void SetVector(const DirectX::XMFLOAT3& vec) modern_except_state override;
	DirectX::XMFLOAT3 GetVector() modern_except_state override;

	void SetTask(class Task* const task);
	void GiveTask(class Task* const task);

	float    GetCollisionRadius() const modern_except_state;

	DirectX::XMFLOAT3 GetPosition() const modern_except_state;
	float    GetSpeed() const modern_except_state;
	float GetZ() const modern_except_state;
	float GetNumberOfRotations() const modern_except_state;
	float GetRotation() const modern_except_state;
	void SetSpeed(const float speed = 0.0f);
	WalkingStance GetWalkingStance() const modern_except_state;
	void SetWalkingStance(const enum WalkingStance stance = WalkingStance::WALKING_STANCE_RUN);
	void ChangeWalkingStance();
	void SetRotations(const int32 rotations);
	void SetRotation(const float rotation);
	void ForceRotation(const float rotation);
	void SetVelocity(const float x,const float y,const float z);
	void DiscardTasks(); 
	void SetPosition(const XMFLOAT3 position);
	void GoBack();
	void Die(class Unit* const killer);
	void ApplyExperienceBonus(class Unit* const killer);
	void SetAttackType(const enum class AttackType type) modern_except_state;
	void SetAttackRange(const float range) modern_except_state;

	const UnitStats& GetStats();

	Attack& GetAttack();

	enum Task::Type GetTaskType() const modern_except_state;
	class Task* GetTask() const modern_except_state;

	bool IsAttacking() const modern_except_state;
	bool IsDead() const modern_except_state;
	bool IsAlive() const modern_except_state;
	bool IsWandering() const modern_except_state;

	bool BeginAttack(class Unit* const target);
	bool Attack(class Unit* const target);
	bool GetAttacked(class Unit* const attacker);
	bool GetHit(class Unit* const hitter);
	bool StartCasting(const DirectX::XMFLOAT2 target);
	void DoDamage(class Unit* const attacker);
	void Damage(const float damage);
	void Select(modern_Boolean selct = 1);

	const float GetHealth() const modern_except_state;
	const float GetMaxHealth() const modern_except_state;
	const float GetHealthPercentage() const modern_except_state;

	const float GetMana() const modern_except_state;
	const float GetMaxMana() const modern_except_state;
	const float GetManaPercentage() const modern_except_state;

	const float GetExperience() const modern_except_state;
	const float GetMaxExperience() const modern_except_state;
	const float GetExperiencePercentage() const modern_except_state;

	void SetFootstepsSound(class ISound* sound);

	void NotifyBlock(class EObject* const other);

	void BeginRunning();
	void EndRunning();

	void LoadSounds(WCHAR* path);
	void LoadSounds(std::string* path);

	class ISound* GetFootstepsSound() const modern_except_state;
	[[nodiscard]] class modern_string const& GetName() modern_except_state;

	friend class Task;
	friend class TaskGotoPoint;
	friend class TaskPatrol;
	friend class TaskFollow;
	friend class TaskAttack;
	friend struct RenderObject;
	friend struct SortByX;
	friend struct SortByY;
	friend struct UnitsVector;

	[[nodiscard]] static const modern_Boolean CheckIfValid(class Unit* const pointer);

private:

	void InitializeModel(
		ID3D11Device* device,
		ID3D11DeviceContext* deviceContext,
		class Shader* shader,
		struct ModelPaths* paths
	);

	void InitializeModel(class Unit* const other);

	void AnimationEnd();

	float                m_speed[2];
	enum  WalkingStance  m_walkingStance;
	enum class UnitDecay m_decayType;
	class TaskQueue      m_tasks;
	
	class ISound*         m_footstepsSound{};
	class sf::Sound*     m_footstepsHandle{};
	class UnitTemplate*  m_template;

	class modern_string m_name;

	struct ID3D11DeviceContext * m_deviceContext;

	float m_currentFrame;
	float m_previousFrame;

	struct DirectX::XMFLOAT4X4   m_worldMatrix;
	struct DirectX::XMFLOAT3     m_floats[2];
	struct DirectX::XMFLOAT4     m_scale;
	class VertexBuffer* m_vertexBuffer;
	struct ModelVariant m_modelVariant;
	float        m_size;
	float        m_lastSize;


	float               m_animationSpeed;
	float               m_currentSpeed;
	float               m_framesPerSecond;

	float               m_rotation[2];

	float               m_previousSpeed;
	float               m_rotations;
	float               m_rad_rotation;
	int                 m_stopped;
	bool                m_stop;
	bool                m_intersection;
	bool                m_dead;
	bool                m_wanderingFlag;
	bool                m_isLooping;

	
	struct UnitStats     m_stats;
	struct Attack        m_attack;

	//class UnitSounds m_sounds;
};

