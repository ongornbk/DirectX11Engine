#include "ModelVariant.h"

ModelVariant::ModelVariant()
{
	ZeroMemory(m_textures, sizeof(Texture*) * 15);
	m_variant = 0;
	m_prevVariant = 0;
}

ID3D11ShaderResourceView* ModelVariant::GetTexture() const
{
	return m_textures[m_variant]->GetTexture();
}

int32_t ModelVariant::GetVariant() const noexcept
{
	return m_variant;
}

float ModelVariant::GetMaxFrames() const noexcept
{
	return m_maxFrames[m_variant];
}

float ModelVariant::GetSize() const noexcept
{
	return m_sizes[m_variant];
}

void ModelVariant::SetVariant(const enum ModelStance variant) const noexcept
{
	this->m_prevVariant = this->m_variant;
	this->m_variant = variant;
}

void ModelVariant::SetVariant(const int32_t variant) const
{
	this->m_prevVariant = this->m_variant;
	this->m_variant = variant;
}

bool ModelVariant::Check() const noexcept
{
	return (this->m_variant != this->m_prevVariant);
}