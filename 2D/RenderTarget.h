#pragma once
#include "d2d1.h"
#include <DirectXMath.h>
#include <atomic>

class RenderTargetSize
{
protected:
static DirectX::XMFLOAT2                   m_renderTargetSize;
};

class RenderTarget
{
protected:
	static std::atomic<ID2D1HwndRenderTarget*> m_renderTarget;

};

