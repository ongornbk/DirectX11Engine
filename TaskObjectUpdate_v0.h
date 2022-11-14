#pragma once
#include "modern/modern_task.h"
#include "modern/modern_handle.h"

class TaskObjectUpdate_v0 : public modern_task
{
    class modern_handle m_object;
    const float m_dt;

public:
    TaskObjectUpdate_v0(const class modern_handle& object, const float dt = 0.f);
    ~TaskObjectUpdate_v0();

    void execute() override;
};


