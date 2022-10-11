#pragma once
#include "modern/modern_array.h"
#include "ITask.h"

class TaskSortY :
    public ITask
{
    class modern_array<class GameObject*>* m_arr;
public:
    TaskSortY(class modern_array<class GameObject*>* const arr);
    ~TaskSortY();

    void execute() override;
};

