#include "ShaderPackage.h"



ShaderPackage::ShaderPackage(
	ID3D11DeviceContext* const __context,
	Shader* const __standard,
	Shader* const __shadow,
	Shader* const __select,
	Shader* const __inter
) :
	m_context(__context),
	standard(__standard),
	shadow(__shadow),
	select(__select),
	inter(__inter)
{
	//assert(__context && __standard && __shadow && __select && __inter);
}

class Shader* const ShaderPackage::BeginShadow() const
{
	if (current)
		if (current != shadow)
			current->End(m_context);
		else
			return current;//current == shadow
shadow->Begin(m_context);
current = shadow;	
return current;
}

class Shader* const ShaderPackage::BeginStandard() const
{
	if (current)
		if (current != standard)
			current->End(m_context);
		else
			return current;
standard->Begin(m_context);
current = standard;
return current;
}

class Shader* const ShaderPackage::BeginSelect() const
{
	if (current)
		if (current != select)
			current->End(m_context);
		else
			return current;
select->Begin(m_context);
current = select;
return current;

}

Shader* const ShaderPackage::BeginInterface() const
{
	if (current)
		if (current != inter)
			current->End(m_context);
		else
			return current;
	inter->Begin(m_context);
	current = inter;
	return current;
}

bool ShaderPackage::SetShaderParameters(ID3D11DeviceContext* const deviceContext, ID3D11ShaderResourceView* const texture, const uint32 index) const
{
	return current->SetShaderParameters(deviceContext,texture,index);
}

bool ShaderPackage::SetShaderParameters(ID3D11DeviceContext* const deviceContext, ID3D11ShaderResourceView* const texture) const
{
	return current->SetShaderParameters(deviceContext, texture);
}

bool ShaderPackage::SetShaderParameters(ID3D11DeviceContext* const deviceContext, const DirectX::XMFLOAT4X4& worldMatrix, const DirectX::XMFLOAT4X4& viewMatrix, const DirectX::XMFLOAT4X4& projectionMatrix) const
{
	return current->SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
}

bool ShaderPackage::SetShaderColorParameters(ID3D11DeviceContext* const deviceContext, float* const colors) const
{
	return current->SetShaderColorParameters(deviceContext, colors);
}

bool ShaderPackage::SetShaderColorParameters(ID3D11DeviceContext* const deviceContext, const DirectX::XMFLOAT4& colors) const
{
	return current->SetShaderColorParameters(deviceContext, colors);
}

bool ShaderPackage::SetShaderScaleParameters(ID3D11DeviceContext* const deviceContext, float* const scale) const
{
	return current->SetShaderScaleParameters(deviceContext, scale);
}

bool ShaderPackage::SetShaderScaleParameters(ID3D11DeviceContext* const deviceContext, const DirectX::XMFLOAT4& scale) const
{
	return current->SetShaderScaleParameters(deviceContext, scale);
}

void ShaderPackage::End() const
{
if(current)
	current->End(m_context);
current = nullptr;
}

Shader* const ShaderPackage::GetShader() const noexcept
{
	return current;
}
