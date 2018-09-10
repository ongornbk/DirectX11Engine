#include "Graphics2D.h"


#define gfx __f000__()->

namespace
{
	Graphics2D* m_instance = nullptr;
}

void _stdcall onUpdate()
{
	if (m_instance)m_instance->Update();
}

void _stdcall onRender()
{
	if (m_instance)m_instance->Render();
}

Graphics2D::Graphics2D()
{
	m_activeBrush = m_cornflowerBlueBrush;
	m_stroke = 1.5f;
	m_renderCallback = onRender;
	m_updateCallback = onUpdate;
}


Graphics2D::~Graphics2D()
{
}

void Graphics2D::Render()
{
	SetStroke(2.0f);
	SetBrush(m_cornflowerBlueBrush);
	SetTextSize(30.0f);
	DrawWideText(L"fdfdfdf", { 0.0f,0.0f,m_renderTargetSize.x,m_renderTargetSize.y });
}

void Graphics2D::Update()
{
}

void Graphics2D::SetBrush(ID2D1SolidColorBrush * brush)
{
	m_activeBrush = brush;
}

void Graphics2D::DrawLine(DirectX::XMFLOAT2 pointA, DirectX::XMFLOAT2 pointB)
{
	gfx DrawLine({ pointA.x,pointA.y }, { pointB.x ,pointB.y }, m_activeBrush, m_stroke);

}

void Graphics2D::DrawRectangle(DirectX::XMFLOAT4 rectangle)
{
	gfx DrawRectangle({ rectangle.x,rectangle.y,rectangle.z,rectangle.w }, m_activeBrush, m_stroke);
}

void Graphics2D::FillRectangle(DirectX::XMFLOAT4 rectangle)
{
	gfx FillRectangle({ rectangle.x,rectangle.y,rectangle.z,rectangle.w }, m_activeBrush);
}

void Graphics2D::DrawEllipse(DirectX::XMFLOAT4 ellipse)
{
	gfx DrawEllipse({ ellipse.x,ellipse.y,ellipse.z,ellipse.w }, m_activeBrush, m_stroke);
}

void Graphics2D::DrawWideText(std::wstring text, DirectX::XMFLOAT4 rect)
{
	gfx DrawTextA(text.c_str(), (uint32_t)text.size(), m_textFormat, { rect.x,rect.y,rect.z,rect.w }, m_activeBrush);
}

void Graphics2D::SetStroke(float size)
{
	m_stroke = size;
}

void Graphics2D::SetTextSize(float size)
{
	m_textSize = size;
}

ID2D1HwndRenderTarget * Graphics2D::__f000__()
{
	return m_renderTarget.load();
}
