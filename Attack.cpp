#include "Attack.h"

Attack::Attack(void) : range(0.f), m_attackDelay(0.2f), delay(false)
{

}

Attack::Attack(const float _range) : range(_range),m_attackDelay(0.2f), delay(false)
{
}
