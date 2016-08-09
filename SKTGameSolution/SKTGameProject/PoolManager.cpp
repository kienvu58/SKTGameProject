#include "PoolManager.h"
#include "SingletonClasses.h"
#include "../GraphicsEngine/HelperFunctions.h"

PoolManager::PoolManager()
{
}

PoolManager::~PoolManager()
{
	for (auto pair : m_mapAvailable)
	{
		for (auto it: *(pair.second))
		{
			delete it;
		}
		pair.second->clear();
		delete pair.second;
	}
	m_mapAvailable.clear();
	for (auto it : m_vInUse)
	{
		delete it;
	}
	m_vInUse.clear();
}

Entity* PoolManager::GetEntityByType(EntityType type)
{
	auto it = m_mapAvailable.find(type);
	Entity* entity;

	auto isReady = true;

	if (it != m_mapAvailable.end())
	{
		if (it->second->size() == 0)
			isReady = false;
	}
	else
	{
		isReady = false;
	}

	if (!isReady)
	{
		entity = Factory->GetPrototypeById(type)->Clone();
		auto ix = std::find(m_vInUse.begin(), m_vInUse.end(), entity);
		if (ix == m_vInUse.end())
			m_vInUse.push_back(entity);
	}
	else
	{
		entity = it->second->at(0);
		RemoveFromVector<Entity*>(*(it->second), entity);
		auto ix = std::find(m_vInUse.begin(), m_vInUse.end(), entity);
		if (ix == m_vInUse.end())
			m_vInUse.push_back(entity);
	}
	return entity;
}

void PoolManager::ReleaseEntity(Entity* entity)
{
	if (entity)
	{
		CleanUp(entity);
		EntityType type = entity->GetType();
		auto it = m_mapAvailable.find(type);
		if (it != m_mapAvailable.end())
		{
			auto ix = std::find(it->second->begin(), it->second->end(), entity);
			if (ix == it->second->end())
				it->second->push_back(entity);
		}
		else
		{
			std::vector<Entity*>* vectorEntity = new std::vector<Entity*>();
			vectorEntity->push_back(entity);
			m_mapAvailable.insert(std::pair<EntityType, std::vector<Entity*>*>(type, vectorEntity));
		}
		RemoveFromVector<Entity*>(m_vInUse, entity);
	}
}

void PoolManager::CleanUp(Entity* entity)
{
	//
}

void PoolManager::Add(Entity* entity)
{
}
