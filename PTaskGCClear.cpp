#include "PTaskGCClear.h"

PTaskGCClear::PTaskGCClear(GarbageCollector* const gc) :
	m_gc(gc)
{

}

void PTaskGCClear::execute()
{
	m_gc->Update();
}
