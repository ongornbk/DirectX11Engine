#include "Shader.h"
#include "GlobalUtilities.h"
#include "IPP.h"
#include <d3dcompiler.h>
#include "Defines.h"
#include "gdef.h"

#pragma comment(lib,"d3dcompiler.lib")

using namespace DirectX;

namespace
{
	ID3D11SamplerState* m_samplerState;
}

Shader::Shader(ID3D11Device * device, HWND hwnd,WCHAR* shaderFileName)
{
	m_vertexShader = NULL;
	m_pixelShader = NULL;
	m_layout = NULL;
	m_matrixBuffer = NULL;
	m_cameraBuffer = NULL;
	m_colorBuffer = NULL;

	m_initialized = Initialize(device, hwnd, shaderFileName);

	D3D11_SAMPLER_DESC samplerDesc;
	HRESULT result;

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0.0f;
	samplerDesc.BorderColor[1] = 0.0f;
	samplerDesc.BorderColor[2] = 0.0f;
	samplerDesc.BorderColor[3] = 0.0f;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	result = device->CreateSamplerState(&samplerDesc, &m_samplerState);

	D3D11_BLEND_DESC omDesc;
	ZeroMemory(&omDesc,sizeof(D3D11_BLEND_DESC));
	omDesc.RenderTarget[0].BlendEnable = true;
	omDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	omDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	omDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	omDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	omDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	omDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	omDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	result = device->CreateBlendState(&omDesc, &m_alphaBlendState);

	D3D11_DEPTH_STENCIL_DESC dsDesc;

	dsDesc.DepthEnable = FALSE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	dsDesc.StencilEnable = false;
	dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsDesc.BackFace = dsDesc.FrontFace;

	result  = device->CreateDepthStencilState(&dsDesc, &m_depthStencilState);
}

Shader::Shader(Shader & shader)
{
	
}


Shader::~Shader(void)
{
	if (m_matrixBuffer)
	{
		(void)m_matrixBuffer->Release();
		m_matrixBuffer = NULL;
	}
	if (m_cameraBuffer)
	{
		(void)m_cameraBuffer->Release();
		m_cameraBuffer = NULL;
	}
	if (m_colorBuffer)
	{
		(void)m_colorBuffer->Release();
		m_colorBuffer = NULL;
	}
	if (m_layout)
	{
		(void)m_layout->Release();
		m_layout = NULL;
	}
	if (m_pixelShader)
	{
		(void)m_pixelShader->Release();
		m_pixelShader = NULL;
	}
	if (m_vertexShader)
	{
		(void)m_vertexShader->Release();
		m_vertexShader = NULL;
	}
	if (m_alphaBlendState)
	{
		(void)m_alphaBlendState->Release();
		m_alphaBlendState = NULL;
	}
	if (m_depthStencilState)
	{
		(void)m_depthStencilState->Release();
		m_depthStencilState = NULL;
	}
	m_name.clear();
}

bool Shader::Initialize(ID3D11Device* device, HWND hwnd,WCHAR* shaderFileName)
{

	wstring shaderFilePath(shaderFileName);
	m_name = string(shaderFilePath.begin(),shaderFilePath.end());
	int pos = (int)m_name.find_last_of("/");
	if (pos >= 0)
	{
		m_name = m_name.substr(pos + 1, m_name.length());
	}
 


	return InitializeShader(device, hwnd,shaderFileName);
}

void Shader::Begin(
	struct ID3D11DeviceContext* const deviceContext
)
{
	deviceContext->OMSetBlendState(m_alphaBlendState, 0, 0xFFFFFFFF);
	deviceContext->OMSetDepthStencilState(m_depthStencilState, 0);
	deviceContext->PSSetSamplers(1, 1, &m_samplerState);
	deviceContext->IASetInputLayout(m_layout);
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Shader::End(
	struct ID3D11DeviceContext * const deviceContext
)
{
	deviceContext->PSSetSamplers(0, 0,NULL);
	deviceContext->IASetInputLayout(NULL);
	deviceContext->VSSetShader(NULL, NULL, 0);
	deviceContext->PSSetShader(NULL, NULL, 0);
}

bool Shader::SetShaderParameters(
	struct ID3D11DeviceContext * const deviceContext,
	struct ID3D11ShaderResourceView * const texture,
	const uint32 index
)
{
	deviceContext->PSSetShaderResources(0, 1, &texture);
	return true;
}

bool Shader::SetShaderParameters(
	struct ID3D11DeviceContext * const deviceContext,
	struct ID3D11ShaderResourceView * const texture
)
{
	deviceContext->PSSetShaderResources(0, 1, &texture);
	return true;
}



bool Shader::SetShaderParameters(
	struct ID3D11DeviceContext * const deviceContext,
	const struct XMFLOAT4X4& worldMatrix,
	const struct XMFLOAT4X4& viewMatrix,
	const struct XMFLOAT4X4& projectionMatrix
)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;




	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	dataPtr = (MatrixBufferType*)mappedResource.pData;
	dataPtr->worldMatrix = XMMatrixTranspose(XMLoadFloat4x4(&worldMatrix));
	dataPtr->viewMatrix = XMMatrixTranspose(XMLoadFloat4x4(&viewMatrix));
	dataPtr->projectionMatrix = XMMatrixTranspose(XMLoadFloat4x4(&projectionMatrix));

	deviceContext->Unmap(m_matrixBuffer, 0);


	deviceContext->VSSetConstantBuffers(0, 1, &m_matrixBuffer);


	return true;
}

