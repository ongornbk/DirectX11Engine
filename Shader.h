#pragma once
#include <d3d11_2.h>
#include <directxmath.h>

#include <fstream>
#include <string>

#include "gdef.h"


using namespace DirectX;

using namespace std;

class Shader
{
private:
	struct MatrixBufferType
	{
	XMMATRIX worldMatrix;
	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;
	};

	struct ColorBufferType
	{
	XMFLOAT4 colorVector;
	};
public:
	Shader(ID3D11Device* device, HWND hwnd, WCHAR* shaderFileName);
	Shader(Shader &shader);
	virtual ~Shader(void);
	virtual void Begin(
		struct ID3D11DeviceContext* const deviceContext
	);
	virtual void End(
		struct ID3D11DeviceContext* const deviceContext
	);
	bool SetShaderParameters(
		struct ID3D11DeviceContext* const deviceContext,
		struct ID3D11ShaderResourceView* const texture,
		const uint32 index
	);
	bool SetShaderParameters(
		struct ID3D11DeviceContext* const deviceContext,
		struct ID3D11ShaderResourceView* const texture
	);

	bool SetShaderParameters(
		struct ID3D11DeviceContext* const deviceContext,
		const struct XMFLOAT4X4& worldMatrix,
		const struct XMFLOAT4X4& viewMatrix,
		const struct XMFLOAT4X4& projectionMatrix
	);

	bool Shader::SetShaderColorParameters(
		struct ID3D11DeviceContext* const deviceContext,
		float * const colors
	);




	string GetName();
	bool IsInitialized();

protected:
	virtual bool Initialize(
		struct ID3D11Device* const device,
		HWND hwnd,
		WCHAR* shaderFileName
	);
	bool m_initialized;
private:
	bool InitializeShader(
		struct ID3D11Device* const device,
		HWND hwnd,
		WCHAR* shaderFileName
	);
	void OutputShadeErrorMessage(
		struct ID3D10Blob* const errorMessage,
		HWND hwnd,
		WCHAR* shaderFileName
	);

	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_colorBuffer;
	ID3D11BlendState* m_alphaBlendState;
	ID3D11DepthStencilState* m_depthStencilState;
	string m_name;
	
};