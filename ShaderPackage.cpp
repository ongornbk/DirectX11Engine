#include "ShaderPackage.h"

void ShaderPackage::Begin(const enum ShaderType type)
{
	shaders[m_activeShader]->End(m_context);
	m_activeShader = type;
	shaders[m_activeShader]->Begin(m_context);
}