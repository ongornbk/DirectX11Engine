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

int32_t ModelVariant::GetVariant() const modern_except_state
{
	return m_variant;
}

float ModelVariant::GetMaxFrames() const modern_except_state
{
	return m_maxFrames[m_variant];
}

float ModelVariant::GetSize() const modern_except_state
{
	return m_sizes[m_variant];
}

void ModelVariant::SetVariant(const enum ModelStance variant) const modern_except_state
{
	this->m_prevVariant = this->m_variant;
	this->m_variant = variant;
}

void ModelVariant::SetVariant(const int32_t variant) const
{
	this->m_prevVariant = this->m_variant;
	this->m_variant = variant;
}

bool ModelVariant::Check() const modern_except_state
{
	return (this->m_variant != this->m_prevVariant);
}