#include "EntityManager.h"
#include <iostream>
#include "GlobalUtilities.h"
#include "Engine.h"


	EntityManager* EntityManager::m_instance = NULL;

EntityManager::EntityManager()
{
	m_entities.reserve(1000);
}


EntityManager::~EntityManager()
{
	RemoveAllEntities();
}

void EntityManager::Update()
{

	for (auto i = m_entities.begin(); i < m_entities.end(); ++i)
	{

		
			if (!(XMVectorGetY((*i)->m_velocity) <= 20.00f))
				(*i)->Update();
			else
			{
				delete *i;
				*i = NULL;
				m_entities.erase(i);
				i--;
			}
		
	}
}

void EntityManager::Release()
{

	delete(m_instance);
}

Entity * EntityManager::AddEntity()
{
	Entity* entity = new Entity();
	m_entities.push_back(entity);
	return entity;
	
}

void EntityManager::RemoveEntity(Entity * entity)
{
	if (entity == NULL)return;
	int index = -1;
	if (ContainsEntity(entity, index))
	{
		m_entities.erase(m_entities.begin() + index);
		delete entity;
	}
}

void EntityManager::RemoveAllEntities()
{
	m_entities.clear();
}

bool EntityManager::ContainsEntity(Entity * entity)
{
	int size = (int)m_entities.size();
	for (int i = 0; i < size; ++i)
	{
		if (m_entities[i] == entity)
		{
			return true;
		}
	}
	return false;
}

bool EntityManager::ContainsEntity(Entity * entity, int & index)
{
	index = -1;
	int size = (int)m_entities.size();
	for (int i = 0; i < size; ++i)
	{
		if (m_entities[i] == entity)
		{
			index = i;
			return true;
		}
	}
	return false;
}

Entity * EntityManager::GetFront()
{
	if (m_entities.empty())return NULL;
	return m_entities.front();
}

Entity * EntityManager::GetBack()
{
	if (m_entities.empty())return NULL;
	return m_entities.back();
}

EntityManager * EntityManager::GetInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new EntityManager();
	}
	return m_instance;
}

void EntityManager::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
{
	//for (const auto & entity : m_entities)
//	{
	//	entity->Render(deviceContext,viewMatrix,projectionMatrix);
	//}
	Engine::GetEngine()->GetGraphics()->EnableAlphaBlending(true);
	for (vector<Entity*>::reverse_iterator i = m_entities.rbegin();
		i != m_entities.rend(); ++i) {

		
		(*i)->Render(deviceContext, viewMatrix, projectionMatrix);
		
	}
	Engine::GetEngine()->GetGraphics()->EnableAlphaBlending(false);
}
