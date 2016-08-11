#pragma once
#include "EntityMinion.h"
#include <Common/FSM/StateMachine.h>

class EntityCellJunior : public EntityMinion
{
public:
	EntityCellJunior();
	virtual ~EntityCellJunior();
	//Get FSM
	StateMachine<EntityCellJunior>* GetFSM() const;

	//clone
	Entity* Clone() override;
	void Init(int prototypeId, const char* dataPath) override;
	void InitStateMachine();
	void Update() override;
	bool HandleMessage(const Telegram& telegram) override;

	void Reset() override;
private:
	//State info
	StateMachine<EntityCellJunior>* m_pStateMachine;
};

