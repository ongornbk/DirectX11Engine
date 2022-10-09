#pragma once
#include "ITask.h"
#include "modern/modern_handle.h"

class TaskUpdateInterface_v4 : public ITask
{
    class modern_handle m_text;
public:
    TaskUpdateInterface_v4(const class modern_handle& text);
    ~TaskUpdateInterface_v4();

    void execute() override;
};



