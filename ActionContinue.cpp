#include "ActionContinue.h"

ActionContinue::ActionContinue()
{
}

ActionContinue::~ActionContinue()
{
}

void ActionContinue::execute()
{
}

const ActionBehavior ActionContinue::execute_in_array()
{
    return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
