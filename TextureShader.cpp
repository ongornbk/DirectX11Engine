#include "TextureShader.h"


TextureShader::TextureShader(ID3D11Device * device, HWND hwnd,WCHAR* shaderFileName) : 
	Shader(device,hwnd,shaderFileName)
{
	m_initialized = InitializeSamplerState(device);
}



TextureShader::~TextureShader(void)
{
	if (m_samplerState)
	{
		m_samplerState->Release();
		m_samplerState = NULL;
	}

}

void TextureShader::Begin(ID3D11DeviceContext * deviceContext, int indexCount)
{
	deviceContext->PSSetSamplers(0, 1, &m_samplerState);
	Shader::Begin(deviceContext);
}

void TextureShader::End(ID3D11DeviceContext * deviceContext)
{
	deviceContext->PSSetSamplers(0, 0, NULL);
	Shader::End(deviceContext);
}

bool TextureShader::Initialize(ID3D11Device * device, HWND hwnd,WCHAR* shaderFileName)
{
	if (!Shader::Initialize(device, hwnd, shaderFileName))
	{
		return false;
	}

	return true;
	
}

bool TextureShader::InitializeSamplerState(ID3D11Device * device)
{
	D3D11_SAMPLER_DESC samplerDesc;
	HRESULT result;

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0.f;
	samplerDesc.BorderColor[1] = 0.f;
	samplerDesc.BorderColor[2] = 0.f;
	samplerDesc.BorderColor[3] = 0.f;
	samplerDesc.MinLOD = 0.f;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	result = device->CreateSamplerState(&samplerDesc, &m_samplerState);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}
