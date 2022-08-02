#include "Text.h"
#include "TextArea.h"
#include "Input.h"

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

void TextArea::Open() modern_except_state
{
	m_stance = OPEN;
}

void TextArea::Close() modern_except_state
{
	m_stance = CLOSED;
}

void TextArea::Update() modern_except_state
{
	if (m_stance == OPEN)
	{

	}
}

void TextArea::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix) modern_except_state
{
	if (m_stance == OPEN)
	{

	}
}