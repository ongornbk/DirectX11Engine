#pragma once
#include <d3d11_1.h>
#include <directxmath.h>
#include "Texture.h"

using namespace DirectX;
class Font
{
private:
	struct FontType
	{
		float left, right;
		int size;
	};
	struct VertexType
	{
		XMVECTOR position;
		XMVECTOR texture;
	};
public:
	Font();
	~Font();
	Font(const Font&);


	bool Initialize(ID3D11Device*, char*, WCHAR*);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();
	void BuildVertexArray(void*, char*, float, float);

private:
	bool LoadFontData(char*);
	void ReleaseFontData();
	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

private:
	FontType*  m_font;
	Texture*   m_texture;
};

