#include "TextArea.h"
#include "Text.h"


TextArea::TextArea()
{
	m_stance = CLOSED;
}


TextArea::~TextArea()
{
	if (m_text)
	{
		delete m_text;
		m_text = nullptr;
	}
}

void TextArea::Open() noexcept
{
	m_stance = OPEN;
}

void TextArea::Close() noexcept
{
	m_stance = CLOSED;
}

void TextArea::Update() noexcept
{
	if (m_stance == OPEN)
	{

	}
}

void TextArea::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix) noexcept
{
	if (m_stance == OPEN)
	{

	}
}