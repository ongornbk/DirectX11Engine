#include "Unit.h"
#include "Engine.h"
#include "S_ModelPaths.h"
#include "RendererManager.h"
#include "IPP.h"
#include "ActionAttack.h"
#include "ActionRemoveObject.h"
#include "ActionExecuteActionArray.h"
#include "ActionMessageFront.h"
#include "ActionChangeLayer.h"
#include "ActionWait.h"
#include "ActionWaitUntil.h"
#include "ActionSkipRemainingActions.h"
#include "ActionIfThenElse.h"
#include "ActionApplyColorFilter.h"
#include "ActionPushObject.h"
#include "ActionPushTimer.h"
#include "ActionAddAlpha.h"
#include "ConditionFactory.h"
#include "modern/modern.h"
#include "Timer.h"
#include "UnitTemplate.h"
#include "Projectile.h"
#include "SettingsC.h"

Unit::Unit() :
	ColorFilter(1.f, 1.f, 1.f, 1.f),
	m_scale(1.f, 1.f, 1.f, 1.f),
	m_vertexBuffer(nullptr),
	m_template(nullptr),
	m_isLooping(true),
	m_animationSpeed(30.f),
	m_framesPerSecond(1.f),
	m_currentSpeed(0.f),
	m_stop(false),
	m_rotations(1.f),
	m_dead(false)

{
	m_floats[0] = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	m_floats[1] = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	m_rotation[0] = DEFAULT_ROTATION;
	m_rotation[1] = DEFAULT_ROTATION;

	DirectX::XMStoreFloat4x4(&m_worldMatrix, DirectX::XMMatrixIdentity());
	m_modelVariant.SetVariant(ModelStance::MODEL_STANCE_TOWNNEUTRAL);

	m_attack.range = 1000.f;
	m_attack.active = false;
	m_attack.m_atype = AttackType::ENUM_ATTACK_TYPE_RANGED_PROJECTILE;

	m_tasks.SetOwner(this);
}

Unit::Unit(class Unit* const other) :
	ColorFilter(other->m_colorFilter),
	m_scale(other->m_scale),
	m_vertexBuffer(nullptr),
	m_template(nullptr),
	m_isLooping(true),
	m_animationSpeed(other->m_animationSpeed),
	m_framesPerSecond(other->m_framesPerSecond),
	m_currentSpeed(other->m_currentSpeed),
	m_stop(other->m_stop),
	m_rotations(other->m_rotations),
	m_dead(other->m_dead)

{
	m_floats[0] = DirectX::XMFLOAT3(other->m_floats[0]);
	m_floats[1] = DirectX::XMFLOAT3(other->m_floats[1]);

	m_rotation[0] = DEFAULT_ROTATION;
	m_rotation[1] = DEFAULT_ROTATION;

	DirectX::XMStoreFloat4x4(&m_worldMatrix, DirectX::XMMatrixIdentity());
	m_modelVariant.SetVariant(other->m_modelVariant.GetVariant());

	m_attack.range = other->GetAttack().range;
	m_attack.active = other->GetAttack().active;

	m_tasks.SetOwner(this);
}


Unit::~Unit()
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = NULL;
	}
}

void Unit::Initialize(
	struct ID3D11Device * const device,
	struct ID3D11DeviceContext * const deviceContext,
	class Shader * const shader,
	WCHAR* paths,
	const float modelsize,
	const float collision,
	const struct DirectX::XMFLOAT3& position,
	const bool wander)
{
	//modern_pair<modern_string, modern_string>& sp = modern_string::SplitString(paths, L'.');
	//m_name = sp.first;
	m_name = L"Barbarian";
	std::wstring tmp0 = std::wstring(paths);
	std::string  tmp1 = std::string(tmp0.begin(), tmp0.end());
	struct ModelPaths* const ptr = S_ModelPaths::GetModelPaths(tmp1);

	
	m_rotations = (float)ptr->m_rotations;
	assert(m_rotations >= 1.f);
	if (m_rotations < 1.f)
		m_rotations = 1.f;

	m_size = modelsize;
	m_lastSize = modelsize;
	m_boundingSphere.Radius = collision;
	m_boundingSphere.Center = position;
	m_boundingSphere.Center.x += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;
	m_boundingSphere.Center.y += ((((float)rand()) / (float)RAND_MAX) * 2.0f) - 1.0f;

	InitializeModel(device, deviceContext, shader, ptr);
	m_wanderingFlag = wander;
	m_type = EObject::EObjectType::OBJECT_TYPE_UNIT;
	switch (ptr->m_leaveCorpse)
	{
	case true:
		m_decayType = UnitDecay::ENUM_LEAVE_CORPSE;
		break;
	case false:
		m_decayType = UnitDecay::ENUM_DECAY;
		break;
	}
}

void Unit::Initialize(Unit* const other)
{


	m_rotations = other->m_rotations;
	assert(m_rotations >= 1.f);
	if (m_rotations < 1.f)
		m_rotations = 1.f;

	m_size = other->m_size;
	m_lastSize = other->m_lastSize;
	m_boundingSphere = other->m_boundingSphere;


	InitializeModel(other);
	m_wanderingFlag = other->m_wanderingFlag;
	m_type = other->m_type;
	m_decayType = other->m_decayType;

}

