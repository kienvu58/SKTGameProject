#pragma once
#include <Common/FSM/State.h>
#include "EntityCell.h"

class EntityCell;

class CellWanderingState : public State<EntityCell>
{
public:
	CellWanderingState();
	~CellWanderingState();

	void Enter(EntityCell* minion) override;
	void Execute(EntityCell* minion) override;
	void Exit(EntityCell* minion) override;
	void Render(EntityCell* minion) override;

	bool OnMessage(EntityCell*, const Telegram&) override;
};

class CellGlobalState : public State<EntityCell>
{
public:
	CellGlobalState();
	~CellGlobalState();

	void Enter(EntityCell* minion) override;
	void Execute(EntityCell* minion) override;
	void Exit(EntityCell* minion) override;
	void Render(EntityCell* minion) override;

	bool OnMessage(EntityCell*, const Telegram&) override;
};

class CellAttackingState : public State<EntityCell>
{
public:
	CellAttackingState();
	~CellAttackingState();

	void Enter(EntityCell* Cell) override;
	void Execute(EntityCell* Cell) override;
	void Exit(EntityCell* Cell) override;
	void Render(EntityCell* Cell) override;

	bool OnMessage(EntityCell*, const Telegram&) override;
};

class CellDodgingState : public State<EntityCell>
{
public:
	CellDodgingState();
	~CellDodgingState();

	void Enter(EntityCell* Cell) override;
	void Execute(EntityCell* Cell) override;
	void Exit(EntityCell* Cell) override;
	void Render(EntityCell* Cell) override;

	bool OnMessage(EntityCell*, const Telegram&) override;
};