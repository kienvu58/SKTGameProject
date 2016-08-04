#pragma once
#include "EntityMinion.h"

class EntityCellJunior : public EntityMinion
{
public:
	EntityCellJunior();
	virtual ~EntityCellJunior();
	//Get FSM
	StateMachine<EntityCellJunior>* GetFSM() const;

	//clone
	Entity* Clone() override;

	void Update() override;
	bool HandleMessage(const Telegram& telegram) override;

	EntityType GetType() override;
private:
	//State info
	StateMachine<EntityCellJunior>* m_pStateMachine;
};

