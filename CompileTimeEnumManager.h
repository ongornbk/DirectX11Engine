#pragma once
#include "GameObjectType.h"

#include <modern__.h>

enum class IntersectionWithProjectile
{
	INTERSECTION_WITH_PROJECTILE_NONE,
	INTERSECTION_WITH_PROJECTILE_HIT,
	INTERSECTION_WITH_PROJECTILE_BLOCK
};

//Interface
struct GameObjectTypeInterface
{
	inline explicit constexpr GameObjectTypeInterface()
	{

	}

	virtual ~GameObjectTypeInterface()
	{

	}

		virtual const enum class GameObjectType GetType() const modern_except_state
	{
		return GameObjectType::OBJECT_TYPE_UNKNOWN;
	}

	virtual const modern_Boolean  InheritsFromColorFilter() const modern_except_state
	{
		return modern_false;
	}

	virtual const modern_Boolean  IsRendered() const modern_except_state
	{
		return modern_false;
	}

	virtual const enum class IntersectionWithProjectile GetIntersectionWithProjectile() const modern_except_state
	{
		return IntersectionWithProjectile::INTERSECTION_WITH_PROJECTILE_NONE;
	}

	virtual const wchar_t* const GetTypeName() const modern_except_state
	{
		return L"GAMEOBJECT_TYPE_NAME_UNKNOWN";
	}
};

//GameObject
struct GameObjectInfoStruct : public GameObjectTypeInterface
{
	inline explicit constexpr GameObjectInfoStruct()
	{

	}
	
} ;

//Unit
struct UnitInfoStruct : public GameObjectTypeInterface
{
	inline explicit constexpr UnitInfoStruct()
	{

	}

	const enum class GameObjectType GetType() const override modern_except_state
	{
		return GameObjectType::OBJECT_TYPE_UNIT;
	}

	const modern_Boolean  InheritsFromColorFilter() const override modern_except_state
	{
		return modern_true;
	}

	const enum class IntersectionWithProjectile GetIntersectionWithProjectile() const override modern_except_state
	{
		return IntersectionWithProjectile::INTERSECTION_WITH_PROJECTILE_HIT;
	}

	const wchar_t* const GetTypeName() const override modern_except_state
	{
		return L"GAMEOBJECT_TYPE_NAME_UNIT";
	}
};

//Agent
struct AgentInfoStruct : public GameObjectTypeInterface
{
	inline explicit constexpr AgentInfoStruct()
	{

	}

	const enum class GameObjectType GetType() const override modern_except_state
	{
		return GameObjectType::OBJECT_TYPE_AGENT;
	}

	const wchar_t* const GetTypeName() const override modern_except_state
	{
		return L"GAMEOBJECT_TYPE_NAME_AGENT";
	}
};

//Projectile
struct ProjectileInfoStruct : public GameObjectTypeInterface
{
	inline explicit constexpr ProjectileInfoStruct()
	{

	}

	const enum class GameObjectType GetType() const override modern_except_state
	{
		return GameObjectType::OBJECT_TYPE_PROJECTILE;
	}

	const wchar_t* const GetTypeName() const override modern_except_state
	{
		return L"GAMEOBJECT_TYPE_NAME_PROJECTILE";
	}
};

//Tree
struct TreeInfoStruct : public GameObjectTypeInterface
{
	inline explicit constexpr TreeInfoStruct()
	{

	}

	const modern_Boolean  InheritsFromColorFilter() const override modern_except_state
	{
		return modern_true;
	}

	const enum class GameObjectType GetType() const override modern_except_state
	{
		return GameObjectType::OBJECT_TYPE_TREE;
	}

	const enum class IntersectionWithProjectile GetIntersectionWithProjectile() const override modern_except_state
	{
		return IntersectionWithProjectile::INTERSECTION_WITH_PROJECTILE_BLOCK;
	}

	const wchar_t* const GetTypeName() const override modern_except_state
	{
		return L"GAMEOBJECT_TYPE_NAME_TREE";
	}

	virtual const modern_Boolean  IsRendered() const modern_except_state
	{
		return modern_true;
	}
};

//Tree Disabled
struct TreeDisabledInfoStruct : public GameObjectTypeInterface
{
	inline explicit constexpr TreeDisabledInfoStruct()
	{

	}

	const modern_Boolean  InheritsFromColorFilter() const override modern_except_state
	{
		return modern_true;
	}

	const enum class GameObjectType GetType() const override modern_except_state
	{
		return GameObjectType::OBJECT_TYPE_TREE;
	}

	const enum class IntersectionWithProjectile GetIntersectionWithProjectile() const override modern_except_state
	{
		return IntersectionWithProjectile::INTERSECTION_WITH_PROJECTILE_NONE;
	}

