#include "RenderLayer.h"

RenderLayer::~RenderLayer()
{
}

size_t RenderLayer::GetNumberOfObjects() const noexcept
{
    return m_size;
}
