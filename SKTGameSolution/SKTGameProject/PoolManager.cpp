#include "PoolManager.h"
#include "SingletonClasses.h"
#include "../GraphicsEngine/HelperFunctions.h"

PoolManager::PoolManager()
{
}

PoolManager::~PoolManager()
{
	for (auto& pair : m_mapAvailable)
	{
		for (auto entity : pair.second)
		{
			delete entity;
		}
		pair.second.clear();
	}
	m_mapAvailable.clear();
	for (auto entity : m_vInUse)
	{
		delete entity;
	}
	m_vInUse.clear();
}

Entity* PoolManager::GetEntityByPrototypeId(int prototypeId)
{
	auto pair = m_mapAvailable.find(prototypeId);
	Entity* entity;

	auto entityReady = true;

	if (pair != m_mapAvailable.end())
	{
		if (pair->second.size() == 0)
			entityReady = false;
	}
	else
	{
		entityReady = false;
	}

	if (entityReady)
	{
		entity = pair->second.at(0);
		RemoveFromVector<Entity*>(pair->second, entity);
		auto ix = std::find(m_vInUse.begin(), m_vInUse.end(), entity);
		if (ix == m_vInUse.end())
			m_vInUse.push_back(entity);
	}
	else
	{
		auto prototype = Factory->GetPrototypeById(prototypeId);
		if (!prototype)
		{
			return nullptr;
		}
		entity = prototype->Clone();
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
		entity->Reset();
		auto prototypeId = entity->GetPrototypeId();
		auto it = m_mapAvailable.find(prototypeId);
		if (it != m_mapAvailable.end())
		{
			auto ix = std::find(it->second.begin(), it->second.end(), entity);
			if (ix == it->second.end())
				it->second.push_back(entity);
		}
		else
		{
			std::vector<Entity*> vectorEntity;
			vectorEntity.push_back(entity);
			m_mapAvailable.insert(std::pair<int, std::vector<Entity*>>(prototypeId, vectorEntity));
		}
		RemoveFromVector<Entity*>(m_vInUse, entity);
	}
}