#pragma once
#include "ITask.h"
#include "modern/modern_array.h"

class TaskPack :
    public ITask
{
    class modern_array<class ITask*> m_tasks;

public:
    TaskPack();
    ~TaskPack();

    void execute() override;

    void pack(class ITask* const task);//Reverse order
};