void Unit::Render(
	struct ID3D11DeviceContext* const deviceContext,
	const struct DirectX::XMFLOAT4X4& viewMatrix,
	const struct DirectX::XMFLOAT4X4& projectionMatrix,
	const struct ShaderPackage &shader)
{
	if (m_flags.m_rendering)
	{



		if (m_flags.m_selectable && m_flags.m_selected)
		{

			//RendererManager::GetInstance()->Focus(this,ObjectFocusType::OBJECT_FOCUS_TYPE_SELECT);

			class Shader* const csh = shader.BeginSelect();

			csh->SetShaderParameters(deviceContext, m_modelVariant.GetTexture());
			csh->SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
			m_vertexBuffer->Render(deviceContext);

			//shader.End();
			//shader.BeginStandard();
		}

		class Shader* const csh = shader.BeginStandard();
		
		csh->SetShaderParameters(deviceContext, m_modelVariant.GetTexture());
		csh->SetShaderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
		csh->SetShaderColorParameters(deviceContext, m_colorFilter);
		//csh->SetShaderScaleParameters(deviceContext, m_scale);
		m_vertexBuffer->Render(deviceContext);
		csh->SetShaderColorParameters(deviceContext, XMFLOAT4(1.f,1.f,1.f,1.f));

	}

}

void Unit::PreRender(
	struct ID3D11DeviceContext * const deviceContext,
	const struct DirectX::XMFLOAT4X4 & viewMatrix,
	const struct DirectX::XMFLOAT4X4 & projectionMatrix,
	const struct ShaderPackage & shader
)
{
	if (m_flags.m_rendering && m_flags.m_cast_shadow)
	{

			//shader.standard->End(deviceContext);
			//shader.BeginShadow();

			//const __m128 cameraPosition = Camera::GetCurrentCamera()->GetPosition();//to opt

			const struct DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationZ(-0.8f) * XMLoadFloat4x4(&m_worldMatrix) * DirectX::XMMatrixTranslation(18.f, 10.f, 0.f);
			struct DirectX::XMFLOAT4X4 shadowMatrix;
			DirectX::XMStoreFloat4x4(&shadowMatrix, rotationMatrix);
			
			shader.SetShaderParameters(deviceContext, m_modelVariant.GetTexture());
			shader.SetShaderParameters(deviceContext, shadowMatrix, viewMatrix, projectionMatrix);
			//shader.shadow->SetShaderScaleParameters(deviceContext,m_scale);
			m_vertexBuffer->Render(deviceContext);

			//shader.End();
			//shader.standard->Begin(deviceContext);
	}
}



