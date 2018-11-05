#pragma once
#include "Shader.h"

struct ShaderPackage
{
	Shader* standard;
	Shader* shadow;
	Shader* select;
};
