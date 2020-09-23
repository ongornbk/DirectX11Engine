#pragma once
#include "LetterSprite.h"
#include "Vector.h"
#include "GarbageCollector.h"
#include <comdef.h>


using std::string;


class Text
{
public:

	struct LetterSpriteStruct
	{
		LetterSpriteStruct()
		{
			m_char = ' ';
			m_sprite = nullptr;
		}
		~LetterSpriteStruct()
		{
			if (m_sprite)
			{
				GarbageCollector::GetInstance()->AsyncDelete(m_sprite);
				m_sprite = nullptr;
			}
		}
		class LetterSprite* m_sprite;
		XMFLOAT4X4          m_world;
		CHAR                m_char;
	};

	Text();
	~Text();

	void Update();
	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader, TextFont* font);
	void Render(struct ID3D11DeviceContext* const deviceContext, DirectX::XMFLOAT4X4& worldMatrix, DirectX::XMFLOAT4X4& viewMatrix, DirectX::XMFLOAT4X4& projectionMatrix);

	void SetPosition(XMFLOAT3 position);
	void SetText(std::string text);
	void SetText(const _bstr_t text);
	string GetText();

private:

	Vector<struct LetterSpriteStruct*> m_letters;
	string                      m_text;


	void Initialize();

};

