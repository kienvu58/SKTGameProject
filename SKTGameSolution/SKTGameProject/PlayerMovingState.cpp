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
	if (InputMgr->IsPressed(KEY_A) ||
		InputMgr->IsPressed(KEY_S))
	{
		Frame* frame = entity->s_AnimationMovingBackward->GetNextFrame();
		entity->SetFrameToSprite(frame);
	}

	if (!InputMgr->IsPressed(KEY_A) &&
		InputMgr->IsPressed(KEY_W) ||
		InputMgr->IsPressed(KEY_D))
	{
		Frame* frame = entity->s_AnimationMovingForward->GetNextFrame();
		entity->SetFrameToSprite(frame);
	}

	if (!(InputMgr->IsPressed(KEY_A) ||
		InputMgr->IsPressed(KEY_S) ||
		InputMgr->IsPressed(KEY_D) ||
		InputMgr->IsPressed(KEY_W)))
	{
		entity->GetFSM()->ChangeState(PlayerStandingState::GetInstance());
	}
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
