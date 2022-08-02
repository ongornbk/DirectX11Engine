#pragma once 
#include <d3d11_1.h>
#include <string>
#include "WICTextureLoader.h"
#include "modern/modern_string.h"
#include "modern/modern_string_view.h"

using namespace std;

class Texture
{
public:
	Texture(void);
	~Texture(void);

	const modern_Boolean Initialize(
		struct ID3D11Device* const device,
		const class modern_string& name
	);

	ID3D11ShaderResourceView* GetTexture();
	const class modern_string_view& GetName();
	int GetWidth();
	int GetHeight();
private:
	ID3D11ShaderResourceView* m_texture;
	class modern_string m_name;
	int m_width;
	int m_height;

};

