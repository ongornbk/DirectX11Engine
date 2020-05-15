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

void* ActionMap::PopPointer()
{
	if (m_stack.empty())
	{
		return nullptr;
	}
	class IParameter* const Itop = m_stack.top();
	switch (Itop->get_type())
	{
	case ParameterType::POINTER:
	{
		class PointerParameter* const top = (class PointerParameter* const)m_stack.top();
		void* const val = top->get();
		delete m_stack.top();
		m_stack.pop();
		return val;
		break;
	}
	default:
	{
		delete m_stack.top();
		m_stack.pop();
		return nullptr;
	}
	}
	
}


BasicParameter::BasicParameterValue ActionMap::PopBasic()
{
	if (m_stack.empty())
	{
		return BasicParameter::BasicParameterValue();
	}
	class BasicParameter* const top = (class BasicParameter* const)m_stack.top();
	const BasicParameter::BasicParameterValue val = top->get();
	delete m_stack.top();
	m_stack.pop();
	return val;
}


void ActionMap::PushPointer(void* const ptr)
{
	m_stack.push(new PointerParameter(ptr));
}

void ActionMap::PushBasic(const float __float__type)
{
	m_stack.push(new BasicParameter(__float__type));
}

void ActionMap::PushBasic(const double __double__type)
{
	m_stack.push(new BasicParameter(__double__type));
}					
					
void ActionMap::PushBasic(const int8 __int8__type)
{
	m_stack.push(new BasicParameter(__int8__type));
}					
					
void ActionMap::PushBasic(const int16 __int16__type)
{		
	m_stack.push(new BasicParameter(__int16__type));
}					
					
void ActionMap::PushBasic(const int32 __int32__type)
{	
	m_stack.push(new BasicParameter(__int32__type));
}					
					
void ActionMap::PushBasic(const int64 __int64__type)
{	
	m_stack.push(new BasicParameter(__int64__type));
}					
					
void ActionMap::PushBasic(const uint8 __uint8__type)
{	
	m_stack.push(new BasicParameter(__uint8__type));
}					
					
void ActionMap::PushBasic(const uint16 __uint16__type)
{	
	m_stack.push(new BasicParameter(__uint16__type));
}					
					
void ActionMap::PushBasic(const uint32 __uint32__type)
{	
	m_stack.push(new BasicParameter(__uint32__type));
}					
					
void ActionMap::PushBasic(const uint64 __uint64__type)
{
	m_stack.push(new BasicParameter(__uint64__type));
}
