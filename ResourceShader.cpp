#include "ResourceShader.h"



ResourceShader::ResourceShader()
{
	m_shader = NULL;
}


ResourceShader::~ResourceShader()
{
	if (m_shader)
	{
		m_shader = NULL;
	}
}

bool ResourceShader::Load(ID3D11Device * device, HWND hwnd,WCHAR* shaderFileName)
{
	m_shader = new Shader(device, hwnd, shaderFileName);
	if (!(m_shader)->IsInitialized())
	{
		m_shader = NULL;
		return false;
	}
	return true;
}

bool ResourceShader::Load(Shader * shader)
{
	if (m_shader == NULL)return false;
	m_shader = shader;
	if (!(m_shader)->IsInitialized())
	{
		m_shader = NULL;
		return false;
	}
	return true;
}

Shader* ResourceShader::GetShader()
{
	return m_shader;
}

string ResourceShader::GetName()
{
	if(m_shader)return (m_shader)->GetName();
	return "Uninitialized Shader";
}
