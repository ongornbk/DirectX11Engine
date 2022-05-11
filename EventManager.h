#pragma once
#include "modern/modern_vector.h"
#include "modern/modern_array.h"
#include <string>
#include "LuaManager.h"

enum class ENUM_EVENT_TYPE
{
	EVENT_TYPE_DO_NOTHING,//out!!!
	EVENT_TYPE_DYING_UNIT,
	EVENT_TYPE_START_CASTING_UNIT,
	COUNT
};

class EventManager
{


	lua_State* m_lua = nullptr;

public:
	EventManager(struct lua_State* const lua);

	void RegisterEvent(struct lua_State* const state);
	void Discard() const noexcept;

	const modern_Boolean EventDyingUnit();
	const modern_Boolean StartCastingUnit();

	static EventManager* GetInstance();
};

