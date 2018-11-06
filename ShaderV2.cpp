#include "ShaderV2.h"

SpriteShader::SpriteShader()
{
}

SpriteShader::~SpriteShader()
{
}

void SpriteShader::Begin(ID3D11DeviceContext * deviceContext)
{
}

void SpriteShader::End(ID3D11DeviceContext * deviceContext)
{
}

ShaderType SpriteShader::GetShaderType()
{
	return ShaderType::SPRITESHADER;
}

string SpriteShader::GetName()
{
	return m_name;
}
