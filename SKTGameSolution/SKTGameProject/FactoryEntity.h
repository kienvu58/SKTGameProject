#pragma once
#include "Entity.h"
#include <map>

class FactoryEntity
{
public:
	FactoryEntity();
	~FactoryEntity();

	void Init(const char* filePath);
	Entity* GetPrototypeById(int prototyteId);
private:
	std::map<int, Entity*> m_mapPrototypes;
};

