#include "ResourceManager.h"
#include "GlobalUtilities.h"
#include <map>
#include <urlmon.h>
#include <sstream>
#include <fstream>
#include <streambuf>

using namespace GlobalUtilities;

#pragma region
#define TEXTURES_LOCATION "../../content/textures/"
#define RESOURCES_LOCATION "../../Resources/Resources.file"
#define DIRT_LOCATION "../../content/textures/tiles/dirt.png"
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

namespace
{
	map<string, string> m_resourcesURLS;
}

static HRESULT GetItemByUrl(string url, string path)
{
	HRESULT result = URLDownloadToFile(NULL, "https://github.com/ongornbk/engine-0.1/raw/master/Resources/dirt.png", path.c_str(), 0, NULL);
	return result;
}

ResourceManager::ResourceManager()
{
	ifstream stream(RESOURCES_LOCATION);
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
		getline(ss, token2, '@');
		m_resourcesURLS[token] = token2;
		cout << token << endl << token2 << endl << endl;
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

void ResourceManager::LoadShaderResource(ID3D11Device * device, HWND hwnd, WCHAR* shaderFileName)
{
	ResourceShader* resourceShader = new ResourceShader();
	if (!resourceShader->Load(device, hwnd, shaderFileName))
	{
		delete resourceShader;
		SetConsoleTextAttribute(hConsole, 12);
		cout << "ResourceManager : Unable To Load : " << *shaderFileName << endl;
		return;
	}
	m_shaders.push_back(resourceShader);
	SetConsoleTextAttribute(hConsole, 10);
	cout << "ResourceManager : Successfully Loaded : " << *shaderFileName << endl;
}

void ResourceManager::LoadShaderResource(Shader * shader)
{
	if (shader == NULL) return;
	ResourceShader* resourceShader = new ResourceShader();
	if (!resourceShader->Load(shader))
	{
		delete resourceShader;
		SetConsoleTextAttribute(hConsole, 12);
		cout << "ResourceManager : Unable To Load shader!" << endl;
		return;
	}
	m_shaders.push_back(resourceShader);
	SetConsoleTextAttribute(hConsole, 10);
	cout << "ResourceManager : Successfully Loaded : " << resourceShader->GetName() << endl;
}

void ResourceManager::LoadTextureResource(ID3D11Device * device, WCHAR* textureFileName)
{
	ResourceTexture* resourceTexture = new ResourceTexture();
	if (!resourceTexture->Load(device, textureFileName))
	{
		wstring ws(textureFileName);
		string str(ws.begin(), ws.end());
		if (!GetItemByUrl(m_resourcesURLS[str],str))
		{
			
			if (!resourceTexture->Load(device, textureFileName))
			{
				delete resourceTexture;
				SetConsoleTextAttribute(hConsole, 12);
				cout << "ResourceManager : Unable To Download" << endl;
				Sleep(3000);
				return;
			}
			else
			{
				cout << "ResourceManager : Successfully Loaded from URL" << endl;
			}
		}
		else
		{
			delete resourceTexture;
			SetConsoleTextAttribute(hConsole, 12);
			cout << "ResourceManager : Unable To Load" <<endl;
			Sleep(3000);
			return;
		}
	}
	m_textures.push_back(resourceTexture);
	SetConsoleTextAttribute(hConsole, 10);
	cout << "ResourceManager : Successfully Loaded" << endl;
}

void ResourceManager::LoadSoundResource(WCHAR* soundFileName)
{
	ResourceSound* resourceSound = new ResourceSound();
	if (!resourceSound->Load(soundFileName))
	{
		delete resourceSound;
		SetConsoleTextAttribute(hConsole, 12);
		cout << "ResourceManager : Unable To Load : " << *soundFileName  << endl;
		return;
	}
	m_sounds.push_back(resourceSound);
	SetConsoleTextAttribute(hConsole, 10);
	cout << "ResourceManager : Successfully Loaded : " << *soundFileName << " at " << resourceSound << endl;
}

void ResourceManager::LoadFontResource(WCHAR * fontFileName)
{
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

Font * ResourceManager::GetFontByName(char * fontName)
{
	return nullptr;
}

ResourceManager * ResourceManager::GetInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new ResourceManager();
	}
	return m_instance;
}
