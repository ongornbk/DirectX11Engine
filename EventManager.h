#pragma once
#include <string>
#include "LuaManager.h"

#include <modern__.h>

enum class ENUM_EVENT_TYPE
{
	EVENT_TYPE_DO_NOTHING,//out!!!
	EVENT_TYPE_DYING_UNIT,
	EVENT_TYPE_START_CASTING_UNIT,
	EVENT_TYPE_SELECT_UNIT,
	EVENT_TYPE_LEVELUP_UNIT,
	COUNT
};

class EventManager
{


	lua_State* m_lua = nullptr;

public:
	EventManager(struct lua_State* const lua);

	void RegisterEvent(struct lua_State* const state);
	void Discard() const modern_except_state;
	//void PostSort();

	const modern_Boolean EventDyingUnit();
	const modern_Boolean EventStartCastingUnit();
	const modern_Boolean EventSelectUnit();
	const modern_Boolean EventLevelUpUnit();
	const modern_Boolean EventRegionEntering();
	const modern_Boolean EventRegionLeaving();

	static EventManager* GetInstance();
};

