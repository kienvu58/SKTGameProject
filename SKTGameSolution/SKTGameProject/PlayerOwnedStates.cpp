#include "PlayerOwnedStates.h"
#include "../GraphicsEngine/InputManager.h"
#include "SingletonClasses.h"


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
		// change to PlayerMovingState
		entity->GetFSM()->ChangeState(PS_Moving::GetInstance());
	}
	if (InputMgr->IsPressed(KEY_J))
	{
		// change to PlayerFiringState
		entity->GetFSM()->ChangeState(PS_Firing::GetInstance());
	}
	if (InputMgr->IsPressed(KEY_K))
	{
		// change to PlayerFiringSpecialState
		entity->GetFSM()->ChangeState(PS_FiringSpecial::GetInstance());
	}
	if (InputMgr->IsPressed(KEY_L))
	{
		// change to PlayerFiringUltimateState
		entity->GetFSM()->ChangeState(PS_FiringUltimate::GetInstance());
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

	auto keyJ = InputMgr->IsPressed(KEY_J);
	auto keyK = InputMgr->IsPressed(KEY_K);
	auto keyL = InputMgr->IsPressed(KEY_L);
	if (velocity.Length() == 0 || keyJ || keyK || keyL)
	{
		// change to PlayerStandingState
		entity->GetFSM()->ChangeState(PS_Standing::GetInstance());
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


/**
*	PlayerFiringState
*/

PlayerFiringState::PlayerFiringState()
{
}

PlayerFiringState::~PlayerFiringState()
{
}

void PlayerFiringState::Enter(EntityPlayer* entity)
{
}

void PlayerFiringState::Execute(EntityPlayer* entity)
{
	Animation* firingAnimation = entity->GetAnimation(FIRING);

	if (entity->IsFrameChanged())
	{
		b2Vec2 kiBlastPosition = entity->GetBody()->GetPosition() + b2Vec2(0.1, 0.1);
		Dispatcher->DispatchMessageA(SEND_MSG_IMMEDIATELY, entity, GS_GamePlay::GetInstance(),
		                             MSG_SPAWN_KI_BLAST, &kiBlastPosition);
	}


	if (!InputMgr->IsPressed(KEY_J) && firingAnimation->GetTotalFrames() <= entity->GetFrameCount())
	{
		// change to PlayerStandingState
		entity->GetFSM()->ChangeState(PS_Standing::GetInstance());
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

/**
*	PlayerFiringSpecialState
*/


PlayerFiringSpecialState::~PlayerFiringSpecialState()
{
}

void PlayerFiringSpecialState::Enter(EntityPlayer* entity)
{
}

void PlayerFiringSpecialState::Execute(EntityPlayer* entity)
{
	// player cannot mow while firing special
	entity->GetBody()->SetLinearVelocity(b2Vec2(0, 0));

	Animation* firingSpecialAnimation = entity->GetAnimation(FIRING_SPECIAL);
	if (!InputMgr->IsPressed(KEY_K) && firingSpecialAnimation->GetTotalFrames() <= entity->GetFrameCount())
	{
		// change to PlayerStandingState
		entity->GetFSM()->ChangeState(PS_Standing::GetInstance());
	}

	entity->UpdateAnimationToSprite(firingSpecialAnimation);
}

void PlayerFiringSpecialState::Exit(EntityPlayer* entity)
{
	entity->ResetCurrentAnimationInfo();
}


void PlayerFiringSpecialState::Render(EntityPlayer* entity)
{
}

PlayerFiringSpecialState::PlayerFiringSpecialState()
{
}


/**
*	PlayerFiringUltimateState
*/


PlayerFiringUltimateState::~PlayerFiringUltimateState()
{
}

void PlayerFiringUltimateState::Enter(EntityPlayer* entity)
{
}

void PlayerFiringUltimateState::Execute(EntityPlayer* entity)
{
	// player cannot mow while firing ultimate
	entity->GetBody()->SetLinearVelocity(b2Vec2(0, 0));

	Animation* firingUltimateAnimation = entity->GetAnimation(FIRING_ULTIMATE);
	if (!InputMgr->IsPressed(KEY_L) && firingUltimateAnimation->GetTotalFrames() <= entity->GetFrameCount())
	{
		// change to PlayerStandingState
		entity->GetFSM()->ChangeState(PS_Standing::GetInstance());
	}

	entity->UpdateAnimationToSprite(firingUltimateAnimation);
}

void PlayerFiringUltimateState::Exit(EntityPlayer* entity)
{
	entity->ResetCurrentAnimationInfo();
}


void PlayerFiringUltimateState::Render(EntityPlayer* entity)
{
}

PlayerFiringUltimateState::PlayerFiringUltimateState()
{
}
