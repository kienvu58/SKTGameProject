#pragma once
#include <Common/FSM/State.h>
#include "EntityMinion.h"

class WanderingState : public State<EntityMinion>
{
public:
	WanderingState();
	~WanderingState();

	void Enter(EntityMinion* minion) override;
	void Execute(EntityMinion* minion) override;
	void Exit(EntityMinion* minion) override;
	void Render(EntityMinion* minion) override;

};
