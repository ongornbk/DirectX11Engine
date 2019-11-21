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

	class Shader* GetShaderByName(const char* shaderName);
	class Texture* GetTextureByName(const char* textureName);
	class Sound* GetSoundByName(const char* soundName);

	class Shader* GetShaderByName(WCHAR* shaderName);
	class Texture* GetTextureByName(WCHAR* textureName);
	class Sound* GetSoundByName(WCHAR* soundName);


	static class ResourceManager* GetInstance();
private:
	vector<class ResourceTexture*> m_textures;
	vector<class ResourceShader*>  m_shaders;
	vector<class ResourceSound*>   m_sounds;

	mutex m_shaderMutex;

	static class ResourceManager* m_instance;




	ResourceManager(void);
};

