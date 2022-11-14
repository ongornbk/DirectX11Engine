#pragma once
#include "modern/modern_task.h"
#include "modern/modern_array.h"

class TaskPack :
    public modern_task
{
    class modern_array<class modern_task*> m_tasks;

public:
    TaskPack();
    ~TaskPack();

    void execute() override;

    void pack(class modern_task* const task);//Reverse order
};

