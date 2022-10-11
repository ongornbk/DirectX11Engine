#pragma once

enum class GameObjectType
{
	GAMEOBJECT_TYPE_UNKNOWN,
	GAMEOBJECT_TYPE_UNIT,
	GAMEOBJECT_TYPE_AGENT,
	GAMEOBJECT_TYPE_DOODADS,
	GAMEOBJECT_TYPE_ANIMATED_DOODADS,
	GAMEOBJECT_TYPE_INTERFACE,
	GAMEOBJECT_TYPE_LINE_OF_COLLISION_AGENT
};

struct GameObjectTypeInterface
{
	explicit constexpr GameObjectTypeInterface(const enum class GameObjectType type)
		: m_type(enum class GameObjectType(type))
	{

	}
	enum class GameObjectType& m_type;
};

struct GameObjectInfoStruct : public GameObjectTypeInterface
{
	constexpr GameObjectInfoStruct()
		: 
		GameObjectTypeInterface(GameObjectType::GAMEOBJECT_TYPE_UNKNOWN)
	{

	}
	
} ;

struct UnitInfoStruct : public GameObjectTypeInterface
{
	constexpr UnitInfoStruct()
		: 
		GameObjectTypeInterface(GameObjectType::GAMEOBJECT_TYPE_UNIT)
	{

	}

};

struct AgentInfoStruct : public GameObjectTypeInterface
{
	constexpr AgentInfoStruct()
		: 
		GameObjectTypeInterface(GameObjectType::GAMEOBJECT_TYPE_AGENT)
	{

	}
};

static constexpr struct GameObjectInfoStruct GameObjectInfo;
static constexpr struct UnitInfoStruct       UnitInfo;
static constexpr struct AgentInfoStruct      AgentInfo;

extern "C"
{

#define GAMEOBJECT_TYPE_GAMEOBJECT_INFO &GameObjectInfo
#define GAMEOBJECT_TYPE_UNIT_INFO       &UnitInfo
#define GAMEOBJECT_TYPE_AGENT_INFO      &AgentInfo
}

