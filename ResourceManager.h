#pragma once
#include "ResourceShader.h"
#include "ResourceTexture.h"
#include "ResourceSound.h"

#include <iostream>
#include <vector>
#include <mutex>

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
	void PrintOutTextures();
	void Release();

	Shader* GetShaderByName(char* shaderName);
	Texture* GetTextureByName(char* textureName);
	Sound* GetSoundByName(char* soundName);


	static ResourceManager* GetInstance();
private:
	vector<ResourceTexture*> m_textures;
	vector<ResourceShader*>  m_shaders;
	vector<ResourceSound*>   m_sounds;

	mutex m_shaderMutex;

	static ResourceManager* m_instance;




	ResourceManager(void);
};

