#pragma once
#include "ICFunction.h"

class CFunctionVoid :
    public ICFunction
{
    CFunctionVoid() = delete;
public:
    CFunctionVoid(void (*vfo)(void));
    ~CFunctionVoid();

     void execute() override;
};

