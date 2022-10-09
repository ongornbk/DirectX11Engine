#pragma once
#include "ITask.h"
#include "modern/modern_handle.h"

class TaskUpdateInterface_v2 : public ITask
{
    class modern_handle m_interface;
    class modern_handle m_focus;
    const float m_dt;

public:
    TaskUpdateInterface_v2(const class modern_handle& __p_interface, const class modern_handle& focus, const float dt = 0.f);
    ~TaskUpdateInterface_v2();

    void execute() override;
};

