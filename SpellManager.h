#pragma once
#define SPELL_MANAGER_HUMAN_PLAYER_SPELL_COUNT 12
#include "modern/modern_static_array.h"
#include "ISpell.h"

struct IButton
{

};

struct SpellButton : public IButton
{
	ISpell* m_spell;
};

struct EmptyButton : public IButton
{

};

class SpellManager
{
	class modern_static_array<class IButton*, 12ull> m_spell;
};

