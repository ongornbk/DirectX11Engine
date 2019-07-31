#pragma once 
#include <d3d11_1.h>
#include <string>
#include "WICTextureLoader.h"


using namespace std;

class Texture
{
public:
	Texture(void);
	~Texture(void);

	bool Initialize(
		struct ID3D11Device* const device,
		WCHAR* fileName
	);

	ID3D11ShaderResourceView* GetTexture();
	string GetName();
	int GetWidth();
	int GetHeight();
private:
	ID3D11ShaderResourceView* m_texture;
	string m_name;
	int m_width;
	int m_height;

};

