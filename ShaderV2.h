#pragma once
#include <d3d11_2.h>
#include <DirectXMath.h>
#include <string>

using std::string;

enum ShaderType
{
	SPRITESHADER
};

struct MatrixBufferType
{
	DirectX::XMMATRIX worldMatrix;
	DirectX::XMMATRIX viewMatrix;
	DirectX::XMMATRIX projectionMatrix;
};

class IShaderV2
{
public:

	virtual void       Begin(ID3D11DeviceContext* deviceContext) = 0;
	virtual void       End(ID3D11DeviceContext* deviceContext) = 0;
	virtual ShaderType GetShaderType() = 0;
	virtual string     GetName() = 0;
};

class SpriteShader : public IShaderV2
{
public:
	SpriteShader();
	~SpriteShader();
	 
	void       Begin(ID3D11DeviceContext* deviceContext) override;
	void       End(ID3D11DeviceContext* deviceContext) override;
	ShaderType GetShaderType() override;
	string     GetName() override;
protected:

	string m_name;
};

