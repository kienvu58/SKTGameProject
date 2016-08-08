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

	bool OnMessage(EntityMinion*, const Telegram&) override;
};

class MinionGlobalState : public State<EntityMinion>
{
public:
	MinionGlobalState();
	~MinionGlobalState();

	void Enter(EntityMinion* minion) override;
	void Execute(EntityMinion* minion) override;
	void Exit(EntityMinion* minion) override;
	void Render(EntityMinion* minion) override;

	bool OnMessage(EntityMinion*, const Telegram&) override;
};

class MinionDeadState : public State<EntityMinion>
{
public:
	MinionDeadState();
	~MinionDeadState();

	void Enter(EntityMinion* minion) override;
	void Execute(EntityMinion* minion) override;
	void Exit(EntityMinion* minion) override;
	void Render(EntityMinion* minion) override;

	bool OnMessage(EntityMinion*, const Telegram&) override;
};