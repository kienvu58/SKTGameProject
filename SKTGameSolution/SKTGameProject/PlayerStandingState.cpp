#include "PlayerStandingState.h"
#include "../GraphicsEngine/InputManager.h"
#include "PlayerMovingState.h"


PlayerStandingState::PlayerStandingState()
{
}


PlayerStandingState::~PlayerStandingState()
{
}

void PlayerStandingState::Enter(EntityPlayer* entity)
{
}

void PlayerStandingState::Execute(EntityPlayer* entity)
{
	
}

void PlayerStandingState::Exit(EntityPlayer* entity)
{
}

void PlayerStandingState::Render(EntityPlayer* entity)
{
}

PlayerStandingState* PlayerStandingState::GetInstance()
{
	static PlayerStandingState instance;
	return &instance;
}
