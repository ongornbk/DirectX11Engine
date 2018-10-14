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

	void _cdecl SetTextsLimit(uint8_t _In_ limit = 5u) noexcept;

	void _cdecl PushText(std::string _In_ text) noexcept;

	void _cdecl PushTextFront(std::string _In_ text) noexcept;

	void _cdecl SetFont(Font* _In_ font) noexcept;

	void _cdecl ClearQueue() noexcept;

	void _cdecl Update() noexcept;

	void _vectorcall Render(ID3D11DeviceContext* _In_ deviceContext,XMFLOAT4X4 _In_ worldMatrix, XMFLOAT4X4 _In_ viewMatrix, XMFLOAT4X4 _In_ projectionMatrix) noexcept;

	void _vectorcall SetTextPosition(DirectX::XMFLOAT2 _In_ pos) noexcept;


	auto _cdecl begin() noexcept;

	auto _cdecl end() noexcept;

protected:

	std::list<Text> m_texts;

	uint8_t                   m_size;
	uint8_t                   m_textsLimit;
	DirectX::XMFLOAT2         m_pos;

	Font*                     m_font;

	PrintingStyle             m_printingStyle;

private:

	Text CreateTextFromString(std::string _In_ text) noexcept;

	void CheckSize() noexcept;
};

