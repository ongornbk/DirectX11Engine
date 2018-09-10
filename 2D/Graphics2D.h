#pragma once
#include "Direct2DCallback.h"
#include "RenderTarget.h"
#include "Brushes.h"
#include "TextFormat.h"
#include "TextSize.h"
#include <string>

class Graphics2D : Direct2DCallback, Brushes, RenderTarget, TextSize, TextFormat, RenderTargetSize
{
public:
	Graphics2D();
	~Graphics2D();

	void Render();
	void Update();

	void SetBrush(ID2D1SolidColorBrush* brush);
	void DrawLine(DirectX::XMFLOAT2 pointA, DirectX::XMFLOAT2 pointB);
	void DrawRectangle(DirectX::XMFLOAT4 rectangle);
	void FillRectangle(DirectX::XMFLOAT4 rectangle);
	void DrawEllipse(DirectX::XMFLOAT4 ellipse);
	void DrawWideText(std::wstring text, DirectX::XMFLOAT4 rect);
	void SetStroke(float size = 1.5f);
	void SetTextSize(float size = 20.0f);

protected:

	ID2D1HwndRenderTarget* __f000__();

	ID2D1SolidColorBrush* m_activeBrush;

	float m_stroke;
};

