#include "CellOwnedStates.h"
#include "SingletonClasses.h"

/* Wandering State */
CellWanderingState::CellWanderingState()
{
}

CellWanderingState::~CellWanderingState()
{
}

void CellWanderingState::Enter(EntityCell* minion)
{
}

void CellWanderingState::Execute(EntityCell* minion)
{
}

void CellWanderingState::Exit(EntityCell* minion)
{
}

void CellWanderingState::Render(EntityCell* minion)
{
}

bool CellWanderingState::OnMessage(EntityCell*, const Telegram&)
{
	return false;
}

/* Global State */
CellGlobalState::CellGlobalState()
{
}

CellGlobalState::~CellGlobalState()
{
}

void CellGlobalState::Enter(EntityCell* minion)
{
}

void CellGlobalState::Execute(EntityCell* minion)
{
	MS_Global::GetInstance()->Execute(minion);

	if (minion->IsDead())
	{
		minion->GetFSM()->ChangeState(CS_Dead::GetInstance());
	}
}

void CellGlobalState::Exit(EntityCell* minion)
{
}

void CellGlobalState::Render(EntityCell* minion)
{
}

bool CellGlobalState::OnMessage(EntityCell* minion, const Telegram& telegram)
{
	if (MS_Global::GetInstance()->OnMessage(minion, telegram))
		return true;
	return false;
}

/* Attacking State */
CellAttackingState::CellAttackingState()
{
}

CellAttackingState::~CellAttackingState()
{
}

void CellAttackingState::Enter(EntityCell* Cell)
{
}

void CellAttackingState::Execute(EntityCell* Cell)
{
}

void CellAttackingState::Exit(EntityCell* Cell)
{
}

void CellAttackingState::Render(EntityCell* Cell)
{
}

bool CellAttackingState::OnMessage(EntityCell*, const Telegram&)
{
	return false;
}

/* Dead State */
CellDeadState::CellDeadState()
{
}

CellDeadState::~CellDeadState()
{
}

void CellDeadState::Enter(EntityCell* Cell)
{
	GS_GamePlay::GetInstance()->GetPlayer()->IncreaseScore(10);
}

void CellDeadState::Execute(EntityCell* Cell)
{
	Dispatcher->DispatchMessageA(Cell, GameInstance, MSG_MINION_OUT_OF_WALL, Cell);
}

void CellDeadState::Exit(EntityCell* Cell)
{
}

void CellDeadState::Render(EntityCell* Cell)
{
}

bool CellDeadState::OnMessage(EntityCell*, const Telegram&)
{
	return false;
}
