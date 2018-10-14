#include "GameChat.h"
#include "GlobalVariables.h"

GameChat::GameChat()
{
	m_textsLimit = 0u;
	m_size = 0u;
	m_font = nullptr;
	m_printingStyle = PrintingStyle::GODOWN;
}


GameChat::~GameChat()
{
	m_texts.clear();
}

void _cdecl GameChat::SetTextsLimit(uint8_t limit) noexcept
{
	m_textsLimit = limit;
}

void _cdecl GameChat::PushText(std::string text) noexcept
{
	m_texts.push_back(CreateTextFromString(text));
	m_size++;
}

void _cdecl GameChat::PushTextFront(std::string text) noexcept
{
	m_texts.push_front(CreateTextFromString(text));
	m_size++;
}

void _cdecl GameChat::SetFont(Font* font) noexcept
{
	m_font = font;
}

void _cdecl GameChat::ClearQueue() noexcept
{
	m_texts.clear();
	m_size = 0u;
}

void _cdecl GameChat::Update() noexcept
{
	constexpr float offsetY = 20.0f;
	float coY = 0.0f;
	for (auto text : m_texts)
	{
		text.SetPosition({ m_pos.x,m_pos.y + coY ,0.0f });
		text.Update();
		coY += offsetY;
	}
}

void _vectorcall GameChat::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 _In_ worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix) noexcept
{
	for (auto text : m_texts)
	{
		text.Render(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	}
}

void _vectorcall GameChat::SetTextPosition(DirectX::XMFLOAT2 pos) noexcept
{
	m_pos.x = pos.x;
	m_pos.y = pos.y;

}



auto _cdecl GameChat::begin() noexcept
{
	return m_texts.begin();
}

auto _cdecl GameChat::end() noexcept
{
	return m_texts.end();
}

Text GameChat::CreateTextFromString(std::string text) noexcept
{
	Text __text;
	__text.Initialize(gv::g_device, gv::g_context, gv::g_textShader, m_font);
	__text.SetText(text);
	return __text;
}

void GameChat::CheckSize() noexcept
{
	if (m_size > m_textsLimit)
	{
		m_size--;

		if (m_printingStyle == PrintingStyle::GODOWN)
		{
			m_texts.pop_front();
		}
		else
		{
			m_texts.pop_back();
		}
	}
}
