#pragma once
#include "Sprite.h"
#include "CollisionCircle.h"

class SuperModel : public CollisionCircle
{
public:

	enum RenderElements
	{
	RHEAD1 = 0,
	RHEAD2 = 1,
	RHEAD3 = 2
	};

	enum Gender
	{
		MALE,
		FEMALE
	};

	enum Head
	{
		HEAD1,
		HEAD2,
		HEAD3
	};

	enum Armor
	{
		CLOTH,
		LEATHER,
		STEEL
	};

	enum Melee_Weapon
	{
		DAGGER,
		SHORTSWORD,
		LONGSWORD,
		GREATSWORD
	};

	enum Ranged_Weapon
	{
		SLINGSHOT,
		SHORTBOW,
		LONGBOW,
		GREATBOW,
	};

	enum Magic_Weapon
	{
		WAND,
		ROD,
		STAFF,
		GREATSTAFF
	};

	enum Shield
	{
		BUCKLER,
		SHIELD
	};

	enum ModelStance
	{
		STANCE = 0,
		RUNNING = 1,
		MELEE_SWING = 2,
		BLOCK = 3,
		HIT_AND_DIE = 4,
		CAST_SPELL = 5,
		SHOOT_BOW = 6
	};



	struct Weapon
	{
		union
		{
			Melee_Weapon  m_melee;
			Magic_Weapon  m_magic;
			Ranged_Weapon m_ranged;
		};

		enum
		{
			MELEE,
			MAGIC,
			RANGED
		} m_weaponType;
	};

	struct ModelEquipmentAndGender
	{
		Gender m_gender;
		Head   m_head;
		Armor  m_armor;
		Weapon m_weapon;
		Shield m_shield;
	};

	//struct ModelAsset
	//{
	//	ModelPart Head;
	//	ModelPart Weapon;
	//	ModelPart Shield;
	//	ModelPart Armor;
	//};

	SuperModel(ModelEquipmentAndGender model,float size);
	~SuperModel();

	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader);
	void Update(float dt = 0.0f);
	void Render(XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);
	void SetRotation(uint16_t rotation);

	static void InitializeTextures();


private:


	VertexBuffer*            m_vertexBuffer = nullptr;
	ModelStance              m_stance = STANCE;
	ModelEquipmentAndGender  m_equipmentAndGender;

	XMFLOAT4X4               m_worldMatrix;
	XMFLOAT3                 m_velocity;
	XMFLOAT3                 m_lastPosition;


	float         m_size;
	float         m_previousSpeed;
	uint16_t      m_rotations;
	bool          m_stop;

	float m_currentFrame;
	float m_previousFrame;


	float         m_animationSpeed;
	float         m_currentSpeed;
	float         m_framesPerSecond;
	bool          m_isLooping;
	float         m_rotation;

public:

	struct
	{
		bool  f_rendering = true;
		bool  f_selected = false;
		bool  f_pushable = true;
		bool  f_blocked = false;
		bool  f_collisionWithTilemap = true;
		bool  f_locked = false;
	};

};

