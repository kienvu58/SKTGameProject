#include "MinionOwnedStates.h"
#include "SingletonClasses.h"

/*Wandering state*/
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

WanderingState::WanderingState()
{
}

WanderingState::~WanderingState()
{
}

/*Global state*/
MinionGlobalState::MinionGlobalState()
{
}

MinionGlobalState::~MinionGlobalState()
{
}

void MinionGlobalState::Enter(EntityMinion* minion)
{
}

void MinionGlobalState::Execute(EntityMinion* minion)
{
	if (minion->IsOutOfWall())
	{
		Dispatcher->DispatchMessageA(SEND_MSG_IMMEDIATELY, minion, GS_GamePlay::GetInstance(), 
			MSG_MINION_OUT_OF_WALL, minion);
	}
}

void MinionGlobalState::Exit(EntityMinion* minion)
{
}

void MinionGlobalState::Render(EntityMinion* minion)
{
}
