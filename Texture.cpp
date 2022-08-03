#include "Texture.h"
#include "GlobalUtilities.h"
#include "gdef.h"
#include "IPP.h"

using namespace DirectX;

Texture::Texture()
{
	m_texture = 0;
	m_width   = 0;
	m_height  = 0;
}




Texture::~Texture()
{
	if (m_texture)
	{
		(void)m_texture->Release();
		m_texture = NULL;
	}
}

const modern_Boolean Texture::Initialize(struct ID3D11Device* const device, const class modern_string& name)
{
	HRESULT result;
	//m_name = name;
	std::wstring str(name.c_wstr());
	const size_t pos = (size_t)str.find_last_of(L"/");
	if (pos >= 0l)
	{
		str = str.substr(pos + 1ull, str.length());
	}
	m_name = str.substr(0ull, str.find(L".")).c_str();
	str = str.substr(str.find(L".")+1);

	
	//if(str[0]==L'p')
	//	result = CreateWICTextureFromFile(device, name.c_wstr(), NULL, &m_texture, NULL);
	//else
	result =   CreateDDSTextureFromFile(device, name.c_wstr(), NULL, &m_texture, NULL);
	if (FAILED(result))
	{
		ipp::Console::Println(name.c_wstr());
		ipp::Console::Println(m_name.c_wstr());
		ipp::Console::Println(modern_string(result).c_wstr());
		//ipp::Console::GetInput();
		return modern_false;
	}

	struct ID3D11Resource* resource = nullptr;
	m_texture->GetResource(&resource);
	struct ID3D11Texture2D* texture2D = nullptr;
	result = resource->QueryInterface(&texture2D);
	if (SUCCEEDED(result))
	{
		struct D3D11_TEXTURE2D_DESC desc;
		texture2D->GetDesc(&desc);
		m_width = desc.Width;
		m_height = desc.Height;
	}

	if (texture2D)
	{
		(void)texture2D->Release();
		texture2D = nullptr;
	}
	if (resource)
	{
		(void)resource->Release();
		resource = nullptr;
	}



	return modern_true;
}


struct ID3D11ShaderResourceView * Texture::GetTexture()
{
	return m_texture;
}

const class modern_string_view& Texture::GetName()
{
	return *(new modern_string_view(&m_name));
}

int Texture::GetWidth()
{
	return m_width;
}

int Texture::GetHeight()
{
	return m_height;
}
