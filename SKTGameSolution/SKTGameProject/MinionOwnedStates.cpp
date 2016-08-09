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

bool WanderingState::OnMessage(EntityMinion* minion, const Telegram& telegram)
{
	return false;
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
		Dispatcher->DispatchMessageA(minion, GameInstance, MSG_MINION_OUT_OF_WALL, minion);
	}
}

void MinionGlobalState::Exit(EntityMinion* minion)
{
}

void MinionGlobalState::Render(EntityMinion* minion)
{
}

bool MinionGlobalState::OnMessage(EntityMinion* minion, const Telegram& telegram)
{
	if (telegram.Message == MSG_MINION_TAKE_DAMAGE)
	{
		float damage = DereferenceToType<float>(telegram.ExtraInfo);
		minion->TakeDamage(damage);
		return true;
	}
	if (telegram.Message == MSG_MINION_HIT_PLAYER)
	{
		Dispatcher->DispatchMessageA(minion, GameInstance, MSG_MINION_OUT_OF_WALL, minion);
		return true;
	}
	return false;
}


/* Dead State */
MinionDeadState::MinionDeadState()
{
}

MinionDeadState::~MinionDeadState()
{
}

void MinionDeadState::Enter(EntityMinion* minion)
{
}

void MinionDeadState::Execute(EntityMinion* minion)
{
}

void MinionDeadState::Exit(EntityMinion* minion)
{
}

void MinionDeadState::Render(EntityMinion* minion)
{
}

bool MinionDeadState::OnMessage(EntityMinion*, const Telegram&)
{
	return false;
}
