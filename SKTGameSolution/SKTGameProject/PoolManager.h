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

	Entity* GetEntityByPrototypeId(int prototypeId);
	void ReleaseEntity(Entity* entity);
	void CleanUp(Entity* entity);
	void Add(Entity* entity);
private:
	std::map<int, std::vector<Entity*>*> m_mapAvailable;
	std::vector<Entity*> m_vInUse;
};

