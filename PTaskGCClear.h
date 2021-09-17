#pragma once
#include "IPTask.h"
#include "GarbageCollector.h"
class PTaskGCClear :
    public IPTask
{
    class GarbageCollector* m_gc;
public:
    PTaskGCClear(GarbageCollector* const gc);

    void execute() override;
};

