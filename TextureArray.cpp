#include "TextureArray.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>

using std::endl;
using std::cout;
using namespace DirectX;

TextureArray::TextureArray()
{
	for(int i = 0;i<13;i++)
	m_textures[i] = NULL;

}


TextureArray::TextureArray(const TextureArray& other)
{

}


TextureArray::~TextureArray()
{
	for (int i = 0; i<13; i++)
	if (m_textures[i])
	{
		(void)m_textures[i]->Release();
		m_textures[i] = NULL;
	}

}


bool TextureArray::InitializeArray(ID3D11Device* device,ModelPaths paths)
{
	HRESULT result;
	Initialize(device, paths.TOWNWALK, 0);
	Initialize(device, paths.TOWNNEUTRAL, 1);
	Initialize(device, paths.SPECIALCAST, 2);
	Initialize(device, paths.GETHIT, 3);
	Initialize(device, paths.KICK, 4);
	Initialize(device, paths.SPECIAL_1, 5);
	Initialize(device, paths.WALK, 6);
	Initialize(device, paths.ATTACK_1, 7);
	Initialize(device, paths.NEUTRAL, 8);
	Initialize(device, paths.ATTACK_2, 9);
	Initialize(device, paths.RUN, 10);
	Initialize(device, paths.SPECIAL_3, 11);
	Initialize(device, paths.SPECIAL_4, 12);

	return true;
}
ID3D11ShaderResourceView * TextureArray::GetTexture(int index)
{
	return m_textures[index];
}
bool TextureArray::Initialize(ID3D11Device *device, WCHAR * filename,int index)
{
	if (filename == NULL)
	{
		return false;
	}
	HRESULT result;


	cout << index << endl;



	result = CreateWICTextureFromFile(device, filename, NULL,&m_textures[index],13);
	if (FAILED(result))
	{
		return false;
	}

	ID3D11Resource* resource = 0;
	m_textures[index]->GetResource(&resource);
	ID3D11Texture2D* texture2D = 0;
	result = resource->QueryInterface(&texture2D);
	if (SUCCEEDED(result))
	{
		D3D11_TEXTURE2D_DESC desc;
		texture2D->GetDesc(&desc);
		m_width[index] = desc.Width;
		m_height[index] = desc.Height;
	}

	if (texture2D)
	{
		(void)texture2D->Release();
		texture2D = NULL;
	}
	if (resource)
	{
		(void)resource->Release();
		resource = NULL;
	}



	return true;
}




ID3D11ShaderResourceView** TextureArray::GetTextureArray()
{
	return m_textures;
}

ModelPaths::ModelPaths()
{
}

ModelPaths::ModelPaths(WCHAR * file)
{
#pragma warning(disable : 4996)
#pragma region
	using std::ifstream;
	using std::getline;
	using std::istreambuf_iterator;
	using std::istringstream;
#pragma endregion
	ifstream stream(file);
	if (!stream.good())
	{

	}
	string BUFFER((istreambuf_iterator<char>(stream)),istreambuf_iterator<char>());
	istringstream ss(BUFFER);
	vector<WCHAR*> animations;
	string token;
	while (getline(ss, token, '\n'))
	{
		wchar_t* wide_string = new wchar_t[token.length() + 1];
		wstring ws = std::wstring(token.begin(), token.end()).c_str();
		wcscpy(wide_string, ws.c_str());
		if (wcscmp(wide_string, L"NULL"))
		{
			animations.push_back(wide_string);
		}
		else
		{
			animations.push_back(NULL);
		}
	}

	ATTACK_1      = animations.at(0);
	ATTACK_2      = animations.at(1);
	GETHIT        = animations.at(2);
	KICK          = animations.at(3);
	NEUTRAL       = animations.at(4);
	RUN           = animations.at(5);
	SPECIALCAST   = animations.at(6);
	SPECIAL_1     = animations.at(7);
	SPECIAL_3     = animations.at(8);
	SPECIAL_4     = animations.at(9);
	TOWNNEUTRAL   = animations.at(10);
	TOWNWALK      = animations.at(11);
	WALK          = animations.at(12);
}
