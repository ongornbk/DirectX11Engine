#pragma once
#include "d2d1.h"
#include <DirectXMath.h>
#include "Brushes.h"
#include "RenderTarget.h"
#include "TextFormat.h"
#include "TextSize.h"
#include "Direct2DCallback.h"
#include "../WindowHandle.h"
#include "Types.h"


class Direct2D : Brushes,RenderTarget,RenderTargetSize,TextFormat,TextSize,Direct2DCallback,WindowHandle
{
public:
	Direct2D();
	~Direct2D();

	Boolean CreateFactory();
	Boolean InitializeResources();
	Boolean DiscardDeviceResources();
	Boolean OnResize(uint32_t width, uint32_t height);
	
	void BeginDraw();
	void EndDraw();

protected:
	ID2D1Factory*          m_factory;
	IDWriteFactory*        m_writeFactory;

};

