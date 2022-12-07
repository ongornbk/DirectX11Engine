#pragma once
#include "Texture.h"
#include "ModelStance.h"

struct ModelVariant
{
	ModelVariant();

	ID3D11ShaderResourceView* GetTexture() const;

	int32_t GetVariant() const modern_except_state;

	float GetMaxFrames() const modern_except_state;

	float GetSize() const modern_except_state;

	void SetVariant(const enum ModelStance variant = ModelStance::MODEL_STANCE_NEUTRAL)const modern_except_state;

	void SetVariant(const int32_t variant) const;
	
	void ErrorSprite(const size_t index) modern_except_state;

	bool Check() const modern_except_state;

	class Texture* m_textures[15];
	float                m_maxFrames[15];
	float                m_sizes[15];
private:
	mutable int32_t                m_variant;
	mutable int32_t                m_prevVariant;

};