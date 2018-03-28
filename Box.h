#pragma once
class Box
{
public:
	Box(DXVECTOR position,DXVECTOR rotation,DXVECTOR scale);
	~Box();
	
	void Initialize(ID3D11Device* device);
	void Update(float dt);
	void Draw(ID3D11Device* device);
	void Release();
	void SetPosition(float x,float y,float z);
	
private:
XMVECTOR m_position;//?xmfloat3
XMVECTOR m_rotation;
XMVECTOR m_scale;
XMMATRIX m_world;
};

