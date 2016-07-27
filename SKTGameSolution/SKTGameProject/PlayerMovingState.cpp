#include "PlayerMovingState.h"
#include "../GraphicsEngine/InputManager.h"
#include "PlayerStandingState.h"


PlayerMovingState::PlayerMovingState()
{
}

void PlayerMovingState::Enter(EntityPlayer* entity)
{
}

void PlayerMovingState::Execute(EntityPlayer* entity)
{
	
}

void PlayerMovingState::Exit(EntityPlayer* entity)
{
}

void PlayerMovingState::Render(EntityPlayer* entity)
{
}

PlayerMovingState* PlayerMovingState::GetInstance()
{
	static PlayerMovingState instance;
	return &instance;
}

PlayerMovingState::~PlayerMovingState()
{
}
