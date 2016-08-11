#pragma once
#include "EntityMinion.h"
#include <Common/FSM/StateMachine.h>

enum CellAnimationName
{
	CELL_STANDING,
	CELL_FORWARD,
	CELL_BACKWARD,
	CELL_UP,
	CELL_DOWN,
	CELL_FIRING
};

class EntityCell
	: public EntityMinion
{
public:
	void InitStateMachine();
	EntityCell();
	~EntityCell();

	//Get FSM
	StateMachine<EntityCell>* GetFSM() const;
	
	void Init(int prototypeId, const char* dataPath) override;

	//clone
	Entity* Clone() override;

	void Update() override;
	bool HandleMessage(const Telegram& telegram) override;

	void Reset() override;
private:
	//State info
	StateMachine<EntityCell>* m_pStateMachine;
};

