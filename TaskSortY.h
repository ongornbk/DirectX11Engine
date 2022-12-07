#pragma once

#include <modern__.h>

class TaskSortY :
    public modern_task
{
    class modern_array<class GameObject*>* m_arr;
public:
    TaskSortY(class modern_array<class GameObject*>* const arr);
    ~TaskSortY();

    void execute() override;
};

