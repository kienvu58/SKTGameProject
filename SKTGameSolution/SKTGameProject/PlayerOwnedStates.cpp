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
	if (entity->IsDead())
	{
		entity->GetFSM()->ChangeState(PS_FallToDead::GetInstance());
	}

	bool keyA = InputMgr->IsPressed(KEY_A);
	bool keyD = InputMgr->IsPressed(KEY_D);
	bool keyW = InputMgr->IsPressed(KEY_W);
	bool keyS = InputMgr->IsPressed(KEY_S);

	b2Vec2 direction(keyD - keyA, keyW - keyS);
	
	if (entity->GetFSM()->CurrentState() != PS_FallToDead::GetInstance())
	{
		entity->GetBody()->SetLinearVelocity(entity->GetMovementSpeed() * direction);
	}

	if (entity->GetFSM()->CurrentState() != PS_Firing::GetInstance())
	{
		entity->DecreaseOverheatPerSecond(50);
	}
}

void PlayerGlobalState::Exit(EntityPlayer* entity)
{
}

void PlayerGlobalState::Render(EntityPlayer* entity)
{
}

bool PlayerGlobalState::OnMessage(EntityPlayer* player, const Telegram& telegram)
{
	if (telegram.Message == MSG_PLAYER_TAKE_DAMAGE)
	{
		float damage = DereferenceToType<float>(telegram.ExtraInfo);
		player->TakeDamage(damage);
		return true;
	}
	return false;
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
	if (InputMgr->IsPressed(KEY_J) && !entity->IsOverheated())
	{
		// change to PlayerFiringState
		entity->GetFSM()->ChangeState(PS_Firing::GetInstance());
	}
	if (InputMgr->IsPressed(KEY_K))
	{
		// change to PlayerFiringSpecialState
		entity->GetFSM()->ChangeState(PS_FiringSpecial::GetInstance());
		MusicMgr->MusicPlay("Skill");
		MusicMgr->MusicVolume("Skill", 100);
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

bool PlayerStandingState::OnMessage(EntityPlayer*, const Telegram&)
{
	return false;
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
	if (velocity.Length() == 0 || keyJ && !entity->IsOverheated() || keyK || keyL)
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

bool PlayerMovingState::OnMessage(EntityPlayer*, const Telegram&)
{
	return false;
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
		b2Vec2 kiBlastPosition = entity->GetBody()->GetPosition() + b2Vec2(0.2, 0.1);
		Dispatcher->DispatchMessageA(SEND_MSG_IMMEDIATELY, entity, GameInstance,
		                             MSG_SPAWN_KI_BLAST, &kiBlastPosition);
		entity->IncreaseOverheat(5);
	}


	if (entity->IsOverheated() ||
		!InputMgr->IsPressed(KEY_J) && firingAnimation->GetTotalFrames() <= entity->GetFrameCount())
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

bool PlayerFiringState::OnMessage(EntityPlayer*, const Telegram&)
{
	return false;
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
	int currentFrame = entity->GetFrameCount() % firingSpecialAnimation->GetTotalFrames();

	if (currentFrame == 2 && entity->IsFrameChanged())
	{
		b2Vec2 kamehamehaPosition = entity->GetBody()->GetPosition() + b2Vec2(0.75, 0.15);
		Dispatcher->DispatchMessageA(SEND_MSG_IMMEDIATELY, entity, GameInstance,
		                             MSG_SPAWN_KAMEHAMEHA, &kamehamehaPosition);
	}

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

bool PlayerFiringSpecialState::OnMessage(EntityPlayer*, const Telegram&)
{
	return false;
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

	int currentFrame = entity->GetFrameCount() % firingUltimateAnimation->GetTotalFrames();

	if (currentFrame == 7 && entity->IsFrameChanged())
	{
		b2Vec2 kamehamehaPosition = entity->GetBody()->GetPosition() + b2Vec2(0.1, 0);
		Dispatcher->DispatchMessageA(SEND_MSG_IMMEDIATELY, entity, GameInstance,
		                             MSG_SPAWN_TRUE_KAMEHAMEHA, &kamehamehaPosition);
	}
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

bool PlayerFiringUltimateState::OnMessage(EntityPlayer*, const Telegram&)
{
	return false;
}

PlayerFiringUltimateState::PlayerFiringUltimateState()
{
}


/**
*	PlayerTakingDamagedState
*/

PlayerTakingDamageState::PlayerTakingDamageState()
{
}

PlayerTakingDamageState::~PlayerTakingDamageState()
{
}

void PlayerTakingDamageState::Enter(EntityPlayer* player)
{
}

void PlayerTakingDamageState::Execute(EntityPlayer* player)
{
}

void PlayerTakingDamageState::Exit(EntityPlayer* player)
{
	player->ResetCurrentAnimationInfo();
}

void PlayerTakingDamageState::Render(EntityPlayer* player)
{
}

bool PlayerTakingDamageState::OnMessage(EntityPlayer*, const Telegram&)
{
	return false;
}

/* Player FallingToDead state*/

PlayerFallingToDead::PlayerFallingToDead()
{
}

PlayerFallingToDead::~PlayerFallingToDead()
{
}

void PlayerFallingToDead::Enter(EntityPlayer* player)
{
	player->GetBody()->SetLinearVelocity(b2Vec2_zero);
	player->GetBody()->ApplyForceToCenter(b2Vec2(0, -100), false);
}

void PlayerFallingToDead::Execute(EntityPlayer* player)
{
	if (player->IsOnTheGround())
	{
		player->UpdateAnimationToSprite(player->GetAnimation(DEAD));
		GameInstance->GetFSM()->ChangeState(GS_GameOver::GetInstance());
	}
	else
	{
		player->UpdateAnimationToSprite(player->GetAnimation(FALLING));
	}
}

void PlayerFallingToDead::Exit(EntityPlayer* player)
{
	player->ResetCurrentAnimationInfo();
}

void PlayerFallingToDead::Render(EntityPlayer* player)
{
}

bool PlayerFallingToDead::OnMessage(EntityPlayer*, const Telegram&)
{
	return false;
}
