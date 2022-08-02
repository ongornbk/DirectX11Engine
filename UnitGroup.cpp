#include "UnitGroup.h"

UnitGroup::UnitGroup()
{

}

UnitGroup::~UnitGroup()
{
}

void UnitGroup::Insert(Unit* const unit)
{
	if(unit)
	m_units.push_back(unit);
}

void UnitGroup::Remove(Unit* const unit)
{
	if(unit)
	m_units.remove(unit);
}

bool UnitGroup::empty() const modern_except_state
{
	return m_units.empty();
}

size_t UnitGroup::size() const modern_except_state
{
	return m_units.size();
}

void UnitGroup::clear() modern_except_state
{
	m_units.clear();
}

std::stack<class Unit*> UnitGroup::GetStack()
{
	class std::stack<class Unit*> stck;
	for (auto&& unit : m_units)
	{
		stck.push(unit);
	}
	return stck;
}
