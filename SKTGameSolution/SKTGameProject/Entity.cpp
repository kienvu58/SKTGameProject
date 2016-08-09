#include "Entity.h"
#include <iostream>


Entity::Entity(): m_iPrototypeId(0) {
}

Entity::~Entity()
{
}

EntityType Entity::GetType()
{
	return ENTITY;
}

void Entity::Init(int prototypeId, const char* dataPath)
{
	std::cout << "Init Base Entity" << std::endl;
}

int Entity::GetPrototypeId() const
{
	return m_iPrototypeId;
}
