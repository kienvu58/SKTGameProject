#pragma once
#include "EntityTypes.h"
class Telegram;

class Entity
{
public:
	Entity();
	virtual ~Entity();
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual bool HandleMessage(const Telegram& telegram) = 0;

	virtual EntityType GetType();

	virtual Entity* Clone() = 0;
};

