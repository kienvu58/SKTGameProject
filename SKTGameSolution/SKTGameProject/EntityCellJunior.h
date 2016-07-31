#pragma once
#include "EntityMinion.h"

class EntityCellJunior : public EntityMinion
{
public:
	EntityCellJunior();
	~EntityCellJunior();

	//clone
	Entity* Clone() override;
};

