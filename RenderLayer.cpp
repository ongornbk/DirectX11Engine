#include "RenderLayer.h"

RenderLayer::~RenderLayer()
{
}

size_t RenderLayer::GetNumberOfObjects() const modern_except_state
{
    return m_size;
}
