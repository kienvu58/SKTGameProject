#include "FactoryEntity.h"
#include "../GraphicsEngine/HelperFunctions.h"

FactoryEntity::FactoryEntity()
{
}


FactoryEntity::~FactoryEntity()
{
	ClearMap<Entity>(*m_pPrototypes);
	m_pPrototypes = nullptr;
}

void FactoryEntity::Init(char* filePath)
{
	m_pPrototypes = new std::map<int, Entity*>();
}
