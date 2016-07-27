#pragma once
#include <Common/FSM/StateMachine.h>
#include "EntityLiving.h"

class EntityPlayer : 
	public EntityLiving
{
public:
	EntityPlayer();
	~EntityPlayer();

	void Render() override;
	void Update() override;

	//Get FSM
	StateMachine<EntityPlayer>* GetFSM() const;
private:
	//State info
	StateMachine<EntityPlayer>* m_pStateMachine;
};
