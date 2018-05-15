#pragma once
#include "Texture.h"
#include <vector>

using std::vector;

struct ModelPaths
{

	ModelPaths();
	ModelPaths(WCHAR* file);

	WCHAR* ATTACK_1;
	WCHAR* ATTACK_2;
	WCHAR* GETHIT;
	WCHAR* KICK;
	WCHAR* NEUTRAL;
	WCHAR* RUN;
	WCHAR* SPECIALCAST;
	WCHAR* SPECIAL_1;
	WCHAR* SPECIAL_3;
	WCHAR* SPECIAL_4;
	WCHAR* TOWNNEUTRAL;
	WCHAR* TOWNWALK;
	WCHAR* WALK;

};

class TextureArray
{
public:
	TextureArray();
	TextureArray(const TextureArray&);
	~TextureArray();

	

	bool InitializeArray(ID3D11Device*,ModelPaths paths);
	ID3D11ShaderResourceView* GetTexture(int index);
	void Shutdown();
	ID3D11ShaderResourceView** GetTextureArray();

private:

	bool Initialize(ID3D11Device*, WCHAR* filename,int index);

	vector<string>                m_name;
	int                           m_width[13];
	int                           m_height[13];
	ID3D11ShaderResourceView*     m_textures[13];
};