#pragma once
#include <list>
#include <stack>

class Unit;

class UnitGroup
{
public:
	UnitGroup();
	~UnitGroup();

	void Insert(class Unit* const unit);
	void Remove(class Unit* const unit);

	bool empty() const noexcept;
	size_t size() const noexcept;
	void clear() noexcept;

	class std::stack<class Unit*> GetStack();

private:
	class std::list<class Unit*> m_units;
};

