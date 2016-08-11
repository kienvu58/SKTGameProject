#pragma once
#include <map>
#include "Entity.h"
#include <vector>

class PoolManager
{
public:
	PoolManager();
	~PoolManager();

	Entity* GetEntityByPrototypeId(int prototypeId);
	void ReleaseEntity(Entity* entity);
private:
	std::map<int, std::vector<Entity*>> m_mapAvailable;
	std::vector<Entity*> m_vInUse;
};

