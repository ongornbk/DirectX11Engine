#pragma once
#include "Player.h"

class PlayerManager
{
	class Player m_players[enum_cast<uint64_t>(PlayerSlot::COUNT)];

public:
	PlayerManager();

	class Player* const SlotToPlayer(const enum class PlayerSlot slot) modern_except_state;

	static class PlayerManager* const GetInstance() modern_except_state;
};

