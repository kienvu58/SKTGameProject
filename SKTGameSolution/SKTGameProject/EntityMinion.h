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
	bool HandleMessage(const Telegram& telegram) override;

	//Get FSM
	StateMachine<EntityMinion>* GetFSM() const;

	EntityMinion();
	~EntityMinion();

	float GetMaxForce();

	//clone
	Entity* Clone() override;
private:
	//State info
	StateMachine<EntityMinion>* m_pStateMachine;

	//behavior
	SteeringBehavior* m_pSteeringBehavior;

	//physics functions
	void TruncateVelocity(b2Vec2& velocity);

	//physics info
	float m_fMaxForce;
};

