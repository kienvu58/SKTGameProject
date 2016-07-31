#pragma once
#include "Entity.h"
#include <map>

class FactoryEntity
{
public:
	FactoryEntity();
	~FactoryEntity();

	void Init(char* filePath);
	Entity* GetPrototype(EntityType type);
private:
	std::map<EntityType, Entity*>* m_pPrototypes;
};