	const wchar_t* const GetTypeName() const override modern_except_state
	{
		return L"GAMEOBJECT_TYPE_NAME_TREE_DISABLED";
	}

	virtual const modern_Boolean  IsRendered() const modern_except_state
	{
		return modern_false;
	}

};

//Interface
struct InterfaceInfoStruct : public GameObjectTypeInterface
{
	inline explicit constexpr InterfaceInfoStruct()
	{

	}

	const enum class GameObjectType GetType() const override modern_except_state
	{
		return GameObjectType::OBJECT_TYPE_INTERFACE;
	}

	const modern_Boolean  InheritsFromColorFilter() const override modern_except_state
	{
		return modern_true;
	}

	const wchar_t* const GetTypeName() const override modern_except_state
	{
		return L"GAMEOBJECT_TYPE_NAME_INTERFACE";
	}
};

//Doodads
struct DoodadsInfoStruct : public GameObjectTypeInterface
{
	inline explicit constexpr DoodadsInfoStruct()
	{

	}

	const enum class GameObjectType GetType() const override modern_except_state
	{
		return GameObjectType::OBJECT_TYPE_DOODADS;
	}

	const enum class IntersectionWithProjectile GetIntersectionWithProjectile() const override modern_except_state
	{
		return IntersectionWithProjectile::INTERSECTION_WITH_PROJECTILE_BLOCK;
	}

	const modern_Boolean  InheritsFromColorFilter() const override modern_except_state
	{
		return modern_true;
	}

	const wchar_t* const GetTypeName() const override modern_except_state
	{
		return L"GAMEOBJECT_TYPE_NAME_DOODADS";
	}

};

//AnimatedDoodads
struct AnimatedDoodadsInfoStruct : public GameObjectTypeInterface
{
	inline explicit constexpr AnimatedDoodadsInfoStruct()
	{

	}

	const enum class GameObjectType GetType() const override modern_except_state
	{
		return GameObjectType::OBJECT_TYPE_ANIMATED_DOODADS;
	}

	const enum class IntersectionWithProjectile GetIntersectionWithProjectile() const override modern_except_state
	{
		return IntersectionWithProjectile::INTERSECTION_WITH_PROJECTILE_BLOCK;
	}

	const modern_Boolean  InheritsFromColorFilter() const override modern_except_state
	{
		return modern_true;
	}

	const wchar_t* const GetTypeName() const override modern_except_state
	{
		return L"GAMEOBJECT_TYPE_NAME_ANIMATED_DOODADS";
	}

};

inline struct GameObjectInfoStruct      const GameObjectInfo         = GameObjectInfo;
inline struct UnitInfoStruct            const UnitInfo               = UnitInfo;
inline struct AgentInfoStruct           const AgentInfo              = AgentInfo;
inline struct ProjectileInfoStruct      const ProjectileInfo         = ProjectileInfo;
inline struct TreeInfoStruct            const TreeInfo               = TreeInfo;
inline struct TreeDisabledInfoStruct    const TreeDisabledInfo       = TreeDisabledInfo;
inline struct InterfaceInfoStruct       const InterfaceInfo          = InterfaceInfo;
inline struct DoodadsInfoStruct         const DoodadsInfo            = DoodadsInfo;
inline struct AnimatedDoodadsInfoStruct const AnimatedDoodadsInfo    = AnimatedDoodadsInfo;

extern "C"
{

	const static GameObjectTypeInterface* const GAMEOBJECT_TYPE_GAMEOBJECT_INFO       = &GameObjectInfo;
	const static GameObjectTypeInterface* const GAMEOBJECT_TYPE_UNIT_INFO             = &UnitInfo;
	const static GameObjectTypeInterface* const GAMEOBJECT_TYPE_AGENT_INFO            = &AgentInfo;
	const static GameObjectTypeInterface* const GAMEOBJECT_TYPE_PROJECTILE_INFO       = &ProjectileInfo;
	const static GameObjectTypeInterface* const GAMEOBJECT_TYPE_TREE_INFO             = &TreeInfo;
	const static GameObjectTypeInterface* const GAMEOBJECT_TYPE_TREE_INFO_DISABLED    = &TreeDisabledInfo;
	const static GameObjectTypeInterface* const GAMEOBJECT_TYPE_INTERFACE_INFO        = &InterfaceInfo;
	const static GameObjectTypeInterface* const GAMEOBJECT_TYPE_DOODADS_INFO          = &DoodadsInfo;
	const static GameObjectTypeInterface* const GAMEOBJECT_TYPE_ANIMATED_DOODADS_INFO = &AnimatedDoodadsInfo;
}

