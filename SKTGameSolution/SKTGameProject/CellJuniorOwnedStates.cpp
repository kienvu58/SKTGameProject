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

void CellJuniorAttackingState::Execute(EntityCellJunior* cellJunior)
{
	cellJunior->IncreaseOverheat(2);
	auto playerPosition = GS_GamePlay::GetInstance()->GetPlayer()->GetBody()->GetPosition();
	cellJunior->GetSteering()->SetSeekTarget(playerPosition);
	if (cellJunior->IsOverheated())
	{
		cellJunior->GetFSM()->ChangeState(CJS_Wandering::GetInstance());
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
	if (telegram.Message == MSG_MINION_INSIDE_VISION_RANGE)
	{
		if (!cellJunior->IsOverheated())
		{
			auto playerPosition = DereferenceToType<b2Vec2>(telegram.ExtraInfo);
			cellJunior->GetFSM()->ChangeState(CJS_Attacking::GetInstance());
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
