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
			class Shader* standard;
			class Shader* shadow;
			class Shader* select;
		};

		class Shader* shaders[3];
	};

	struct ID3D11DeviceContext* m_context;
	enum ShaderType             m_activeShader;

	void Begin(const enum ShaderType type = ShaderType::STANDARD);

	void BeginShadow() const;
	void BeginStandard() const;
	void BeginSelect() const;

	void End() const;

	mutable class Shader* current{};
};
