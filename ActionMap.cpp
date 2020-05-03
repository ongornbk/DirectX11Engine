#include "ActionMap.h"

namespace
{
	static class ActionMap* m_instance = nullptr;
}

ActionMap::ActionMap()
{
}

ActionMap::~ActionMap()
{
	m_fooMap.clear();
}

ActionMap* ActionMap::GetInstance()
{
	if (m_instance)
		return m_instance;
	m_instance = new ActionMap();
	return m_instance;
}

void ActionMap::AddAction(std::function<class IAction*(class ActionMap*)> foo, std::string name)
{
	m_fooMap[name] = foo;
}

std::function<class IAction* (class ActionMap*)> const ActionMap::GetAction(std::string name)
{
	return m_fooMap[name];
}

void* ActionMap::Pop()
{
	void* const top = m_stack.top();
	m_stack.pop();
	return top;
}

void ActionMap::Push(void* const ptr)
{
	m_stack.push(ptr);
}
