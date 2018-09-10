#include "RenderTarget.h"

DirectX::XMFLOAT2 RenderTargetSize::m_renderTargetSize = { 0.0f,0.0f };
std::atomic<ID2D1HwndRenderTarget*> RenderTarget::m_renderTarget = nullptr;