void Unit::Update(const float dt)
{

	m_flags.m_rendering = validateRendering(m_boundingSphere.Center);

	if (m_dead)
		goto SKIP_BEGIN;

	if (!m_flags.m_blocked)
	{

		if (m_tasks.Update())
		{

		}
		else
		{
			if (m_wanderingFlag)
			{
				m_tasks.Wander(this);
			}
			else
			{
				if (m_stop)
				{

				}
				else
				{
					if (m_attack.active == false)
					{
						SetAnimation(ModelStance::MODEL_STANCE_TOWNNEUTRAL);
						SetVelocity(0.0f, 0.0f, 0.0f);
						Unit::EndRunning();
					}
				}

			}
		}



		if (!m_stop)
		{
			//if (m_modelVariant.Check())
			//{
				//delete m_vertexBuffer;
				//{
				//	m_vertexBuffer = new class VertexBuffer();
				//	float sizexy[2] = { m_size,m_size };
				//	(void)m_vertexBuffer->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(),, sizexy, true);
				//}
				//DirectX::XMMATRIX
			//}
			m_rotation[0] = m_rotation[1];



			m_flags.m_collided = TileMap::CollisionAt(m_boundingSphere.Center);
			if (m_flags.m_collided)
			{
				m_boundingSphere.Center = m_floats[1];
			}
			else
			{
				m_floats[1] = m_boundingSphere.Center;
			}
			struct DirectX::XMFLOAT3 niuPos = modern_xfloat3_sum(m_boundingSphere.Center, modern_xfloat3_multiply(m_floats[0], dt));

			m_flags.m_collided = TileMap::CollisionAt(niuPos);

			if (!m_flags.m_collided)
			{
				m_boundingSphere.Center = niuPos;
			}
		}

	SKIP_BEGIN:

		if (m_flags.m_rendering)
		{

			DirectX::XMStoreFloat4x4(
				&m_worldMatrix,
				DirectX::XMMatrixMultiply(
				DirectX::XMMatrixScaling(m_modelVariant.GetSize(), m_modelVariant.GetSize(), m_modelVariant.GetSize()),
				DirectX::XMMatrixTranslation(
					m_boundingSphere.Center.x,
					m_boundingSphere.Center.y,
					m_boundingSphere.Center.z //- (m_size / 1.5f)
				)
					
				)
			);


			if (m_modelVariant.GetMaxFrames() == 1.f) return;
			if (m_currentFrame < m_modelVariant.GetMaxFrames())
			{
				m_currentSpeed += m_animationSpeed * dt;

				if (m_currentSpeed > m_framesPerSecond)
				{
					m_currentFrame++;
					m_currentSpeed = 0.f;
					if (m_currentFrame >= m_modelVariant.GetMaxFrames())
					{
						if (m_modelVariant.GetVariant() == ModelStance::MODEL_STANCE_DEATH)
						{
							if (m_decayType == UnitDecay::ENUM_DECAY)
							{
								this->Remove();
							}
							else
							{
								//m_modelVariant.SetVariant(ModelStance::MODEL_STANCE_DEAD);
								ForceAnimation(ModelStance::MODEL_STANCE_DEAD);
								m_flags.m_cast_shadow = false;
								//m_isLooping = false;
							}
						}

						if (m_isLooping)
						{
							m_currentFrame = 0.f;
						}
						else
						{
							m_stop = false;
							m_isLooping = true;
							m_currentFrame = 0.f;
							m_previousFrame = -1.f;
							m_modelVariant.SetVariant(m_stopped);
						}
					}

				}
			}
			if (m_currentFrame == m_previousFrame) return;





			struct D3D11_MAPPED_SUBRESOURCE mappedResource;
			struct SpriteVertexType* vertices = m_vertexBuffer->GetVertices();

			vertices[0].uv.x = m_currentFrame / m_modelVariant.GetMaxFrames();
			vertices[0].uv.y = (m_rotation[0] + 1.f) / m_rotations;

			vertices[1].uv.x = m_currentFrame / m_modelVariant.GetMaxFrames();
			vertices[1].uv.y = m_rotation[0] / m_rotations;

			vertices[2].uv.x = (m_currentFrame + 1.f) / m_modelVariant.GetMaxFrames();
			vertices[2].uv.y = m_rotation[0] / m_rotations;

			vertices[3].uv.x = (m_currentFrame + 1.f) / m_modelVariant.GetMaxFrames();
			vertices[3].uv.y = (m_rotation[0] + 1.f) / m_rotations;


//#pragma omp critical
			{
				HRESULT result = m_deviceContext->Map(m_vertexBuffer->GetVertexBuffer(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &mappedResource);
				if (FAILED(result))
				{
					//return;
					//goto EXIT_CRT_0;
				}
				else
				{
					struct SpriteVertexType* const verticesPtr = (struct SpriteVertexType* const)mappedResource.pData;
					memcpy(verticesPtr, (void*)vertices, sizeof(struct SpriteVertexType) * m_vertexBuffer->GetVertexCount());
					m_deviceContext->Unmap(m_vertexBuffer->GetVertexBuffer(), 0);
				}
			//EXIT_CRT_0:
			}
			m_previousFrame = m_currentFrame;
		}
		




	//	float mousePosition[2];
	//	UserInterface::GetMousePosition(mousePosition[0], mousePosition[1]);
	//	DirectX::FXMVECTOR point = XMVectorSet(mousePosition[0],mousePosition[1], 0.0f, 0.0f);
	//	DirectX::BoundingBox select;
	//	select.Center = m_boundingSphere.Center;
	//	select.Center.y += m_size / 4.f;
	//	select.Extents.x = m_size / 2.f;
	//	select.Extents.y = m_size / 2.f;
	//	select.Extents.z = m_size / 2.f;
	//	{
	//		if (select.Contains(point))
	//		{
	//			m_flags.m_selected = true;
	//			GLOBAL m_lastSelectedUnit.make_handle(this->GetHandle());
	//			GLOBAL m_selectStatus = true;
	//		}
	//		else
	//		{
	//			m_flags.m_selected = false;
	//		}
	//	}
	}
	//
	m_intersection = false;
}	


void Unit::SetZ(const float z)
{
	m_boundingSphere.Center.z = z;
}

void Unit::SetTask(class Task* const task)
{
	if(!m_attack.active)
	m_tasks.SetTask(task);
}

void Unit::GiveTask(class Task * const task)
{
	m_tasks.QueueTask(task);
}

void Unit::Release()
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = nullptr;
	}
}

void Unit::Intersect(class EObject* const other)
{
	if (m_intersection == false)
	{
		//m_boundingSphere.Center.x = m_floats[1].x;
		//m_boundingSphere.Center.y = m_floats[1].y;
		{
			if (other->m_flags.m_pushable == false)
				m_stop = false;
		}
		//m_boundingSphere.Center.z = m_floats[1].z;
		if (m_wanderingFlag)
		{
			switch (GetTaskType())
			{
				case Task::Type::TASKGOTOPOINT:
				{
					if (other == nullptr || other == this)
					{
						return;
					}
					if (other->m_type == EObjectType::OBJECT_TYPE_UNIT)
					{
						if (this->IsAttacking() || ((class Unit*)other)->IsDead() || m_stop|| ((class Unit*)other)->m_wanderingFlag == false)
						{
					
						}
						else
						{
							//TaskAttack* task = new TaskAttack();
							//task->object.make_handle(this->GetHandle());
							//task->target.make_handle(other->GetHandle());
							//task->Initialize();
							//m_tasks.SetTask(task);
						}
					}
					else
					{
					m_tasks.Discard();
					}
					break;
				}
			default:
			{
				break;
			}
			}
		}
	}
		m_intersection = true;
		
}

