#include "PlayerOwnedStates.h"
#include "../GraphicsEngine/InputManager.h"


/**
*	PlayerGlobalState
*/


PlayerGlobalState::~PlayerGlobalState()
{
}

void PlayerGlobalState::Enter(EntityPlayer* entity)
{
}

void PlayerGlobalState::Execute(EntityPlayer* entity)
{
	bool keyA = InputMgr->IsPressed(KEY_A);
	bool keyD = InputMgr->IsPressed(KEY_D);
	bool keyW = InputMgr->IsPressed(KEY_W);
	bool keyS = InputMgr->IsPressed(KEY_S);

	b2Vec2 direction(keyD - keyA, keyW - keyS);
	entity->GetBody()->SetLinearVelocity(entity->GetMovementSpeed() * direction);

}

void PlayerGlobalState::Exit(EntityPlayer* entity)
{
}

void PlayerGlobalState::Render(EntityPlayer* entity)
{
}

PlayerGlobalState* PlayerGlobalState::GetInstance()
{
	static PlayerGlobalState instance;
	return &instance;
}

PlayerGlobalState::PlayerGlobalState()
{
}


/**
*	PlayerStandingState
*/


PlayerStandingState::~PlayerStandingState()
{
}

void PlayerStandingState::Enter(EntityPlayer* entity)
{
}

void PlayerStandingState::Execute(EntityPlayer* entity)
{
	b2Vec2 velocity = entity->GetBody()->GetLinearVelocity();
	if (velocity.Length() > 0)
	{
		entity->GetFSM()->ChangeState(PlayerMovingState::GetInstance());
	}
	if (InputMgr->IsPressed(KEY_J))
	{
		entity->GetFSM()->ChangeState(PlayerFiringState::GetInstance());
	}


	entity->UpdateAnimationToSprite(entity->GetAnimation(STANDING));
}

void PlayerStandingState::Exit(EntityPlayer* entity)
{
	entity->ResetCurrentAnimationInfo();
}

void PlayerStandingState::Render(EntityPlayer* entity)
{
}

PlayerStandingState* PlayerStandingState::GetInstance()
{
	static PlayerStandingState instance;
	return &instance;
}

PlayerStandingState::PlayerStandingState()
{
}


/**
 *	PlayerMovingState
 */

PlayerMovingState::PlayerMovingState()
{
}

PlayerMovingState::~PlayerMovingState()
{
}

void PlayerMovingState::Enter(EntityPlayer* entity)
{
}

void PlayerMovingState::Execute(EntityPlayer* entity)
{
	b2Vec2 velocity = entity->GetBody()->GetLinearVelocity();
	if (velocity.Length() == 0 || InputMgr->IsPressed(KEY_J))
	{
		entity->GetFSM()->ChangeState(PlayerStandingState::GetInstance());
	}


	if (velocity.x > 0)
	{
		// MOVING FORWARD
		entity->UpdateAnimationToSprite(entity->GetAnimation(MOVING_FORWARD));
	}
	if (velocity.x < 0)
	{
		// MOVING BACKWARD	
		entity->UpdateAnimationToSprite(entity->GetAnimation(MOVING_BACKWARD));
	}
	if (velocity.x == 0)
	{
		if (velocity.y > 0)
		{
			// MOVING FORWARD
			entity->UpdateAnimationToSprite(entity->GetAnimation(MOVING_FORWARD));
		}

		if (velocity.y < 0)
		{
			// MOVING BACKWARD
			entity->UpdateAnimationToSprite(entity->GetAnimation(MOVING_BACKWARD));
		}
	}
}


void PlayerMovingState::Exit(EntityPlayer* entity)
{
	entity->ResetCurrentAnimationInfo();
}

void PlayerMovingState::Render(EntityPlayer* entity)
{
}

PlayerMovingState* PlayerMovingState::GetInstance()
{
	static PlayerMovingState instance;
	return &instance;
}


/**
*	PlayerFiringState
*/


PlayerFiringState::~PlayerFiringState()
{
}

void PlayerFiringState::Enter(EntityPlayer* entity)
{
}

void PlayerFiringState::Execute(EntityPlayer* entity)
{
	Animation* firingAnimation = entity->GetAnimation(FIRING_SPECIAL);
	if (!InputMgr->IsPressed(KEY_J) && firingAnimation->GetTotalFrames() <= entity->GetFrameCount())
	{
		entity->GetFSM()->ChangeState(PlayerStandingState::GetInstance());
	}

	entity->UpdateAnimationToSprite(firingAnimation);
}

void PlayerFiringState::Exit(EntityPlayer* entity)
{
	entity->ResetCurrentAnimationInfo();
}

void PlayerFiringState::Render(EntityPlayer* entity)
{
}

PlayerFiringState* PlayerFiringState::GetInstance()
{
	static PlayerFiringState instance;
	return &instance;
}

PlayerFiringState::PlayerFiringState()
{
}
