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
}

void CellJuniorAttackingState::Execute(EntityCellJunior* celljunior)
{
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

void CellJuniorWanderingState::Enter(EntityCellJunior* minion)
{
}

void CellJuniorWanderingState::Execute(EntityCellJunior* minion)
{
}

void CellJuniorWanderingState::Exit(EntityCellJunior* minion)
{
}

void CellJuniorWanderingState::Render(EntityCellJunior* minion)
{
}

bool CellJuniorWanderingState::OnMessage(EntityCellJunior* cellJunior, const Telegram& telegram)
{
	if (telegram.Message == MSG_CELLJR_INSIDE_ATTACK_RANGE)
	{
		auto goKuPosition = DereferenceToType<b2Vec2>(telegram.ExtraInfo);
		//minion->GetFSM()->ChangeState(CJS_Attacking::GetInstance());
		std::cout << goKuPosition.x << " " << goKuPosition.y << std::endl;
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
	if (minion->IsOutOfWall())
	{
		Dispatcher->DispatchMessageA(SEND_MSG_IMMEDIATELY, minion, Singleton<Game>::GetInstance(),
			MSG_MINION_OUT_OF_WALL, minion);
	}
}

void CellJuniorGlobalState::Exit(EntityCellJunior* minion)
{
}

void CellJuniorGlobalState::Render(EntityCellJunior* minion)
{
}

bool CellJuniorGlobalState::OnMessage(EntityCellJunior*, const Telegram&)
{
	return false;
}
