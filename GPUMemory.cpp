#include "GPUMemory.h"

namespace
{
    static class GPUMemory* m_instance = nullptr;
}

void GPUMemory::Initialize()
{
    m_instance = new class GPUMemory();
}

struct modern_class* const GPUMemory::get()
{
    return m_instance;
}
