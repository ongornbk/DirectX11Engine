#pragma once
#include "Sprite.h"
#include "RenderModel.h"

class SuperModel : RenderModel
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
		GRATSTAFF
	};

	enum Shield
	{
		BUCKLER,
		SHIELD
	};

	enum ModelStance
	{
		STANCE,
		RUNNING,
		MELEE_SWING,
		BLOCK,
		HIT_AND_DIE,
		CAST_SPELL,
		SHOOT_BOW
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

	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader, WCHAR* filename);
	void Update(float dt = 0.0f);
	void Render(XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);

	static void InitializeTextures();


private:



	ModelStance             m_stance;
	ModelEquipmentAndGender m_equipmentAndGender;


	float         m_size;
	float         m_previousSpeed;
	float         m_rotations;
	int           m_stopped;
	bool          m_stop;

	float m_currentFrame;
	float m_previousFrame;


	float         m_animationSpeed;
	float         m_currentSpeed;
	float         m_framesPerSecond;
	bool          m_isLooping;
	float         m_rotation;
};

