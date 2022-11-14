#pragma once
#include "modern/modern_task.h"
class TaskBarrier :
    public modern_task
{
private:
   // std::atomic<int64_t> m_barrier;
public:
    TaskBarrier();
    ~TaskBarrier();

    void execute() override;
};
