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

struct ColorVertexType : public SimpleVertexType
{
	DirectX::XMFLOAT3 color;
};

