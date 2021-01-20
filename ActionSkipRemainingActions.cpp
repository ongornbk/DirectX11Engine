#include "ActionSkipRemainingActions.h"

ActionSkipRemainingActions::ActionSkipRemainingActions()
{
}

ActionSkipRemainingActions::~ActionSkipRemainingActions()
{

}

void ActionSkipRemainingActions::execute()
{

}

const ActionBehavior ActionSkipRemainingActions::execute_in_array()
{
	//this->execute();//WHY???
	return ActionBehavior::ACTION_BEHAVIOR_SKIP_REMAINING_ACTIONS;
}
