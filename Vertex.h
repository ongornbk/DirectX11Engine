#pragma once
#include <DirectXMath.h>

struct SimpleVertexType
{
	DirectX::XMFLOAT3 position;
};

struct SpriteVertexType : public SimpleVertexType
{
	DirectX::XMFLOAT2 uv;
};

struct UnitVertexType : public SpriteVertexType
{
	DirectX::XMFLOAT4 color;
	//float             light;
};

