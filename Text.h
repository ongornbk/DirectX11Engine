#pragma once
#include "LetterSprite.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class Text
{
public:

	struct LetterSpriteStruct
	{
		LetterSprite* m_sprite;
		XMFLOAT4X4    m_world;
		CHAR          m_char;
	};

	Text();
	~Text();

	void Update();
	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader, Font* font);
	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);

	void SetPosition(XMFLOAT3 position);
	void SetText(std::string text);
	string GetText();

private:

	vector<LetterSpriteStruct*> m_letters;
	string                m_text;


	void Initialize();

};

