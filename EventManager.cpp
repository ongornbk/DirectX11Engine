#include "EventManager.h"
#include "Global.h"
#include "Region.h"
#include "ActionExecuteActionArray.h"
#include "ActionExecuteLuaFunction.h"
#include "ActionGlobalSetLeavingObject.h"
#include "Timer.h"

namespace
{
	static EventManager* m_instance;
	static modern_vector<std::string>  m_eventsNames;
	static modern_vector<std::string>   m_foosNames;
	//static std::vector<std::string>  m_eventsNames;
	//static std::vector<std::string>  m_foosNames;
	static modern_array<lua_CFunction> m_foos;
	//static modern_array<IAction*> m_postSort;
	static int32_t    m_event = 0;
	static modern_Boolean m_discard;
}

EventManager::EventManager(struct lua_State* const lua) : m_lua(lua)
{
	m_instance = this;

	m_eventsNames.push_back("event_do_nothing");


	m_foos.push_back([](lua_State* state){return 0;});
	m_foosNames.push_back("");

	m_eventsNames.push_back("event_dying_unit");
	m_eventsNames.push_back("event_start_casting_unit");
	m_eventsNames.push_back("event_select_unit");
	m_eventsNames.push_back("event_levelup_unit");

	for (int32_t i = 1; i < enum_cast<int32_t>(ENUM_EVENT_TYPE::COUNT); i++)
	{
		m_foos.push_back(nullptr);
		m_foosNames.push_back("");
	}
}

void EventManager::RegisterEvent(lua_State* const state)
{
	lua_Integer event = lua_tointeger(state, 1);
	std::string foo_name = lua_tostring(state, 2);

	if(event > 0ll && event < enum_cast<int64_t>(ENUM_EVENT_TYPE::COUNT))
	{
		m_foosNames[event] = foo_name;
		m_foos[event] = [](lua_State* state)
		{
			lua_pcall(state, 0, 0, 0);
			lua_getglobal(state, m_foosNames[m_event].c_str());
			lua_pcall(state, 0, 0, 0);
			return 0;
		};
	}
}

void EventManager::Discard() const modern_except_state
{
	m_discard++;
}

//void EventManager::PostSort()
//{
//	for (auto& action : m_postSort)
//	{
//		action->execute();
//		delete action;
//		action = nullptr;
//	}
//	m_postSort.clear();
//}

const modern_Boolean EventManager::EventDyingUnit()
{
	m_discard = modern_false;
	m_event = enum_cast<int32_t>(ENUM_EVENT_TYPE::EVENT_TYPE_DYING_UNIT);
	if (m_foos[m_event])
		m_foos[m_event](m_lua);
	return m_discard;
}

const modern_Boolean EventManager::EventStartCastingUnit()
{
	m_discard = modern_false;
	m_event = enum_cast<int32_t>(ENUM_EVENT_TYPE::EVENT_TYPE_START_CASTING_UNIT);
	if (m_foos[m_event])
		m_foos[m_event](m_lua);
	return m_discard;
}

const modern_Boolean EventManager::EventSelectUnit()
{
	m_discard = modern_false;
	m_event = enum_cast<int32_t>(ENUM_EVENT_TYPE::EVENT_TYPE_SELECT_UNIT);
	if (m_foos[m_event])
		m_foos[m_event](m_lua);
	return m_discard;
}

const modern_Boolean EventManager::EventLevelUpUnit()
{
	m_discard = modern_false;
	m_event = enum_cast<int32_t>(ENUM_EVENT_TYPE::EVENT_TYPE_LEVELUP_UNIT);
	if (m_foos[m_event])
		m_foos[m_event](m_lua);
	return m_discard;
}

const modern_Boolean EventManager::EventRegionEntering()
{
	class Region* const region = (class Region* const)Global::GetInstance()->m_triggeringRegion.get();
	m_discard = modern_false;
	//if (region->m_eventEntersBindStatus)
	//{
		lua_pcall(m_lua, 0, 0, 0);
		lua_getglobal(m_lua, region->m_eventEnters.c_str());
		lua_pcall(m_lua, 0, 0, 0);
		
	//}

	//class ActionExecuteActionArray* const def_actions_array = new class ActionExecuteActionArray();
	//def_actions_array->push(new class ActionExecuteLuaFunction(m_lua,modern_cstring(region->m_eventEnters.c_str())));
	//Timer::CreateInstantTimer(def_actions_array);

	return m_discard;
}

const modern_Boolean EventManager::EventRegionLeaving()
{
	class Region* const region = (class Region* const)Global::GetInstance()->m_triggeringRegion.get();
	m_discard = modern_false;
	//if (region->m_eventLeavesBindStatus)
	//{
		lua_pcall(m_lua, 0, 0, 0);
		lua_getglobal(m_lua, region->m_eventLeaves.c_str());
		lua_pcall(m_lua, 0, 0, 0);
	//}

	
	//m_postSort.push_back(new class ActionGlobalSetLeavingObject(Global::GetInstance()->m_leavingObject));
	//m_postSort.push_back(new class ActionExecuteLuaFunction(m_lua, modern_cstring(region->m_eventLeaves.c_str())));
	return m_discard;
}

EventManager* EventManager::GetInstance()
{
	return m_instance;
}
