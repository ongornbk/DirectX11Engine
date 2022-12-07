#pragma once
#include <modern__.h>

class TaskUpdateInterface_v3 : public modern_task
{
    class modern_handle m_interface;
    class modern_handle m_focus;
    const float m_dt;

public:
    TaskUpdateInterface_v3(const class modern_handle& __p_interface, const class modern_handle& focus, const float dt = 0.f);
    ~TaskUpdateInterface_v3();

    void execute() override;
};

