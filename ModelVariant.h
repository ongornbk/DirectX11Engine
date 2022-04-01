#pragma once
#include "Texture.h"
#include "ModelStance.h"

struct ModelVariant
{
	ModelVariant();

	ID3D11ShaderResourceView* GetTexture() const;

	int32_t GetVariant() const noexcept;

	float GetMaxFrames() const noexcept;

	float GetSize() const noexcept;

	void SetVariant(const enum ModelStance variant = ModelStance::MODEL_STANCE_NEUTRAL)const noexcept;

	void SetVariant(const int32_t variant) const;

	bool Check() const noexcept;

	class Texture* m_textures[15];
	float                m_maxFrames[15];
	float                m_sizes[15];
private:
	mutable int32_t                m_variant;
	mutable int32_t                m_prevVariant;

};