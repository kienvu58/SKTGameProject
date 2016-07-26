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
	Frame* frame = entity->s_AnimationStanding->GetNextFrame();
	entity->SetFrameToSprite(frame);

	if (InputMgr->IsPressed(KEY_A) ||
		InputMgr->IsPressed(KEY_S) ||
		InputMgr->IsPressed(KEY_D) ||
		InputMgr->IsPressed(KEY_W))
	{
		entity->GetFSM()->ChangeState(PlayerMovingState::GetInstance());
	}
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
