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

	void SetTextsLimit(const int32 limit) noexcept;

	void PushText(std::string  text) noexcept;

	void PushTextFront(std::string  text) noexcept;

	void SetFont(class Font* font) noexcept;

	void ClearQueue() noexcept;

	void Update() noexcept;

	void  Render(struct ID3D11DeviceContext* const deviceContext, DirectX::XMFLOAT4X4& worldMatrix, DirectX::XMFLOAT4X4& viewMatrix, DirectX::XMFLOAT4X4& projectionMatrix) noexcept;

	void  SetTextPosition(DirectX::XMFLOAT3 pos) noexcept;

	void  SetGlobals(ID3D11Device*  device, ID3D11DeviceContext*  context, Shader* shader) noexcept;

	auto  begin() noexcept;

	auto  end() noexcept;

protected:

	std::list<Text*> m_texts;

	int32                     m_size;
	int32                     m_textsLimit;
	DirectX::XMFLOAT3         m_pos;
	Font*                     m_font;

	PrintingStyle             m_printingStyle;

private:

	Text* CreateTextFromString(std::string  text) noexcept;

	void CheckSize() noexcept;
};

