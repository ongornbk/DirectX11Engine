#pragma once
#include "Text.h"
#include <list>
#include <sal.h>
#include <comdef.h>

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

	void SetTextsLimit(const int32 limit) modern_except_state;

	void PushText(std::string  text) modern_except_state;

	void PushTextFront(std::string  text) modern_except_state;

	void SetFont(class TextFont* font) modern_except_state;

	void ClearQueue() modern_except_state;

	void Update() modern_except_state;

	void  Render(struct ID3D11DeviceContext* const deviceContext,DirectX::XMFLOAT4X4& viewMatrix, DirectX::XMFLOAT4X4& projectionMatrix,class Shader* const shader) modern_except_state;

	void  SetTextPosition(DirectX::XMFLOAT3 pos) modern_except_state;

	void  SetGlobals(ID3D11Device*  device, ID3D11DeviceContext*  context, Shader* shader) modern_except_state;

	auto  begin() modern_except_state;

	auto  end() modern_except_state;

protected:

	std::list<Text*> m_texts;

	int32                     m_size;
	int32                     m_textsLimit;
	DirectX::XMFLOAT3         m_pos;
	TextFont*                     m_font;

	PrintingStyle             m_printingStyle;

private:

	Text* CreateTextFromString(std::string  text) modern_except_state;
	//Text* CreateTextFromString(const _bstr_t text) modern_except_state;

	void CheckSize() modern_except_state;
};

