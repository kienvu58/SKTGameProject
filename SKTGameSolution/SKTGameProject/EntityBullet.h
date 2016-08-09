#pragma once
#include "Entity.h"

class EntityBullet : 
	public Entity
{
public:
	EntityBullet();
	virtual ~EntityBullet();

	void Render() override;
	void Update() override;
	bool HandleMessage(const Telegram& telegram) override;
	EntityType GetType() override;
	Entity* Clone() override;
};
