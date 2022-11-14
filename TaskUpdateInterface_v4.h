#pragma once
#include "modern/modern_task.h"
#include "modern/modern_handle.h"

class TaskUpdateInterface_v4 : public modern_task
{
    class modern_handle m_text;
public:
    TaskUpdateInterface_v4(const class modern_handle& text);
    ~TaskUpdateInterface_v4();

    void execute() override;
};



