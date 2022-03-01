#include "ResourceManager.h"
#include "GlobalUtilities.h"
#include "IPP.h"
#include <map>
#include <urlmon.h>
#include <sstream>
#include <fstream>
#include <streambuf>

using ipp::Console;

#pragma region
#define TEXTURES_LOCATION   "../../content/textures/"
#define RESOURCES_LOCATION  "../../Resources/Resources.file"
#define DIRT_LOCATION       "../../content/textures/tiles/dirt.png"
#define TILES_LOCATION      "../../content/textures/tiles/"
#define TEXTURES_LOCATION2   "x64/Release/content/textures/"
#define RESOURCES_LOCATION2  "x64/Release/Resources/Resources.file"
#define DIRT_LOCATION2       "x64/Release/content/textures/tiles/dirt.png"
#define TILES_LOCATION2      "x64/Release/content/textures/tiles/"
#define RESOURCES_URL       "https://raw.githubusercontent.com/ongornbk/engine-0.1/master/Resources/Resources.file"
#pragma endregion

#pragma comment(lib,"urlmon.lib")

#pragma region
using std::ifstream;
using std::stringstream;
using std::streambuf;
using std::getline;
using std::istringstream;
#pragma endregion

ResourceManager* ResourceManager::m_instance = NULL;

extern "C"
{


	namespace
	{
		std::map<std::string, std::string> m_resourcesURLS;
		struct ID3D11Device*       m_device;
	}

	namespace rm
	{

		void SetDevice(ID3D11Device* device)
		{
			m_device = device;
		}

	}

}

static HRESULT GetItemByUrl(string url, string path)
{

	HRESULT result = URLDownloadToFile(NULL, url.c_str(), path.c_str(), 0, NULL);
	return result;
}

ResourceManager::ResourceManager()
{
	ifstream stream(RESOURCES_LOCATION);
	if (!stream.good())
	{
		stream.close();
		stream.open(RESOURCES_LOCATION2);
		if (!stream.good())
		{
			if (FAILED(GetItemByUrl(RESOURCES_URL, RESOURCES_LOCATION)))
			{
				Console::Println(("Download Failed : " + string(RESOURCES_URL)), ipp::RED);
				return;
			}
			else
			{
				stream = ifstream(RESOURCES_LOCATION);
			}
		}
	}
	std::string BUFFER((std::istreambuf_iterator<char>(stream)),std::istreambuf_iterator<char>());
	istringstream ss(BUFFER);
	vector<string> resources;
	string token, token2;
	while (getline(ss, token, '\n'))
	{
		resources.push_back(token);
	}
	for (auto && obj : resources)
	{
		ss = istringstream(obj);
		getline(ss, token, '@');
		getline(ss, token2);
		m_resourcesURLS[token] = token2;
	}




}


ResourceManager::~ResourceManager()
{

		while (!m_shaders.empty())
		{
			delete m_shaders[0];
			m_shaders.erase(m_shaders.begin());
		}
		while (!m_textures.empty())
		{
			delete m_textures[0];
			m_textures.erase(m_textures.begin());
		}
		while (!m_sounds.empty())
		{
			delete m_sounds[0];
			m_sounds.erase(m_sounds.begin());
		}
	


}

void ResourceManager::LoadShaderResource(HWND hwnd, WCHAR* shaderFileName)
{
	using std::cout;
	ResourceShader* resourceShader = new ResourceShader();
	if (!resourceShader->Load(m_device, hwnd, shaderFileName))
	{
		//wstring ws(shaderFileName);
		//string str(ws.begin(), ws.end());
		//if (SUCCEEDED(GetItemByUrl(m_resourcesURLS[str], str)))
		//{
		//
		//	if (!resourceShader->Load(m_device,hwnd, shaderFileName))
		//	{
		//		delete resourceShader;
		//		Console::Println(("Download Failed : " + string(m_resourcesURLS[str])), ipp::RED);
		//		return;
		//	}
		//	else
		//	{
		//
		//		m_shaders.push_back(resourceShader);
		//		return;
		//	}
		//}
		//else
		//{
			delete resourceShader;
			Console::SetTextColor(ipp::RED);
			Console::Print("Load Failed : ");
			if (shaderFileName == L"")
				shaderFileName = L"-empty wstring-";
			Console::Println(wstring(shaderFileName));
			return;
		//}
	}
	m_shaderMutex.lock();
	m_shaders.push_back(resourceShader);
	m_shaderMutex.unlock();
}


void ResourceManager::LoadShaderResource(Shader * shader)
{
	using std::cout;
	if (shader == NULL) return;
	ResourceShader* resourceShader = new ResourceShader();
	if (!resourceShader->Load(shader))
	{
		delete resourceShader;
		Console::Println("Unable to load shader!", ipp::RED);
		return;
	}
	m_shaders.push_back(resourceShader);
}

