#pragma once
#include "EntityCellJunior.h"
#include "MinionOwnedStates.h"


class CellJuniorWanderingState : public State<EntityCellJunior>
{
public:
	CellJuniorWanderingState();
	~CellJuniorWanderingState();

	void Enter(EntityCellJunior* minion) override;
	void Execute(EntityCellJunior* minion) override;
	void Exit(EntityCellJunior* minion) override;
	void Render(EntityCellJunior* minion) override;

	bool OnMessage(EntityCellJunior*, const Telegram&) override;
};

class CellJuniorGlobalState : public State<EntityCellJunior>
{
public:
	CellJuniorGlobalState();
	~CellJuniorGlobalState();

	void Enter(EntityCellJunior* minion) override;
	void Execute(EntityCellJunior* minion) override;
	void Exit(EntityCellJunior* minion) override;
	void Render(EntityCellJunior* minion) override;

	bool OnMessage(EntityCellJunior*, const Telegram&) override;
};

class CellJuniorAttackingState : public State<EntityCellJunior>
{
public:
	CellJuniorAttackingState();
	~CellJuniorAttackingState();

	void Enter(EntityCellJunior* celljunior) override;
	void Execute(EntityCellJunior* celljunior) override;
	void Exit(EntityCellJunior* celljunior) override;
	void Render(EntityCellJunior* celljunior) override;
	
	bool OnMessage(EntityCellJunior*, const Telegram&) override;
};

class CellJuniorDeadState : public State<EntityCellJunior>
{
public:
	CellJuniorDeadState();
	~CellJuniorDeadState();

	void Enter(EntityCellJunior* celljunior) override;
	void Execute(EntityCellJunior* celljunior) override;
	void Exit(EntityCellJunior* celljunior) override;
	void Render(EntityCellJunior* celljunior) override;

	bool OnMessage(EntityCellJunior*, const Telegram&) override;
};