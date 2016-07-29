#pragma once
#include "Entity.h"
#include <map>

enum class prototype_type
{
	player,
	minion
};

class FactoryEntity
{
public:
	FactoryEntity();
	~FactoryEntity();

	void Init(char* filePath);
private:
	std::map<int, Entity*>* m_pPrototypes;
};

