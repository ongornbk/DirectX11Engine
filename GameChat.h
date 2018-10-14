#pragma once
#include "Text.h"
#include <list>
#include <sal.h>

class GameChat
{
public:
	GameChat();
	~GameChat();

	enum PrintingStyle
	{
		GOUP,
		GODOWN
	};

	void SetTextsLimit(uint8_t limit) noexcept;

	void PushText(std::string  text) noexcept;

	void PushTextFront(std::string  text) noexcept;

	void SetFont(Font* font) noexcept;

	void ClearQueue() noexcept;

	void Update() noexcept;

	void  Render(ID3D11DeviceContext* deviceContext,XMFLOAT4X4  worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix) noexcept;

	void  SetTextPosition(DirectX::XMFLOAT3 pos) noexcept;

	void  SetGlobals(ID3D11Device*  device, ID3D11DeviceContext*  context, Shader* shader) noexcept;

	auto  begin() noexcept;

	auto  end() noexcept;

protected:

	std::list<Text*> m_texts;

	uint8_t                   m_size;
	uint8_t                   m_textsLimit;
	DirectX::XMFLOAT3         m_pos;
	Font*                     m_font;

	PrintingStyle             m_printingStyle;

private:

	Text* CreateTextFromString(std::string  text) noexcept;

	void CheckSize() noexcept;
};