void ResourceManager::LoadTextureResource(WCHAR* textureFileName)
{
	using std::cout;
	ResourceTexture* resourceTexture = new ResourceTexture();
	if (!resourceTexture->Load(m_device, textureFileName))
	{
		wstring ws(textureFileName);
		string str(ws.begin(), ws.end());
		if (SUCCEEDED(GetItemByUrl(m_resourcesURLS[str],str)))
		{
			
			if (!resourceTexture->Load(m_device, textureFileName))
			{
				delete resourceTexture;
				Console::Println(("Download Failed : " + string(m_resourcesURLS[str])), ipp::RED);
				return;
			}
			else
			{
				m_textures.push_back(resourceTexture);
				return;
			}
		}
		else
		{
			delete resourceTexture;
			wstring wsac = L"Load Failed : " + std::wstring(textureFileName);
			string strwsc(wsac.begin(), wsac.end());
            Console::Println((strwsc), ipp::RED);
			return;
		}
	}
	m_textures.push_back(resourceTexture);
}

void ResourceManager::LoadTextureResource(modern_string& name)
{
	LoadTextureResource(name.c_wstr());
}

void ResourceManager::LoadSoundResource(WCHAR* soundFileName,const enum class SoundType type)
{
	ResourceSound* resourceSound = new ResourceSound();
	if (!resourceSound->Load(soundFileName,type))
	{
		wstring ws(soundFileName);
		string str(ws.begin(), ws.end());
		if (SUCCEEDED(GetItemByUrl(m_resourcesURLS[str], str)))
		{

			if (!resourceSound->Load(soundFileName,type))
			{
				delete resourceSound;
				Console::Println(("Download Failed : " + string(m_resourcesURLS[str])), ipp::RED);
				return;
			}
			else
			{
				m_sounds.push_back(resourceSound);
				return;
			}
		}
		else
		{
			delete resourceSound;
			Console::Println("Load Failed : ", wstring(soundFileName), ipp::RED);
			return;
		}
	}
	m_sounds.push_back(resourceSound);
}

void ResourceManager::LoadUnitTemplateResource(modern_string& filename)
{
}

void ResourceManager::PrintOutTextures()
{

	Console::SetTextColor(ipp::GOLDEN);
	Console::Print((int)m_textures.size());
	Console::Println(" Textures found ...");

	for (int i = 0; i < (int)m_textures.size(); i++)
	{
		Console::Print((void*)m_textures[i]);
		Console::Println(" : " + m_textures[i]->GetName());
	}
}



void ResourceManager::Release()
{
	delete(this);
}

class Shader* ResourceManager::GetShaderByName(const char * shaderName)
{
	for (int i = 0; i < (int)m_shaders.size(); ++i)
	{
	ResourceShader* resourceShader = m_shaders[i];
	string resourceShaderName = resourceShader->GetName();
	if(!strcmp(shaderName,resourceShaderName.c_str()))
	{
		return resourceShader->GetShader();
	}

}
	return NULL;
}

class Texture * ResourceManager::GetTextureByName(const char* textureName)
{
	for (int i = 0; i < (int)m_textures.size(); i++)
	{
		ResourceTexture* resourceTexture = m_textures[i];
		string resourceTextureName = resourceTexture->GetName();
		if (!strcmp(textureName, resourceTextureName.c_str()))
		{
			return resourceTexture->GetTexture();
		}

	}
	for (int i = 0; i < (int)m_textures.size(); i++)
	{
		ResourceTexture* resourceTexture = m_textures[i];
		string resourceTextureName = resourceTexture->GetName();
		if (!strcmp("sys", resourceTextureName.c_str()))
		{
			return resourceTexture->GetTexture();
		}

	}
	return NULL;
}
class ISound  * ResourceManager::GetSoundByName(const char* soundName)
{
	for (int i = 0; i < (int)m_sounds.size(); ++i)
	{
		ResourceSound* resourceSound = m_sounds[i];
		string resourceSoundName = resourceSound->GetName();
		if (!strcmp(soundName, resourceSoundName.c_str()))
		{
			return resourceSound->GetSound();
		}

	}


	return NULL;
}

class Shader* ResourceManager::GetShaderByName(WCHAR* shaderName)
{
	std::wstring tmp0 = std::wstring(shaderName);
	std::string  tmp1 = std::string(tmp0.begin(), tmp0.end());
	return GetShaderByName(tmp1.c_str());
}

class Texture* ResourceManager::GetTextureByName(WCHAR* textureName)
{
	std::wstring tmp0 = std::wstring(textureName);
	std::string  tmp1 = std::string(tmp0.begin(), tmp0.end());
	return GetTextureByName(tmp1.c_str());
}

class ISound* ResourceManager::GetSoundByName(WCHAR* soundName)
{
	std::wstring tmp0 = std::wstring(soundName);
	std::string  tmp1 = std::string(tmp0.begin(), tmp0.end());
	return GetSoundByName(tmp1.c_str());
}


class ResourceManager * ResourceManager::GetInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new ResourceManager();
	}
	return m_instance;
}
