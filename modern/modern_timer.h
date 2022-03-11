#include "modern_def.h"

typedef std::chrono::time_point<std::chrono::steady_clock> modern_timepoint;
typedef std::chrono::duration<double, std::milli> modern_duration;

class modern_timer
{
public:
	modern_timer();
	~modern_timer();
	void Restart();
	modern_Boolean Stop();
	modern_Boolean Start();

	double GetDeltaTime();

	__forceinline static modern_timepoint const& now();
private:
	modern_Boolean   m_running = false;
	modern_timepoint m_start;
	modern_timepoint m_stop;
};