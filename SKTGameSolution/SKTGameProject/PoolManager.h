#pragma once
#include <map>
#include "EntityTypes.h"
#include "Entity.h"
#include <vector>

class PoolManager
{
public:
	PoolManager();
	~PoolManager();

	Entity* GetEntityByType(EntityType type);
	void ReleaseEntity(Entity* entity);
	void CleanUp(Entity* entity);
	void Add(Entity* entity);
private:
	std::map<EntityType, std::vector<Entity*>*> m_mapAvailable;
	std::vector<Entity*> m_vInUse;
};

