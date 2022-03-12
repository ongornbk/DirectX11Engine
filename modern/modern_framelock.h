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

	const modern_Boolean Run()                         noexcept;
	const modern_Boolean State()                 const noexcept;
	void                 Update(const double dt)       noexcept;
	const double         GetDeltaTime()                noexcept;
};