const RenderLayerType Unit::GetLayerType() const noexcept
{
	if (m_dead)
		return RenderLayerType::ENUM_CORPSE_TYPE;
	return RenderLayerType::ENUM_OBJECT_TYPE;
}

void Unit::Remove()
{
	class ActionExecuteActionArray* const action = new ActionExecuteActionArray();
	action->push(new ActionRemoveObject(this));
	Timer::CreateInstantTimer(action);
}

void Unit::SetVector(const DirectX::XMFLOAT3& vec) noexcept
{
	m_floats[0] = vec;
}

DirectX::XMFLOAT3 Unit::GetVector() noexcept
{
	return m_floats[0];
}

float Unit::GetCollisionRadius() const noexcept
{
	return m_boundingSphere.Radius;
}


XMFLOAT3 Unit::GetPosition() const noexcept
{
	return m_boundingSphere.Center;
}

float Unit::GetSpeed() const noexcept
{
	return m_speed[0];
}

float Unit::GetZ() const noexcept
{
	return m_boundingSphere.Center.z;
}

float Unit::GetNumberOfRotations() const noexcept
{
	return m_rotations;
}

float Unit::GetRotation() const noexcept
{
	return m_rotation[0];
}

void Unit::SetSpeed(const float speed)
{
	m_speed[0] = speed;
	m_speed[1] = speed;
}

enum WalkingStance Unit::GetWalkingStance() const noexcept
{
	return m_walkingStance;
}

void Unit::SetWalkingStance(const enum WalkingStance stance)
{
	this->m_walkingStance = stance;
	switch (stance)
	{
	case WalkingStance::WALKING_STANCE_WALK:
		m_speed[0] = m_speed[1] / 2.0f;
		break;
	case WalkingStance::WALKING_STANCE_RUN:
		m_speed[0] = m_speed[1];
		break;
	}
}

void Unit::ChangeWalkingStance()
{
	switch (m_walkingStance)
	{
	case WalkingStance::WALKING_STANCE_RUN:
			m_walkingStance = WalkingStance::WALKING_STANCE_WALK;
			m_speed[0] = m_speed[1] / 2.0f;
			break;
	case WalkingStance::WALKING_STANCE_WALK:
		m_walkingStance = WalkingStance::WALKING_STANCE_RUN;
		m_speed[0] = m_speed[1];
		break;
	}
}

void Unit::SetRotations(const int32 rotations)
{
	(this->m_rotations) = (float)(rotations % (int32_t)m_rotations);
}

void Unit::SetRotation(float rotation)
{
	//m_rotation = rotation;
	m_rotation[1] = (float)((int32_t)rotation % (int32_t)m_rotations);
}

void Unit::ForceRotation(const float rotation)
{
	m_rotation[0] = (float)((int32_t)rotation % (int32_t)m_rotations);
	m_rotation[1] = (float)((int32_t)rotation % (int32_t)m_rotations);
}

void Unit::SetVelocity(const float x,const float y,const float z)
{
	m_floats[0] = { x,y,z };
}



void Unit::DiscardTasks()
{
	m_tasks.Discard();
}

void Unit::SetPosition(const struct DirectX::XMFLOAT3 position)
{
	m_boundingSphere.Center = position;
}

void Unit::GoBack()
{
	m_boundingSphere.Center = m_floats[1];
}

void Unit::Die(Unit* const killer)
{
	//killer == nullptr is correct
	if (m_dead)
		return;
	m_flags.m_selectable = false;
	m_dead = true;
	m_attack.active = false;
	//m_isLooping = false;

	ForceAnimation(ModelStance::MODEL_STANCE_DEATH);
	SetVelocity(0.0f, 0.0f, 0.0f);
	Unit::EndRunning();
	//m_flags.m_cast_shadow = false;
	//m_flags.m_pushable = false;

	class ActionExecuteActionArray* const action = new ActionExecuteActionArray();
	switch(m_decayType)
	{
	case UnitDecay::ENUM_LEAVE_CORPSE:
	{
		class FuzzyExpiringTimer* const fuzz = new FuzzyExpiringTimer();
		fuzz->Initialize(new ActionAddAlpha(this, -0.01), new ActionRemoveObject(this), 1.f);
		action->push(new ActionChangeLayer(this, RenderLayerType::ENUM_CORPSE_TYPE));
		action->push(new ActionWait(10.f));
		action->push(new ActionPushTimer(fuzz));
	}
		break;
	case UnitDecay::ENUM_DECAY:
		action->push(new ActionChangeLayer(this, RenderLayerType::ENUM_CORPSE_TYPE));
		action->push(new ActionWait(2.f));
		action->push(new ActionRemoveObject(this));
		break;
	}
	Timer::CreateInstantTimer(action);
}

const UnitStats& Unit::GetStats()
{
	return m_stats;
}

Attack& Unit::GetAttack()
{
	return m_attack;
}

