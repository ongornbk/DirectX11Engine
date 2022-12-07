#pragma once
#include <modern__.h>

class TaskUpdateInterface_v5 : public modern_task
{
    class modern_handle m_interface;
    struct DirectX::XMFLOAT3 m_offset;
    const float m_dt;

public:
    TaskUpdateInterface_v5(const class modern_handle& __p_interface,const struct DirectX::XMFLOAT3& offset, const float dt = 0.f);
    ~TaskUpdateInterface_v5();

    void execute() override;
};

