#pragma once
#include "VertexBuffer.h"

//proto

class ParticleVertexBuffer : public VertexBuffer
{
public:
	ParticleVertexBuffer();
	~ParticleVertexBuffer();
private:
	SimpleVertexType* m_vertexType;
};

