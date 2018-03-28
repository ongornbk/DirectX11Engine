#pragma once
#include "ResourceShader.h"
#include "ResourceTexture.h"
#include "ResourceSound.h"
#include "ResourceFont.h"

#include <iostream>
#include <vector>

using namespace std;

class ResourceManager
{
public:
	~ResourceManager(void);

	void LoadShaderResource(ID3D11Device* device, HWND hwnd, WCHAR* shaderFileName);
	void LoadShaderResource(Shader* shader);
	void LoadTextureResource(ID3D11Device* device, WCHAR* textureFileName);
	void LoadSoundResource(WCHAR* soundFileName);
	void LoadFontResource(WCHAR* fontFileName);
	void Release();

	Shader* GetShaderByName(char* shaderName);
	Texture* GetTextureByName(char* textureName);
	Sound* GetSoundByName(char* soundName);
	Font* GetFontByName(char* fontName);

	static ResourceManager* GetInstance();
private:
	vector<ResourceTexture*> m_textures;
	vector<ResourceShader*>  m_shaders;
	vector<ResourceSound*>   m_sounds;
	vector<ResourceFont*>    m_font;

	static ResourceManager* m_instance;




	ResourceManager(void);
};