bool Shader::SetShaderColorParameters(
	struct ID3D11DeviceContext* const deviceContext,
	float * const colors
)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ColorBufferType* dataPtr;
	
	
	
	
	result = deviceContext->Map(m_colorBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}
	
	dataPtr = (ColorBufferType*)mappedResource.pData;
	dataPtr->colorVector.x = colors[0];
	dataPtr->colorVector.y = colors[1];
	dataPtr->colorVector.z = colors[2];
	dataPtr->colorVector.w = colors[3];
	
	deviceContext->Unmap(m_colorBuffer, 0);
	
	
	deviceContext->PSSetConstantBuffers(1, 1, &m_colorBuffer);

	return true;
}


string Shader::GetName()
{
	return m_name;
}

bool Shader::IsInitialized()
{
	return m_initialized;
}

bool Shader::InitializeShader(ID3D11Device* device, HWND hwnd,WCHAR* shaderFileName)
{
	HRESULT result;
	ID3D10Blob* errorMessage = 0;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC colorBufferDesc;

	result = D3DCompileFromFile(shaderFileName, NULL,NULL,"VSMain", "vs_4_0",D3DCOMPILE_ENABLE_STRICTNESS, 0, &vertexShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			OutputShadeErrorMessage(errorMessage, hwnd, shaderFileName);
		}
		else
		{
			wstring tmp0 = wstring(shaderFileName);
			string tmp1 = string(tmp0.begin(), tmp0.end());
			MessageBox(hwnd, tmp1.c_str(), "Error in Shader File VS", MB_OK);
		}
		return false;
	}
	result = D3DCompileFromFile(shaderFileName, NULL, NULL,"PSMain", "ps_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &pixelShaderBuffer, &errorMessage);

	if (FAILED(result))
	{
		if (errorMessage)
		{
			OutputShadeErrorMessage(errorMessage, hwnd, shaderFileName);
		}
		else
		{
			wstring tmp0 = wstring(shaderFileName);
			string tmp1 = string(tmp0.begin(), tmp0.end());
			MessageBox(hwnd, tmp1.c_str(), "Error in Shader File PS", MB_OK);
		}
		return false;
	}
	if (errorMessage)
	{
		errorMessage->Release();
		errorMessage = NULL;
	}
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(result))
	{
		return false;
	}

	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(),pixelShaderBuffer->GetBufferSize(),NULL,&m_pixelShader);
	if (FAILED(result))
	{
		return false;
	}

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;



	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_layout);
	if (FAILED(result))
	{
		return false;
	}

	(void)vertexShaderBuffer->Release();
	vertexShaderBuffer = NULL;

	(void)pixelShaderBuffer->Release();
	pixelShaderBuffer = NULL;

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(result))
	{
		return false;
	}

	colorBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	colorBufferDesc.ByteWidth = sizeof(ColorBufferType);
	colorBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	colorBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	colorBufferDesc.MiscFlags = 0;
	colorBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&colorBufferDesc, NULL, &m_colorBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void Shader::OutputShadeErrorMessage(ID3D10Blob * errorMessage, HWND hwnd, WCHAR* shaderFileName)
{
	char* compileErrors = (char*)errorMessage->GetBufferPointer();
	uint32 bufferSize = (uint32)(errorMessage->GetBufferSize());

	ofstream fout;
	fout.open("shader-error-txt");
	for (unsigned int i = 0u; i < bufferSize; ++i)
	{
		fout << compileErrors[i];
	}
	fout.close();

	(void)errorMessage->Release();
	errorMessage = 0;
	//wstring tmp0 = wstring(shaderFileName);
	//string tmp1 = string(tmp0.begin(), tmp0.end());
	//MessageBox(hwnd, "Error compiling shader. CHeck shader-error.txt for message", tmp1.c_str(), MB_OK);

	return;
}


