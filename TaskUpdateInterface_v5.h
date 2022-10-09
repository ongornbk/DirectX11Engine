#pragma once
#include "ITask.h"
#include "modern/modern_handle.h"
#include "modern/modern_xmath.h"

class TaskUpdateInterface_v5 : public ITask
{
    class modern_handle m_interface;
    struct DirectX::XMFLOAT3 m_offset;
    const float m_dt;

public:
    TaskUpdateInterface_v5(const class modern_handle& __p_interface,const struct DirectX::XMFLOAT3& offset, const float dt = 0.f);
    ~TaskUpdateInterface_v5();

    void execute() override;
};

