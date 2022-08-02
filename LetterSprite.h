#pragma once
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "Font.h"
#include "GarbageCollector.h"
#include "PositionC.h"

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
		const struct DirectX::XMFLOAT4X4& world,
		const struct DirectX::XMFLOAT4X4& viewMatrix,
		const struct DirectX::XMFLOAT4X4& projectionMatrix,
		class Shader* const shader
	);

	

	const char GetLetter() const modern_except_state;

	static  void _vectorcall SetMatrixIdentity(const struct DirectX::XMMATRIX identity) modern_except_state;

private:
	ID3D11DeviceContext * m_deviceContext;

	class VertexBuffer* m_vertexBuffer;
	class Texture*      m_texture;
	float         m_size;
	char          m_char;
};

struct LetterSpriteStruct : public PositionC
{
public:
	LetterSpriteStruct(class LetterSprite* const letter);

	void Render(
		struct ID3D11DeviceContext* const deviceContext,
		const struct DirectX::XMFLOAT4X4& viewMatrix,
		const struct DirectX::XMFLOAT4X4& projectionMatrix,
		class Shader* const shader
	);

	void PreRender(
		struct ID3D11DeviceContext* const deviceContext,
		const struct DirectX::XMFLOAT4X4& viewMatrix,
		const struct DirectX::XMFLOAT4X4& projectionMatrix,
		class Shader* const shader
	);

	void Update();

	void _vectorcall SetPosition(const struct DirectX::XMFLOAT3& position);

	const char GetLetter() const modern_except_state;
private:
	LetterSpriteStruct();
	class LetterSprite* m_letter;
};