#include "GameChat.h"
#include "IPP.h"

namespace
{
	static Shader*                   m_shader;
	static ID3D11Device*             m_device;
	static ID3D11DeviceContext*      m_context;
}

GameChat::GameChat()
{
	m_textsLimit = 0u;
	m_size = 0u;
	m_font = nullptr;
	m_printingStyle = PrintingStyle::GODOWN;
}


GameChat::~GameChat()
{
	for (auto && text : m_texts)
	{
		if (text)
		{
			delete text;
			text = nullptr;
		}
	}
	m_texts.clear();
}

void GameChat::SetTextsLimit(uint8_t limit) noexcept
{
	m_textsLimit = limit;
}

void GameChat::PushText(std::string text) noexcept
{
	m_texts.push_back(CreateTextFromString(text));
	m_size++;
	CheckSize();
}

void  GameChat::PushTextFront(std::string text) noexcept
{
	m_texts.push_front(CreateTextFromString(text));
	m_size++;
	CheckSize();
}

void  GameChat::SetFont(Font* font) noexcept
{
	m_font = font;
}

void GameChat::ClearQueue() noexcept
{
	m_texts.clear();
	m_size = 0u;
}

void GameChat::Update() noexcept
{
	constexpr float offsetY = 30.0f;
	float coY = 0.0f;
	for (auto&& text : m_texts)
	{
		text->SetPosition({ m_pos.x,m_pos.y - coY ,m_pos.z });
		text->Update();
		coY += offsetY;
	}
}

void GameChat::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix) noexcept
{
	for (auto&& text : m_texts)
	{
		text->Render(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	}
}

void  GameChat::SetTextPosition(DirectX::XMFLOAT3 pos) noexcept
{
	m_pos.x = pos.x;
	m_pos.y = pos.y;
	m_pos.z = pos.z;
}

void GameChat::SetGlobals(ID3D11Device * device, ID3D11DeviceContext * context, Shader * shader) noexcept
{
	m_device = device;
	m_context = context;
	m_shader = shader;
}



auto  GameChat::begin() noexcept
{
	return m_texts.begin();
}

auto _cdecl GameChat::end() noexcept
{
	return m_texts.end();
}

Text* GameChat::CreateTextFromString(std::string text) noexcept
{
	Text* __text = new Text();
	__text->Initialize(m_device, m_context, m_shader, m_font);
	__text->SetText(text);
	return __text;
}

void GameChat::CheckSize() noexcept
{
	if (m_size > m_textsLimit)
	{
		m_size--;

		if (m_printingStyle == PrintingStyle::GODOWN)
		{
			Text* text = m_texts.front();
			if (text)
			{
				text;
				text = nullptr;
			}
			m_texts.pop_front();
		}
		else
		{
			Text* text = m_texts.back();
			if (text)
			{
				text;
				text = nullptr;
			}
			m_texts.pop_back();
		}
	}
}
