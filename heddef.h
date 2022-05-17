#pragma once


#define hde_BEGIN_ACTIONS class ActionExecuteActionArray* const def_actions_array = new class ActionExecuteActionArray();
#define hde_ACTION_REMOVE_THIS def_actions_array->push(new class ActionRemoveObject(this));
#define hde_ACTIONS_INSTANT Timer::CreateInstantTimer(def_actions_array);
