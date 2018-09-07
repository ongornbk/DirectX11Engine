#pragma once
#include "Shader.h"


class Particle
{
public:
	Particle();
	~Particle();
protected:
	Shader* m_shader;
	float   m_size[2];
};

