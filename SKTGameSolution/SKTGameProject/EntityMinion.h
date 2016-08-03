#pragma once
#include "EntityLiving.h"
#include <Common/FSM/StateMachine.h>
#include "SteeringBehavior.h"

class SteeringBehavior;

class EntityMinion : public EntityLiving
{
public:

	void Render() override;
	void Update() override;
	EntityType GetType() override;
	bool HandleMessage(const Telegram& telegram) override = 0;

	EntityMinion();
	virtual ~EntityMinion();

	float GetMaxForce();

	//clone
	Entity* Clone() override;
protected:
	//behavior
	SteeringBehavior* m_pSteeringBehavior;

	//physics functions
	void TruncateVelocity(b2Vec2& velocity);

	//physics info
	float m_fMaxForce;
};

