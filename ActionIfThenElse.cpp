#include "ActionIfThenElse.h"

ActionIfThenElse::ActionIfThenElse(
	class ICondition* const __condition,
	class IAction* const __then,
	class IAction* const __else)
	: m_if(__condition), m_then(__then), m_else(__else)
{
}

ActionIfThenElse::~ActionIfThenElse()
{
	if (m_if)
	{
		delete m_if;
		m_if = nullptr;
	}
	if (m_then)
	{
		delete m_then;
		m_then = nullptr;
	}
	if (m_else)
	{
		delete m_else;
		m_else = nullptr;
	}
}

void ActionIfThenElse::execute()
{

}

IAction* const ActionIfThenElse::GetThen()
{
	return m_then;
}

const ActionBehavior ActionIfThenElse::execute_in_array()
{
	if (m_if->CheckCondition())
		return m_then->execute_in_array();
	m_then = m_else;
	return m_else->execute_in_array();
}

const ActionType ActionIfThenElse::GetType()
{
	return ActionType::ACTION_TYPE_IF_THEN_ELSE;
}
