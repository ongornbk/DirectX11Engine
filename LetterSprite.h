#pragma once
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "Font.h"
#include "GarbageCollector.h"

class LetterSprite
{
public:

	LetterSprite(
		class TextFont* const font,
		char letter,
		float size);

	virtual ~LetterSprite(void);

	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader, TextFont* font);

	void Render(
		struct ID3D11DeviceContext* const deviceContext,
		const struct DirectX::XMFLOAT4X4& viewMatrix,
		const struct DirectX::XMFLOAT4X4& projectionMatrix,
		class Shader* const shader
	);

	void Update();

	void _vectorcall SetPosition(const float x, const float y, const float z = 0.f) noexcept;

	const char GetLetter() const noexcept;

private:
	ID3D11DeviceContext * m_deviceContext;

	class VertexBuffer* m_vertexBuffer;
	class Texture*      m_texture;
	XMFLOAT4X4          m_world;
	float         m_size;
	char          m_char;
};
