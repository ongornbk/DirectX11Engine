#pragma once
#include "Shader.h"

enum ShaderType
{
	STANDARD = 0,
	SHADOW = 1,
	SELECT = 2,
};

struct ShaderPackage
{
	union
	{
		struct
		{
			Shader* standard;
			Shader* shadow;
			Shader* select;
		};

		Shader* shaders[3];
	};

	ID3D11DeviceContext* m_context;
	ShaderType           m_activeShader;

	void Begin(const enum ShaderType type = ShaderType::STANDARD);


};