Task::Type Unit::GetTaskType() const noexcept
{
	return m_tasks.GetActiveType();
}

Task* Unit::GetTask()const noexcept
{
	if (m_tasks.GetActiveType() != Task::Type::NONE)
		return m_tasks.GetActiveTask();
	else return nullptr;
}

bool Unit::IsAttacking() const noexcept
{
	return m_attack.active;
}

bool Unit::IsDead() const noexcept
{
	return m_dead;
}

bool Unit::IsAlive() const noexcept
{
	return !m_dead;
}

bool Unit::BeginAttack(class Unit* const target)
{
	if (m_stop)
	{
		return false;
	}
	if (this->GetLayerType() != target->GetLayerType())
	{
		return false;
	}
	else
	{
		if (target)
		{
		DirectX::XMFLOAT3 position = GetPosition();
		DirectX::XMFLOAT3 destination = target->m_boundingSphere.Center;
		float rotation = atan2(destination.y - position.y, destination.x - position.x) * 180.0f / 3.141f;
		rotation += 90.f;
		rotation /= (360 / m_rotations);
		rotation = m_rotations - rotation;
		SetRotation(rotation);
		//const int32 atkt = ipp::math::RandomInt32(0, 1);
		//if(atkt)
		PlayAnimation(ModelStance::MODEL_STANCE_ATTACK_1);
		//else
		//PlayAnimation(Unit::ModelStance::MS_ATTACK_2);
		SetVelocity(0.0f, 0.0f, 0.0f);
		m_attack.active = true;
		
			class IAction* const action = new ActionAttack(this, target);
			Timer::CreateExpiringTimer(action, m_attack.m_attackDelay);
			
		
		
			

		}
		return true;
	}

}

