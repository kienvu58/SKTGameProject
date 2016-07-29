#pragma once
#include <Common/FSM/StateMachine.h>
#include "EntityLiving.h"

enum AnimationName
{
	STANDING,
	MOVING_FORWARD,
	MOVING_BACKWARD,
	TAKING_DAMAGED,
	FALLING,
	DEAD,
	FIRING,
	FIRING_SPECIAL,
	FIRING_ULTIMATE
};

class EntityPlayer :
	public EntityLiving
{
public:
	EntityPlayer();
	~EntityPlayer();

	void Render() override;
	void Update() override;
	EntityType GetType() override;
	bool HandleMessage(const Telegram& telegram) override;

	//Get FSM
	StateMachine<EntityPlayer>* GetFSM() const;
private:
	//player attributes
	float m_fMaxKi;
	float m_fCurrentKi;

	//State info
	StateMachine<EntityPlayer>* m_pStateMachine;
};
