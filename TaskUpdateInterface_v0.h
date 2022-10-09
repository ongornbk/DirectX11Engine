#pragma once
#include "ITask.h"
#include "modern/modern_handle.h"

class TaskUpdateInterface_v0 : public ITask
{
    class modern_handle m_interface;
    const float m_dt;

public:
    TaskUpdateInterface_v0(const class modern_handle& __p_interface,const float dt = 0.f);
    ~TaskUpdateInterface_v0();

    void execute() override;
};

