#include "ShaderPackage.h"
#include "IPP.h"

void ShaderPackage::Begin(const enum ShaderType type)
{
	shaders[m_activeShader]->End(m_context);
	m_activeShader = type;
	shaders[m_activeShader]->Begin(m_context);
}

void ShaderPackage::BeginShadow() const
{
		if (current)
			current->End(m_context);
		shadow->Begin(m_context);
		current = shadow;	
}

void ShaderPackage::BeginStandard() const
{
if (current)
		current->End(m_context);
	standard->Begin(m_context);
	current = standard;	
}

void ShaderPackage::BeginSelect() const
{
if (current)
		current->End(m_context);
	select->Begin(m_context);
	current = select;

}

void ShaderPackage::End() const
{
	if(current)
	current->End(m_context);
	current = nullptr;
}
