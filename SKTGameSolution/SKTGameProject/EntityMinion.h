#pragma once
#include "EntityLiving.h"
#include "SteeringBehavior.h"

class SteeringBehavior;

class EntityMinion : public EntityLiving
{
public:
	EntityMinion();
	virtual ~EntityMinion();
	
	void Render() override;
	void Update() override;
	EntityType GetType() override;
	void InitSteeringBehavior();
	bool HandleMessage(const Telegram& telegram) override = 0;

	float GetMaxForce() const;
	SteeringBehavior* GetSteering() const;

	//clone
	Entity* Clone() override;

	void Reset() override;
	void Explode();
	int GetPrize() const;
protected:
	//behavior
	SteeringBehavior* m_pSteeringBehavior;

	//physics functions
	void TruncateVelocity(b2Vec2& velocity) const;

	//physics info
	float m_fMaxForce;

	int m_iExplosionPID;
	int m_iPrize;
};
