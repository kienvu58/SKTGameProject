#include "Entity.h"
#include <iostream>


Entity::Entity(): m_iPrototypeId(0), m_bIsActive(false)
{
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

void Entity::Reset()
{
	std::cout << "Reset nothing" << std::endl;
}

int Entity::GetPrototypeId() const
{
	return m_iPrototypeId;
}

bool Entity::IsActive() const
{
	return m_bIsActive;
}
