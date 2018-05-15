#pragma once
#include "ResourceShader.h"
#include "ResourceTexture.h"
#include "ResourceSound.h"
#include "ResourceFont.h"

#include <iostream>
#include <vector>

using namespace std;

extern "C"
{
	namespace rm
	{
		void SetDevice(ID3D11Device* device);
	}
}

class ResourceManager
{
public:
	~ResourceManager(void);

	void LoadShaderResource(HWND hwnd, WCHAR* shaderFileName);
	void LoadShaderResource(Shader* shader);
	void LoadTextureResource( WCHAR* textureFileName);
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

