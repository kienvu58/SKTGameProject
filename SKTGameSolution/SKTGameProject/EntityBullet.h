#pragma once
#include "Entity.h"

struct b2Vec2;

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

	virtual void Fire(b2Vec2 position, int direction) = 0;
	virtual bool IsActive() = 0;

protected:
	float m_fSpeed;
	float m_fAttackDamage;

	// direction of ki blast, 1: left to right, -1: right to left
	int m_iDirection;
};
