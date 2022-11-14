#pragma once
#include "modern/modern_array.h"
#include "modern/modern_task.h"

class TaskSortX :
    public modern_task
{
    class modern_array<class GameObject*>* m_arr;
public:
    TaskSortX(class modern_array<class GameObject*>* const arr);
    ~TaskSortX();

    void execute() override;
};

