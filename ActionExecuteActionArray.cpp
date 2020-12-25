#include "ActionExecuteActionArray.h"
#include "IActionSplitArrayBehavior.h"
#include "IActionTimer.h"
#include "Timer.h"

ActionExecuteActionArray::ActionExecuteActionArray()
{
}

ActionExecuteActionArray::~ActionExecuteActionArray()
{
	for (auto&& ele : m_actions)
	{
		delete ele;
		ele = nullptr;
	}
}

void ActionExecuteActionArray::push(class IAction* const action)
{
	if (action)
		m_actions.push_back(action);
}

void ActionExecuteActionArray::execute()
{
	for (int32_t i = 0; i < m_actions.size(); i++)
	{

		switch (m_actions[i]->execute_in_array())
		{
		case ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH:
			break;
		case ActionBehavior::ACTION_BEHAVIOR_SPLITARRAY:
			switch (dynamic_cast<class IActionSplitArrayBehavior*>(m_actions[i])->GetType())
			{
			case ActionType::TIMER:
			{



				class ActionExecuteActionArray* const action = new ActionExecuteActionArray();
				for (int32_t j = i+1; j < m_actions.size(); j++)
				{
					action->push(m_actions[j]);
				}
				class IActionTimer* const timer = dynamic_cast<class IActionTimer*>(m_actions[i]);
				Timer::CreateExpiringTimer(action, timer->GetDuration());

				m_actions.resize(++i);
			}
			break;
			default:
				break;
			}
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
