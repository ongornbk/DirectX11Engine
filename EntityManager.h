#pragma once
#include "Entity.h"
#include "Camera.h"
#include <vector>

using namespace std;

class EntityManager
{
public:
	
	~EntityManager(void);

	void Update();
	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);

	Entity* AddEntity();
	void RemoveEntity(Entity* entity);
	void RemoveAllEntities();
	void Release();

	bool ContainsEntity(Entity* entity);
	bool ContainsEntity(Entity* entity,int& index);

	Entity* GetFront();
	Entity* GetBack();

	static EntityManager* GetInstance();

private:

	EntityManager(void);
	vector<Entity*> m_entities;
	static EntityManager* m_instance;

};