bool Unit::Attack(class Unit* const target)
{
	switch (m_attack.m_atype)
	{
	case AttackType::ENUM_ATTACK_TYPE_MELEE:
	{
		m_attack.active = false;
		return ((class Unit* const)target)->GetAttacked(this);
		break;
	}
	case AttackType::ENUM_ATTACK_TYPE_RANGED_PROJECTILE:
	{
		m_attack.active = false;

		Engine* const engine = Engine::GetEngine();
			engine->PlaySound(L"attack1_arrow");

		{
			class Projectile* const proj = new Projectile();
			DirectX::XMFLOAT3 f3 = DirectX::XMFLOAT3(0.f, 0.f, 0.f);

			f3 = modern_xfloat3_sub(m_boundingSphere.Center, target->GetPosition());
			const float length = sqrtf((f3.x * f3.x) + (f3.y * f3.y));
			if (length > 0.f)
			{
				f3 = modern_xfloat3_div(f3, length);
				f3 = modern_xfloat3_multiply(f3, -800.f);
			}

			proj->Initialize(
				Engine::GetEngine()->GetGraphics()->GetDevice(),
				Engine::GetEngine()->GetGraphics()->GetDeviceContext(),
				ResourceManager::GetInstance()->GetShaderByName(L"units"),
				L"arrow0",
				32.f,
				25.f,
				m_boundingSphere.Center,
				f3,
				this
			);
			RendererManager::GetInstance()->PushProjectile(proj);

			class IAction* const action = new ActionRemoveObject(proj);
			Timer::CreateExpiringTimer(action, m_attack.range / 800.f);
		}
		{
			class Projectile* const proj = new Projectile();
			DirectX::XMFLOAT3 f3 = DirectX::XMFLOAT3(0.f, 0.f, 0.f);

			f3 = modern_xfloat3_sub(m_boundingSphere.Center, target->GetPosition());
			const float length = sqrtf((f3.x * f3.x) + (f3.y * f3.y));
			if (length > 0.f)
			{
				f3 = modern_xfloat3_div(f3, length);
				f3 = modern_xfloat3_multiply(f3, -800.f);
			}

			f3.x = f3.x * cos(modern_degtorad * 10.f) - f3.y * sin(modern_degtorad * 10.f);
			f3.y = f3.x * sin(modern_degtorad * 10.f) + f3.y * cos(modern_degtorad * 10.f);

			proj->Initialize(
				Engine::GetEngine()->GetGraphics()->GetDevice(),
				Engine::GetEngine()->GetGraphics()->GetDeviceContext(),
				ResourceManager::GetInstance()->GetShaderByName(L"units"),
				L"arrow0",
				32.f,
				25.f,
				m_boundingSphere.Center,
				f3,
				this
			);
			RendererManager::GetInstance()->PushProjectile(proj);

			class IAction* const action = new ActionRemoveObject(proj);
			Timer::CreateExpiringTimer(action, m_attack.range / 800.f);
		}
		{
			class Projectile* const proj = new Projectile();
			DirectX::XMFLOAT3 f3 = DirectX::XMFLOAT3(0.f, 0.f, 0.f);

			f3 = modern_xfloat3_sub(m_boundingSphere.Center, target->GetPosition());
			const float length = sqrtf((f3.x * f3.x) + (f3.y * f3.y));
			if (length > 0.f)
			{
				f3 = modern_xfloat3_div(f3, length);
				f3 = modern_xfloat3_multiply(f3, -800.f);
			}

			f3.x = f3.x * cos(modern_degtorad * -10.f) - f3.y * sin(modern_degtorad * -10.f);
			f3.y = f3.x * sin(modern_degtorad * -10.f) + f3.y * cos(modern_degtorad * -10.f);

			proj->Initialize(
				Engine::GetEngine()->GetGraphics()->GetDevice(),
				Engine::GetEngine()->GetGraphics()->GetDeviceContext(),
				ResourceManager::GetInstance()->GetShaderByName(L"units"),
				L"arrow0",
				32.f,
				25.f,
				m_boundingSphere.Center,
				f3,
				this
			);
			RendererManager::GetInstance()->PushProjectile(proj);

			class IAction* const action = new ActionRemoveObject(proj);
			Timer::CreateExpiringTimer(action, m_attack.range / 800.f);
		}
		{
			class Projectile* const proj = new Projectile();
			DirectX::XMFLOAT3 f3 = DirectX::XMFLOAT3(0.f, 0.f, 0.f);

			f3 = modern_xfloat3_sub(m_boundingSphere.Center, target->GetPosition());
			const float length = sqrtf((f3.x * f3.x) + (f3.y * f3.y));
			if (length > 0.f)
			{
				f3 = modern_xfloat3_div(f3, length);
				f3 = modern_xfloat3_multiply(f3, -800.f);
			}

			f3.x = f3.x * cos(modern_degtorad * 20.f) - f3.y * sin(modern_degtorad * 20.f);
			f3.y = f3.x * sin(modern_degtorad * 20.f) + f3.y * cos(modern_degtorad * 20.f);

			proj->Initialize(
				Engine::GetEngine()->GetGraphics()->GetDevice(),
				Engine::GetEngine()->GetGraphics()->GetDeviceContext(),
				ResourceManager::GetInstance()->GetShaderByName(L"units"),
				L"arrow0",
				32.f,
				25.f,
				m_boundingSphere.Center,
				f3,
				this
			);
			RendererManager::GetInstance()->PushProjectile(proj);

			class IAction* const action = new ActionRemoveObject(proj);
			Timer::CreateExpiringTimer(action, m_attack.range / 800.f);
		}
		{
			class Projectile* const proj = new Projectile();
			DirectX::XMFLOAT3 f3 = DirectX::XMFLOAT3(0.f, 0.f, 0.f);

			f3 = modern_xfloat3_sub(m_boundingSphere.Center, target->GetPosition());
			const float length = sqrtf((f3.x * f3.x) + (f3.y * f3.y));
			if (length > 0.f)
			{
				f3 = modern_xfloat3_div(f3, length);
				f3 = modern_xfloat3_multiply(f3, -800.f);
			}

			f3.x = f3.x * cos(modern_degtorad * -20.f) - f3.y * sin(modern_degtorad * -20.f);
			f3.y = f3.x * sin(modern_degtorad * -20.f) + f3.y * cos(modern_degtorad * -20.f);

			proj->Initialize(
				Engine::GetEngine()->GetGraphics()->GetDevice(),
				Engine::GetEngine()->GetGraphics()->GetDeviceContext(),
				ResourceManager::GetInstance()->GetShaderByName(L"units"),
				L"arrow0",
				32.f,
				25.f,
				m_boundingSphere.Center,
				f3,
				this
			);
			RendererManager::GetInstance()->PushProjectile(proj);

			class IAction* const action = new ActionRemoveObject(proj);
			Timer::CreateExpiringTimer(action, m_attack.range / 800.f);
		}
		return false;
		break;
	}
	}

}

bool Unit::GetAttacked(class Unit* const attacker)
{
	//class ActionExecuteActionArray* const action = new ActionExecuteActionArray();
	//action->push(new ActionMessageFront(this));
	//for (float i = 0.f; i < 1.f; i+= 0.05f)
	//{
	//	action->push(new ActionApplyColorFilter(attacker, DirectX::XMFLOAT4(1.f, i , i, 1.f)));
	//	action->push(new ActionWait(0.01f));
	//}
	//Timer::CreateInstantTimer(action);
	DoDamage(attacker);
	const int32_t ran = modern_random(0, 2);
	Engine* const engine = Engine::GetEngine();
	switch (ran)
	{
	case 0:
		engine->PlaySound(L"attack1");
		break;
	case 1:
		engine->PlaySound(L"attack2");
		break;
	case 2:
		engine->PlaySound(L"attack3");
		break;
	}
	//COMBATTEXT
	{
		//Interface* txt;
		//txt->Initialize()
		//txt.
	}
	if (m_stop || m_dead)
	{
		return false;
	}
	{
		PlayAnimation(ModelStance::MODEL_STANCE_GETHIT);
		SetVelocity(0.0f, 0.0f, 0.0f);
		return true;
	}
}

bool Unit::GetHit(Unit* const hitter)
{
	if (m_stop || m_dead)
	{
		return false;
	}
	{
		PlayAnimation(ModelStance::MODEL_STANCE_GETHIT);
		SetVelocity(0.0f, 0.0f, 0.0f);
		return true;
	}
}

