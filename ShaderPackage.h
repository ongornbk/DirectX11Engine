#pragma once
#include "Shader.h"
#include <mutex>

struct ShaderPackage
{
protected:
		struct
		{
			class Shader* standard;
			class Shader* shadow;
			class Shader* select;
			class Shader* inter;
		};

public:

	ShaderPackage(
		struct ID3D11DeviceContext* const __context,
		class Shader* const __standard,
		class Shader* const __shadow,
		class Shader* const __select,
		class Shader* const __inter);

	struct ID3D11DeviceContext* m_context;
	
	class Shader* const BeginShadow() const;
	class Shader* const BeginStandard() const;
	class Shader* const BeginSelect() const;
	class Shader* const BeginInterface() const;

	bool SetShaderParameters(
		struct ID3D11DeviceContext* const deviceContext,
		struct ID3D11ShaderResourceView* const texture,
		const uint32 index
	) const;
	bool SetShaderParameters(
		struct ID3D11DeviceContext* const deviceContext,
		struct ID3D11ShaderResourceView* const texture
	) const;

	bool SetShaderParameters(
		struct ID3D11DeviceContext* const deviceContext,
		const struct DirectX::XMFLOAT4X4& worldMatrix,
		const struct DirectX::XMFLOAT4X4& viewMatrix,
		const struct DirectX::XMFLOAT4X4& projectionMatrix
	) const;

	bool SetShaderColorParameters(
		struct ID3D11DeviceContext* const deviceContext,
		float* const colors
	) const;

	bool SetShaderColorParameters(
		struct ID3D11DeviceContext* const deviceContext,
		const struct DirectX::XMFLOAT4& colors
	) const;

	bool SetShaderScaleParameters(
		struct ID3D11DeviceContext* const deviceContext,
		float* const scale
	) const;

	bool SetShaderScaleParameters(
		struct ID3D11DeviceContext* const deviceContext,
		const struct DirectX::XMFLOAT4& scale
	) const;

	void End() const;

	class Shader* const GetShader() const modern_except_state;

private:

	mutable class Shader* current{};
};
