#pragma once
#include "PlayerController.h"
#include "PlayerSlotStatus.h"
#include "PlayerSlot.h"
#include "modern/modern_memory.h"
#include "modern/modern_class.h"

class Player : public modern_class
{
	enum class PlayerController m_controller;
	enum class PlayerSlotStatus m_slotStatus;
	enum class PlayerSlot       m_slot;

public:
	const modern_handle& GetHandle();
};

