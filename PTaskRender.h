#pragma once
#include "IPTask.h"
#include "Engine.h"
class PTaskRender :
    public IPTask
{
    class Engine* m_engine;
public:
    PTaskRender(Engine* const engine);

    void execute() override;
};

