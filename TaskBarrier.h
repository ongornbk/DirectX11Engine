#pragma once
#include "ITask.h"
class TaskBarrier :
    public ITask
{
private:
    std::atomic<int64_t> m_barrier;
public:
    TaskBarrier();
    ~TaskBarrier();

    void execute() override;
};
