#pragma once
#include "LetterSprite.h"
#include "Vector.h"
#include "GarbageCollector.h"
#include "TextAlignment.h"
#include <comdef.h>
#include "modern/modern.h"
#include "modern/modern_class.h"

using std::string;



class Text : public modern_class
{
public:

	

	Text();
	Text(const enum class TextAlignment align);
	~Text();

	void Update();
	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader, TextFont* font,float size);
	void Render(
		struct ID3D11DeviceContext* const deviceContext,
		const struct DirectX::XMFLOAT4X4& viewMatrix,
		const struct DirectX::XMFLOAT4X4& projectionMatrix,
		class Shader* const shader);

	void PreRender(
		struct ID3D11DeviceContext* const deviceContext,
		const struct DirectX::XMFLOAT4X4& viewMatrix,
		const struct DirectX::XMFLOAT4X4& projectionMatrix,
		class Shader* const shader);

	void SetPosition(const struct DirectX::XMFLOAT3& position);
	void _vectorcall SetPosition(const DirectX::XMVECTOR& position);
	void SetOffset(const struct DirectX::XMFLOAT3& offset);
	void Translate(const struct DirectX::XMFLOAT3& vec);
	void SetText(std::string text);
	void SetAlignment(const enum class TextAlignment alignment);
	//void SetText(const _bstr_t text);
	string GetText();
	float GetSize() const noexcept;
	class Shader* const GetShader();

private:

	modern_array<struct LetterSpriteStruct*>& m_letters;
	string                      m_text;
	class Shader* m_shader;
	class TextFont* m_font;
	float m_size;
	float m_spaceWidth;
	float m_width;
	enum class TextAlignment m_alignment;

	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT3 m_offset;

	void Initialize();
	void UpdatePosition();

public:

	const modern_handle& GetHandle();
};

