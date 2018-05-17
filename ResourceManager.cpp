#include "ResourceManager.h"
#include "GlobalUtilities.h"
#include <map>
#include <urlmon.h>
#include <sstream>
#include <fstream>
#include <streambuf>

using namespace GlobalUtilities;

#pragma region
#define TEXTURES_LOCATION   "../../content/textures/"
#define RESOURCES_LOCATION  "../../Resources/Resources.file"
#define DIRT_LOCATION       "../../content/textures/tiles/dirt.png"
#define TILES_LOCATION      "../../content/textures/tiles/"
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
static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

extern "C"
{


	namespace
	{
		map<string, string> m_resourcesURLS;
		ID3D11Device*       m_device;
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
		if (FAILED(GetItemByUrl(RESOURCES_URL,RESOURCES_LOCATION)))
		{
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Download Failed : "<<RESOURCES_URL<< endl;
			return;
		}
		else
		{
			stream = ifstream(RESOURCES_LOCATION);
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
		wstring ws(shaderFileName);
		string str(ws.begin(), ws.end());
		if (SUCCEEDED(GetItemByUrl(m_resourcesURLS[str], str)))
		{

			if (!resourceShader->Load(m_device,hwnd, shaderFileName))
			{
				delete resourceShader;
				SetConsoleTextAttribute(hConsole, 12);
				cout << "Download Failed : " << m_resourcesURLS[str]<< endl;
				return;
			}
			else
			{
				m_shaders.push_back(resourceShader);
				return;
			}
		}
		else
		{
			delete resourceShader;
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Load Failed : "<<shaderFileName << endl;
			return;
		}
	}
	m_shaders.push_back(resourceShader);
}

void ResourceManager::LoadShaderResource(Shader * shader)
{
	using std::cout;
	if (shader == NULL) return;
	ResourceShader* resourceShader = new ResourceShader();
	if (!resourceShader->Load(shader))
	{
		delete resourceShader;
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Unable To Load shader!" << endl;
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
				SetConsoleTextAttribute(hConsole, 12);
				cout << "Download Failed :" << m_resourcesURLS[str]<< endl;
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
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Load Failed : " << m_resourcesURLS[str]<<endl;
			return;
		}
	}
	m_textures.push_back(resourceTexture);
}

void ResourceManager::LoadSoundResource(WCHAR* soundFileName)
{
	ResourceSound* resourceSound = new ResourceSound();
	if (!resourceSound->Load(soundFileName))
	{
		wstring ws(soundFileName);
		string str(ws.begin(), ws.end());
		if (SUCCEEDED(GetItemByUrl(m_resourcesURLS[str], str)))
		{

			if (!resourceSound->Load(soundFileName))
			{
				delete resourceSound;
				SetConsoleTextAttribute(hConsole, 12);
				cout << "Download Failed : " << m_resourcesURLS[str]<< endl;
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
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Load Failed : " << soundFileName<< endl;
			return;
		}
	}
	m_sounds.push_back(resourceSound);
}



void ResourceManager::Release()
{
	delete(this);
}

Shader* ResourceManager::GetShaderByName(char * shaderName)
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

Texture * ResourceManager::GetTextureByName(char* textureName)
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
	return NULL;
}
Sound  * ResourceManager::GetSoundByName(	char* soundName)
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


ResourceManager * ResourceManager::GetInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new ResourceManager();
	}
	return m_instance;
}
