#include "ActionExecuteActionArray.h"
#include "ActionIfThenElse.h"
#include "IActionSplitArrayBehavior.h"
#include "GarbageCollector.h"
#include "IActionTimer.h"
#include "IActionCondition.h"
#include "Timer.h"

#include <modern__.h>

ActionExecuteActionArray::ActionExecuteActionArray()
{
}

ActionExecuteActionArray::~ActionExecuteActionArray()
{
	for (auto&& ele : m_actions)
	{
		//GarbageCollector::GetInstance()->AsyncDelete(ele);
		delete ele;
		ele = nullptr;
	}
}

void ActionExecuteActionArray::push(class IAction* const action)
{
	assert(action);
	if (action)
		m_actions.push_back(action);
}

void ActionExecuteActionArray::execute()
{
	for (size_t i = 0ull; i < m_actions.size(); i++)
	{
		class IAction* volatile currentAction = m_actions[i];
		REPEAT_SWITCH:
		switch (currentAction->execute_in_array())
		{
		case ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH:
			break;
		case ActionBehavior::ACTION_BEHAVIOR_SPLITARRAY:
			switch (dynamic_cast<class IActionSplitArrayBehavior*>(currentAction)->GetType())
			{
			case ActionType::ACTION_TYPE_TIMER:
			{



				class ActionExecuteActionArray* const action = new ActionExecuteActionArray();
				for (int32_t j = i+1ull; j < m_actions.size(); j++)
				{
					action->push(m_actions[j]);
				}
				class IActionTimer* const timer = dynamic_cast<class IActionTimer*>(currentAction);
				Timer::CreateExpiringTimer(action, timer->GetDuration());

				m_actions.resize(++i);
			}
			break;
			case ActionType::ACTION_TYPE_CONDITION:
			{

				class IActionCondition* const condition = dynamic_cast<class IActionCondition*>(currentAction);
				if (condition)
				{
					class ActionExecuteActionArray* const action = new ActionExecuteActionArray();
					for (int32_t j = i + 1ull; j < m_actions.size(); j++)
					{
						action->push(m_actions[j]);
					}

					Timer::CreateConditionTimer(action, condition->GetCondition());

					m_actions.resize(++i);
				}
			}
			break;
			case ActionType::ACTION_TYPE_IF_THEN_ELSE:
			{
				//class ActionExecuteActionArray* const action = new ActionExecuteActionArray();
				//for (int32_t j = i + 1; j < m_actions.size(); j++)
				//{
				//	action->push(m_actions[j]);
				//}
				class ActionIfThenElse* action_if_then_else = dynamic_cast<class ActionIfThenElse*>(currentAction);
				if (action_if_then_else)
				{
					currentAction = action_if_then_else->GetThen();
					//m_actions.resize(++i);
					goto REPEAT_SWITCH;
				}
			}
			break;
			default:
				break;
			}
			goto END;
		case ActionBehavior::ACTION_BEHAVIOR_SKIP_REMAINING_ACTIONS:
			goto END;
			
		}
	}
END:
	return;
}

const ActionBehavior ActionExecuteActionArray::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
