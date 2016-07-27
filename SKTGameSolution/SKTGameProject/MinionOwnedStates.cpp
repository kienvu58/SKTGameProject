#include "MinionOwnedStates.h"

void WanderingState::Enter(EntityMinion* minion)
{
}

void WanderingState::Execute(EntityMinion* minion)
{
	
}

void WanderingState::Exit(EntityMinion* minion)
{
}

void WanderingState::Render(EntityMinion* minion)
{
	
}

WanderingState* WanderingState::GetInstance()
{
	static WanderingState instance;
	return &instance;
}

WanderingState::WanderingState()
{
}

WanderingState::~WanderingState()
{
}