#pragma once
#include "EntityLiving.h"
#include <Common/FSM/StateMachine.h>

class EntityMinion : public EntityLiving
{
public:

	void Render() override;
	void Update() override;

	//Get FSM
	StateMachine<EntityMinion>* GetFSM() const;

	EntityMinion();
	~EntityMinion();

private:
	//State info
	StateMachine<EntityMinion>* m_pStateMachine;
};

