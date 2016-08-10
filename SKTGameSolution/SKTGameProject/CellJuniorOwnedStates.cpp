#include "CellJuniorOwnedStates.h"
#include "MessageTypes.h"
#include "Game.h"
#include <Singleton.hpp>
#include "MessageDispatcher.h"
#include "SingletonClasses.h"
#include <iostream>

/*Attacking State*/
CellJuniorAttackingState::CellJuniorAttackingState()
{
}

CellJuniorAttackingState::~CellJuniorAttackingState()
{
}

void CellJuniorAttackingState::Enter(EntityCellJunior* celljunior)
{
	celljunior->ScaleVelocity(2.0);
	celljunior->GetSteering()->WanderOff();
	celljunior->GetSteering()->SeekOn();
}

void CellJuniorAttackingState::Execute(EntityCellJunior* celljunior)
{
	b2Vec2 playerPositon = GS_GamePlay::GetInstance()->GetPlayer()->GetBody()->GetPosition();
	celljunior->GetSteering()->SetSeekTarget(playerPositon);
	celljunior->IncreaseOverheat(2);
	if (celljunior->IsOverheated())
	{
		celljunior->GetFSM()->ChangeState(CJS_Wandering::GetInstance());
	}
}

void CellJuniorAttackingState::Exit(EntityCellJunior* celljunior)
{
}

void CellJuniorAttackingState::Render(EntityCellJunior* celljunior)
{
}

bool CellJuniorAttackingState::OnMessage(EntityCellJunior*, const Telegram&)
{
	return false;
}

/*Wandering state*/
CellJuniorWanderingState::CellJuniorWanderingState()
{
}

CellJuniorWanderingState::~CellJuniorWanderingState()
{
}

void CellJuniorWanderingState::Enter(EntityCellJunior* cellJunior)
{
	cellJunior->GetBody()->SetLinearVelocity(cellJunior->GetMovementSpeed() * b2Vec2(-1, 0));
	cellJunior->GetSteering()->WanderOn();
	cellJunior->GetSteering()->SeekOff();
}

void CellJuniorWanderingState::Execute(EntityCellJunior* cellJunior)
{
	cellJunior->DecreaseOverheatPerSecond(15);
}

void CellJuniorWanderingState::Exit(EntityCellJunior* cellJunior)
{
}

void CellJuniorWanderingState::Render(EntityCellJunior* cellJunior)
{
}

bool CellJuniorWanderingState::OnMessage(EntityCellJunior* cellJunior, const Telegram& telegram)
{
	if (telegram.Message == MSG_CELLJR_INSIDE_ATTACK_RANGE)
	{
		if (!cellJunior->IsOverheated())
		{
			auto goKuPosition = DereferenceToType<b2Vec2>(telegram.ExtraInfo);
			cellJunior->GetFSM()->ChangeState(CJS_Attacking::GetInstance());
			cellJunior->GetSteering()->SetSeekTarget(goKuPosition);
		}	
		return true;
	}
	return false;
}

/*Global state*/
CellJuniorGlobalState::CellJuniorGlobalState()
{
}

CellJuniorGlobalState::~CellJuniorGlobalState()
{
}

void CellJuniorGlobalState::Enter(EntityCellJunior* minion)
{
}

void CellJuniorGlobalState::Execute(EntityCellJunior* minion)
{
	MS_Global::GetInstance()->Execute(minion);

	if (minion->IsDead())
	{
		minion->GetFSM()->ChangeState(CJS_Dead::GetInstance());
	}
}

void CellJuniorGlobalState::Exit(EntityCellJunior* minion)
{
}

void CellJuniorGlobalState::Render(EntityCellJunior* minion)
{
}

bool CellJuniorGlobalState::OnMessage(EntityCellJunior* minion, const Telegram& telegram)
{
	if (MS_Global::GetInstance()->OnMessage(minion, telegram))
		return true;
	return false;
}

/* Dead State */

CellJuniorDeadState::CellJuniorDeadState()
{
}

CellJuniorDeadState::~CellJuniorDeadState()
{
}

void CellJuniorDeadState::Enter(EntityCellJunior* celljunior)
{
	GS_GamePlay::GetInstance()->GetPlayer()->IncreaseScore(10);
}

void CellJuniorDeadState::Execute(EntityCellJunior* celljunior)
{
	Dispatcher->DispatchMessageA(celljunior, GameInstance, MSG_MINION_OUT_OF_WALL, celljunior);
}

void CellJuniorDeadState::Exit(EntityCellJunior* celljunior)
{
}

void CellJuniorDeadState::Render(EntityCellJunior* celljunior)
{
}

bool CellJuniorDeadState::OnMessage(EntityCellJunior*, const Telegram&)
{
	return false;
}
