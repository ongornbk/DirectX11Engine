#include "ActionMessageFront.h"
#include "UserInterfaceGame.h"

ActionMessageFront::ActionMessageFront(class GameObject* const object) : m_object(object)
{
}

ActionMessageFront::~ActionMessageFront()
{
}

void ActionMessageFront::execute()
{
	class GameChat* const game_chat = UserInterfaceGame::GetGameChat();
	if (game_chat)
	{
		game_chat->PushTextFront(std::to_string((unsigned long long) m_object));
	}
}

const ActionBehavior ActionMessageFront::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
