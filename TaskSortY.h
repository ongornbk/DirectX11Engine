#pragma once
#include "modern/modern_array.h"
#include "modern/modern_task.h"

class TaskSortY :
    public modern_task
{
    class modern_array<class GameObject*>* m_arr;
public:
    TaskSortY(class modern_array<class GameObject*>* const arr);
    ~TaskSortY();

    void execute() override;
};