bool Unit::StartCasting(const DirectX::XMFLOAT2 target)
{
	if (m_stop)
	{
		return false;
	}
	else
	{
		DirectX::XMFLOAT3 position = GetPosition();
		float rotation = atan2(target.y - position.y, target.x - position.x) * 180.0f / 3.141f;
		rotation += 90.0f;
		rotation /= (360.f / m_rotations);
		rotation = m_rotations - rotation;
		//SetRotation(rotation);
		ForceRotation(rotation);
		PlayAnimation(ModelStance::MODEL_STANCE_SPECIALCAST);
		SetVelocity(0.0f, 0.0f, 0.0f);
		return true;
	}
}

void Unit::DoDamage(class Unit* const attacker)
{
	m_stats.m_health -= attacker->GetStats().m_attackDamage;
	if (m_stats.m_health > 0.f)
	{

	}
	else
	{
		Die(attacker);
		m_stats.m_health = 0.f;
	}
}

void Unit::Select(modern_Boolean selct)
{
	if (selct)
		{
			m_flags.m_selected = true;
			GLOBAL m_lastSelectedUnit.make_handle(this->GetHandle());
			GLOBAL m_selectStatus = true;
		}
		else
		{
			m_flags.m_selected = false;
		}
}

const float Unit::GetHealth() const noexcept
{
	return m_stats.m_health;
}

const float Unit::GetMaxHealth() const noexcept
{
	return m_stats.m_maxHealth;
}

void Unit::SetFootstepsSound(class ISound * const sound)
{
	//m_footstepsSound = sound;
	//m_footstepsHandle = sound->GetSound();
}

void Unit::BeginRunning()
{
	if (m_footstepsSound)
	{
		if (m_footstepsHandle)
		{
			//if(m_footstepsHandle.)
		//	m_footstepsHandle->stop();
		//	m_footstepsHandle = m_footstepsSound->StartPlaying();
		}
		else
		{
			//m_footstepsHandle = m_footstepsSound->StartPlaying();
		}
	}
}

void Unit::EndRunning()
{
	if (m_footstepsHandle)
	{
		//m_footstepsHandle->stop();
		//m_footstepsHandle = nullptr;
	}
}

void Unit::LoadSounds(WCHAR* path)
{
	//m_sounds.Load(path);
}

void Unit::LoadSounds(std::string* path)
{
}

class ISound * Unit::GetFootstepsSound() const noexcept
{
	return m_footstepsSound;
}

modern_string const& Unit::GetName() noexcept
{
	return m_name;
}

void Unit::Resize(
	struct ID3D11Device * const device,
	class Shader * const shader,
	const float resize
)
{
	m_size *= resize;
	float sizexy[2] = { m_size,m_size };
	(void)m_vertexBuffer->Initialize(device, shader, sizexy, true);
}

void Unit::PlayAnimation(
	const enum ModelStance animation
)
{
	if (m_flags.m_rendering&&!m_stop)
	{
		m_currentFrame = 0.0f;
		m_previousFrame = -1.0f;
		m_stopped = m_modelVariant.GetVariant();
		m_modelVariant.SetVariant(animation);
		m_isLooping = false;
		m_stop = true;

		//switch (animation)
		//{
		//case	ModelStance::MODEL_STANCE_ATTACK_1:
		//	m_attack.active = true;
		//	break;
		//case	ModelStance::MODEL_STANCE_ATTACK_2:
		//	m_attack.active = true;
		//	break;
		//
		//
		//default:
		//	m_attack.active = false;
		//	break;
		//}
	}

	
}

void Unit::SetAnimation(
	const enum ModelStance animation
)
{
	if (m_flags.m_rendering && !m_stop&&(animation!=m_modelVariant.GetVariant()))
	{
		m_currentFrame = 0.0f;
		m_previousFrame = -1.0f;
		m_modelVariant.SetVariant(animation);
	}
}

void Unit::ForceAnimation(const ModelStance animation)
{
	m_currentFrame = 0.0f;
	m_previousFrame = -1.0f;
	m_modelVariant.SetVariant(animation);
}

void Unit::SetAnimationSpeed(
	const float speed
)
{
	m_previousSpeed = m_animationSpeed;
	m_animationSpeed = speed;
}

