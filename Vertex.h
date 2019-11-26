#pragma once
#include <DirectXMath.h>

struct SpriteVertexType
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT2 uv;
};

struct TextureVertexType
{
	DirectX::XMFLOAT2 position;
	DirectX::XMFLOAT2 uv;
};

struct ColorVertexType
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 color;
};

