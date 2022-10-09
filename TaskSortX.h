#pragma once
#include "modern/modern_array.h"
#include "ITask.h"

class TaskSortX :
    public ITask
{
    class modern_array<class EObject*>* m_arr;
public:
    TaskSortX(class modern_array<class EObject*>* const arr);
    ~TaskSortX();

    void execute() override;
};

