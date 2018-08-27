#pragma once

#include <d3d11_1.h>
#include <directxmath.h>

using namespace DirectX;

class Box
{
public:
	Box(XMVECTOR position,XMVECTOR rotation,XMVECTOR scale);
	~Box();
	
	void Initialize(ID3D11Device* device);
	void Update(float dt);
	void Draw(ID3D11Device* device);
	void Release();
	void SetPosition(float x,float y,float z);
	
private:

ID3D11Buffer * m_vertexBuffer;
ID3D11Buffer* m_indexBuffer;
int m_vertexCount;
int m_indexCount;

XMVECTOR m_position;//?xmfloat3
XMVECTOR m_rotation;
XMVECTOR m_scale;
XMMATRIX m_world;
};

