#pragma once
#include "Sprite.h"
#include "S_ModelPaths.h"



class SpriteModel
{
public:
#define STANDARDSTANCE 4

	

	enum ModelStance
	{
		TOWNWALK = 0,
		TOWNNEUTRAL = 1,
		SPECIALCAST = 2,
		GETHIT = 3,
		KICK = 4,
		SPECIAL_1 = 5,
		WALK = 6,
		ATTACK_1 = 7,
		NEUTRAL = 8,
		ATTACK_2 = 9,
		RUN = 10,
		SPECIAL_3 = 11,
		SPECIAL_4 = 12,
	};



	struct ModelVariant
	{
		ModelVariant()
		{
		}
		//TextureArray*      GetTextureArray()
		//{
		//	return m_textures;
		//}
		ID3D11ShaderResourceView* GetTexture()
		{
			return m_textures[m_variant]->GetTexture();
		}
		int GetVariant()
		{
			return m_variant;
		}
		float        GetMaxFrames()
		{
			return m_maxFrames[m_variant];
		}
		void SetVariant(ModelStance variant)
		{
			this->m_variant = variant;
		}
		void SetVariant(int variant)
		{
			this->m_variant = variant;
		}
		//TextureArray*      m_textures;
		Texture*             m_textures[13];
		float m_maxFrames[13] = { 8,16,15,5,0,0,8,16,8,0,8,0,0 };
	private:
		int m_variant;
		
	};

	

	SpriteModel(float size);

	~SpriteModel(void);

	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader,ModelPaths* paths);

	void Update(float dt);
	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix,Shader* shader);
	void SetRotation(int rotation);
	void Resize(ID3D11Device * device, Shader * shader, float resize);
	void SetAnimation(ModelStance animation,bool lock,bool force);
	void SetAnimationSpeed(float speed);
	void PlayAnimation(ModelStance animation);
	bool IsLocked();
	void DrawRectangle(ID3D11DeviceContext * deviceContext,Shader* shader,int borderWidth = 1);
	void SetRotations(float rotations);

	friend class Model;

private:
	ID3D11DeviceContext * m_deviceContext;
	float m_currentFrame;
	float m_previousFrame;


	float         m_animationSpeed;
	float         m_currentSpeed;
	float         m_framesPerSecond;
	bool          m_isLooping;
	float         m_rotation;
	VertexBuffer* m_vertexBuffer;
	ModelVariant  m_modelVariant;
	float         m_size;
	float         m_previousSpeed;
	float         m_rotations;
	int           m_stopped;
	bool          m_stop;
};

