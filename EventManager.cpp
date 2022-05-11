#include "EventManager.h"

namespace
{
	static EventManager* m_instance;
	static modern_vector<std::string>  m_eventsNames;
	static modern_vector<std::string>   m_foosNames;
	static modern_array<lua_CFunction> m_foos;
	static int32_t    m_event = 0;
	static modern_Boolean m_discard;
}

EventManager::EventManager(lua_State* const lua) : m_lua(lua)
{
	m_instance = this;

	m_eventsNames.push_back("event_do_nothing");


	m_foos.push_back([](lua_State* state){return 0;});
	m_foosNames.push_back("");

	m_eventsNames.push_back("event_dying_unit");

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

	if(event > 0 && event < enum_cast<int32_t>(ENUM_EVENT_TYPE::COUNT))
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

void EventManager::Discard() const noexcept
{
	m_discard++;
}

const modern_Boolean EventManager::EventDyingUnit()
{
	m_discard = false;
	m_event = enum_cast<int32_t>(ENUM_EVENT_TYPE::EVENT_TYPE_DYING_UNIT);
	if (m_foos[m_event])
		m_foos[m_event](m_lua);
	return m_discard;
}

const modern_Boolean EventManager::StartCastingUnit()
{
	m_discard = false;
	m_event = enum_cast<int32_t>(ENUM_EVENT_TYPE::EVENT_TYPE_START_CASTING_UNIT);
	if (m_foos[m_event])
		m_foos[m_event](m_lua);
	return m_discard;
}

EventManager* EventManager::GetInstance()
{
	return m_instance;
}
