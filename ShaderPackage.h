#pragma once
#include "Shader.h"

struct ShaderPackage
{
	
		struct
		{
			class Shader* standard;
			class Shader* shadow;
			class Shader* select;
		};

	struct ID3D11DeviceContext* m_context;
	
	void BeginShadow() const;
	void BeginStandard() const;
	void BeginSelect() const;

	void End() const;

	mutable class Shader* current{};
};
