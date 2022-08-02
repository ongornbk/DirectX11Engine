#pragma once
#include <list>
#include <stack>
#include "modern/modern_def.h"

class Unit;

class UnitGroup
{
public:
	UnitGroup();
	~UnitGroup();

	void Insert(class Unit* const unit);
	void Remove(class Unit* const unit);

	bool empty() const modern_except_state;
	size_t size() const modern_except_state;
	void clear() modern_except_state;

	class std::stack<class Unit*> GetStack();

private:
	class std::list<class Unit*> m_units;
};

