#pragma once
#include "EntityCellJunior.h"


class CellJuniorAttackingState : public State<EntityCellJunior>
{
public:
	CellJuniorAttackingState();
	~CellJuniorAttackingState();

	void Enter(EntityCellJunior* celljunior) override;
	void Execute(EntityCellJunior* celljunior) override;
	void Exit(EntityCellJunior* celljunior) override;
	void Render(EntityCellJunior* celljunior) override;

};
