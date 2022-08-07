#include "ResourceTexture.h"



ResourceTexture::ResourceTexture(void)
{
	m_texture = NULL;
}


ResourceTexture::~ResourceTexture(void)
{
	if (m_texture)
	{
		delete m_texture;
		m_texture = NULL;
	}
}

const modern_Boolean ResourceTexture::Load(struct ID3D11Device* const device, const class modern_string& name)
{
	m_texture = new class Texture();
	if (m_texture->Initialize(device, name)) return modern_true;

		delete m_texture;
		m_texture = nullptr;
		return modern_false;
}

Texture * ResourceTexture::GetTexture()
{
	return m_texture;
}

const class modern_string_view& ResourceTexture::GetName() const modern_except_state
{
	if (m_texture)
	{
		return m_texture->GetName();
	}
	return_new_reference modern_string_view(L"UNINITIALIZED RESOURCE TEXTURE");
}
