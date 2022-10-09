#include "PlayerManager.h"

namespace
{
    static class PlayerManager* m_manager = nullptr;
}

PlayerManager::PlayerManager()
{
    m_manager = this;
}

class Player* const PlayerManager::SlotToPlayer(const enum class PlayerSlot slot)
{
    return &m_players[enum_cast<size_t>(slot)];
}

PlayerManager* const PlayerManager::GetInstance()
{
    return m_manager;
}