int32 Unit::isReleased() const noexcept
{
	if (m_vertexBuffer)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

bool Unit::CheckIfValid(Unit* const pointer)
{
	if (pointer)
		if (pointer->m_type == EObject::EObjectType::OBJECT_TYPE_UNIT)
			return true;
	return false;
}

void Unit::InitializeModel(
	struct ID3D11Device * const device,
	struct ID3D11DeviceContext * const deviceContext,
	class Shader * const shader,
	struct ModelPaths * const paths
)
{
	{
		m_vertexBuffer = new class VertexBuffer();
		float sizexy[2] = { m_size,m_size };
		(void)m_vertexBuffer->Initialize(device, shader, sizexy, true);
	}

	for (int32_t i = 0; i < 15; i++)
	{
		m_modelVariant.m_maxFrames[i] = (float)paths->m_frames[i];
		m_modelVariant.m_sizes[i] = (float)paths->m_sizes[i];
		//std::cout << modern_cstring((int)m_modelVariant.m_sizes[i]).c_str() << std::endl;
	}

	


	if (paths->ATTACK_1 != NULL)
	{
		std::wstring tmp0 = std::wstring(paths->ATTACK_1);
		std::string tmp1 = std::string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[0] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}

	if (paths->ATTACK_2 != NULL)
	{
		std::wstring tmp0 = std::wstring(paths->ATTACK_2);
		std::string tmp1 = std::string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[1] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}

	if (paths->GETHIT != NULL)
	{
		std::wstring tmp0 = std::wstring(paths->GETHIT);
		std::string tmp1 = std::string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[2] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}

	if (paths->KICK != NULL)
	{
		std::wstring tmp0 = std::wstring(paths->KICK);
		std::string tmp1 = std::string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[3] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	if (paths->NEUTRAL != NULL)
	{
		std::wstring tmp0 = std::wstring(paths->NEUTRAL);
		std::string tmp1 = std::string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[4] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	if (paths->RUN != NULL)
	{
		std::wstring tmp0 = std::wstring(paths->RUN);
		std::string tmp1 = std::string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[5] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	if (paths->SPECIALCAST != NULL)
	{
		std::wstring tmp0 = std::wstring(paths->SPECIALCAST);
		std::string tmp1 = std::string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[6] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	if (paths->SPECIAL_1 != NULL)
	{
		std::wstring tmp0 = std::wstring(paths->SPECIAL_1);
		std::string tmp1 = std::string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[7] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	if (paths->SPECIAL_2 != NULL)
	{
		std::wstring tmp0 = std::wstring(paths->SPECIAL_2);
		std::string tmp1 = std::string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[8] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	if (paths->SPECIAL_3 != NULL)
	{
		std::wstring tmp0 = std::wstring(paths->SPECIAL_3);
		std::string tmp1 = std::string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[9] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	if (paths->TOWNNEUTRAL != NULL)
	{
		std::wstring tmp0 = std::wstring(paths->TOWNNEUTRAL);
		std::string tmp1 = std::string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[10] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	if (paths->TOWNWALK != NULL)
	{
		std::wstring tmp0 = std::wstring(paths->TOWNWALK);
		std::string tmp1 = std::string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[11] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	if (paths->WALK != NULL)
	{
		std::wstring tmp0 = std::wstring(paths->WALK);
		std::string tmp1 = std::string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[12] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	if (paths->DEATH != NULL)
	{
		std::wstring tmp0 = std::wstring(paths->DEATH);
		std::string tmp1 = std::string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[13] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}
	if (paths->DEAD != NULL)
	{
		std::wstring tmp0 = std::wstring(paths->DEAD);
		std::string tmp1 = std::string(tmp0.begin(), tmp0.end());
		m_modelVariant.m_textures[14] = ResourceManager::GetInstance()->GetTextureByName((char*)tmp1.c_str());
	}


	{
		m_deviceContext = deviceContext;
		m_currentFrame = 0.0f;
		m_previousFrame = -1.0f;
	}

}

void Unit::InitializeModel(Unit* const other)
{
	{
		m_vertexBuffer = new class VertexBuffer();
		float sizexy[2] = { m_size,m_size };
		(void)m_vertexBuffer->Initialize(m_vertexBuffer);
	}

	for (int32_t i = 0; i < 15; i++)
	{
		m_modelVariant.m_maxFrames[i] = other->m_modelVariant.m_maxFrames[i];
		m_modelVariant.m_sizes[i] = other->m_modelVariant.m_sizes[i];
	}

	m_modelVariant.m_textures[0] = other->m_modelVariant.m_textures[0];
	m_modelVariant.m_textures[1] = other->m_modelVariant.m_textures[1];
	m_modelVariant.m_textures[2] = other->m_modelVariant.m_textures[2];
	m_modelVariant.m_textures[3] = other->m_modelVariant.m_textures[3];
	m_modelVariant.m_textures[4] = other->m_modelVariant.m_textures[4];
	m_modelVariant.m_textures[5] = other->m_modelVariant.m_textures[5];
	m_modelVariant.m_textures[6] = other->m_modelVariant.m_textures[6];
	m_modelVariant.m_textures[7] = other->m_modelVariant.m_textures[7];
	m_modelVariant.m_textures[8] = other->m_modelVariant.m_textures[8];
	m_modelVariant.m_textures[9] = other->m_modelVariant.m_textures[9];
	m_modelVariant.m_textures[10] = other->m_modelVariant.m_textures[10];
	m_modelVariant.m_textures[11] = other->m_modelVariant.m_textures[11];
	m_modelVariant.m_textures[12] = other->m_modelVariant.m_textures[12];
	m_modelVariant.m_textures[13] = other->m_modelVariant.m_textures[13];
	m_modelVariant.m_textures[14] = other->m_modelVariant.m_textures[14];



	{
		m_deviceContext = other->m_deviceContext;
		m_currentFrame = other->m_currentFrame;
		m_previousFrame = other->m_previousFrame;
	}
}



