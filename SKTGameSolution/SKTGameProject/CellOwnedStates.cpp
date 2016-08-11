#include "CellOwnedStates.h"
#include "SingletonClasses.h"
#include "../GraphicsEngine/Globals.h"
#include "RayCastMultipleCallback.h"

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

/* Wandering State */
CellWanderingState::CellWanderingState()
{

}

CellWanderingState::~CellWanderingState()
{
}

void CellWanderingState::Enter(EntityCell* cell)
{
	cell->GetSteering()->WanderOn();
	cell->GetBody()->SetLinearVelocity(cell->GetMovementSpeed() * b2Vec2(-1, 0));
}

void CellWanderingState::Execute(EntityCell* cell)
{
	cell->UpdateAnimationToSprite(cell->GetAnimation(CELL_FORWARD));
	static float angle = 0.0f;
	angle += Globals::deltaTime * 10 * Radians(360);
	b2Vec2 eye = cell->GetBody()->GetPosition();
	b2Vec2 target = eye + 2 * b2Vec2(cosf(angle), sinf(angle));
	RayCastMultipleCallback callback;
	callback.maskBits = CATEGORY_KI_BLAST;
	PhysicsMgr->GetWorld()->RayCast(&callback, eye, target);
	if (callback.fixtures.size() > 0)
	{
		b2Vec2 fleeTarget = callback.fixtures.at(0)->GetBody()->GetPosition();
		cell->GetSteering()->SetFleeTarget(fleeTarget);
		cell->GetFSM()->ChangeState(CS_Dodging::GetInstance());
	}
	cell->DecreaseOverheatPerSecond(15);
}

void CellWanderingState::Exit(EntityCell* cell)
{
	cell->GetSteering()->WanderOff();
	cell->ResetCurrentAnimationInfo();
}

void CellWanderingState::Render(EntityCell* minion)
{
}

bool CellWanderingState::OnMessage(EntityCell*, const Telegram&)
{
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

void CellAttackingState::Exit(EntityCell* cell)
{
	cell->ResetCurrentAnimationInfo();
}

void CellAttackingState::Render(EntityCell* Cell)
{

}

bool CellAttackingState::OnMessage(EntityCell*, const Telegram&)
{
	return false;
}

/* Dodging State */
CellDodgingState::CellDodgingState()
{
}

CellDodgingState::~CellDodgingState()
{
}

void CellDodgingState::Enter(EntityCell* cell)
{
	cell->GetSteering()->FleeOn();
	cell->GetSteering()->SetFleeTarget(b2Vec2(0, 0));
	cell->ScaleVelocity(2.0f);
	cell->SetOverheat(0);
}

void CellDodgingState::Execute(EntityCell* cell)
{
	cell->IncreaseOverheat(6);
	cell->UpdateAnimationToSprite(cell->GetAnimation(CELL_BACKWARD));
	if (cell->IsOverheated())
	{
		cell->GetFSM()->ChangeState(CS_Wandering::GetInstance());
	}
}

void CellDodgingState::Exit(EntityCell* cell)
{
	cell->GetSteering()->FleeOff();
	cell->ResetCurrentAnimationInfo();
}

void CellDodgingState::Render(EntityCell* Cell)
{
}

bool CellDodgingState::OnMessage(EntityCell*, const Telegram&)
{
	return false;
}
