#pragma once
#include "EntityMinion.h"

class EntityCell
	: public EntityMinion
{
public:
	EntityCell();
	~EntityCell();

	//Get FSM
	StateMachine<EntityCell>* GetFSM() const;

	//clone
	Entity* Clone() override;

	void Update() override;
	bool HandleMessage(const Telegram& telegram) override;

	EntityType GetType() override;

	void Reset() override;
private:
	//State info
	StateMachine<EntityCell>* m_pStateMachine;
};

