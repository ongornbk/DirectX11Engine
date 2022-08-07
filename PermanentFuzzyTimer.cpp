#include "PermanentFuzzyTimer.h"

bool PermanentFuzzyTimer::update(const float dt)
{
	actionFuzzy->execute();
	return true;
}

PermanentFuzzyTimer::PermanentFuzzyTimer()
{
	actionFuzzy = nullptr;
}

PermanentFuzzyTimer::~PermanentFuzzyTimer()
{
	if (actionFuzzy)
	{
		delete actionFuzzy;
		actionFuzzy = nullptr;
	}

}

void PermanentFuzzyTimer::Initialize(IAction* const fuzzy)
{
	actionFuzzy = fuzzy;
}
