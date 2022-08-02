#include "modern_def.h"

class modern_framelock
{
	modern_Boolean  m_state;
	double          m_lock;
	double          m_time;
	double          m_deltaTime;
public:
	modern_framelock(const double lock);
	~modern_framelock();

	const modern_Boolean Run()                         modern_except_state;
	const modern_Boolean State()                 const modern_except_state;
	void                 Update(const double dt)       modern_except_state;
	const double         GetDeltaTime()                modern_except_state;
};