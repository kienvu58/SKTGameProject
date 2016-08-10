#pragma once
#include "EntityLiving.h"
#include "SteeringBehavior.h"

class SteeringBehavior;

class EntityMinion : public EntityLiving
{
public:

	void Render() override;
	void Update() override;
	EntityType GetType() override;
	void InitSteeringBehavior();
	bool HandleMessage(const Telegram& telegram) override = 0;

	EntityMinion();
	virtual ~EntityMinion();

	float GetMaxForce() const;
	SteeringBehavior* GetSteering() const;

	//clone
	Entity* Clone() override;

	void Reset() override;
	void Explode();
protected:
	//behavior
	SteeringBehavior* m_pSteeringBehavior;

	//physics functions
	void TruncateVelocity(b2Vec2& velocity) const;

	//physics info
	float m_fMaxForce;

	int m_iExplosionPID;
};

