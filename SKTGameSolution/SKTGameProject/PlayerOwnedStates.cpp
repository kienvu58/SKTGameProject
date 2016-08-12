#include "PlayerOwnedStates.h"
#include "../GraphicsEngine/InputManager.h"
#include "SingletonClasses.h"
#include "../GraphicsEngine/Globals.h"

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
	else
	{
		entity->DetectMinions();
	}

	auto keyA = InputMgr->IsPressed(KEY_A);
	auto keyD = InputMgr->IsPressed(KEY_D);
	auto keyW = InputMgr->IsPressed(KEY_W);
	auto keyS = InputMgr->IsPressed(KEY_S);

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
		auto damage = DereferenceToType<float>(telegram.ExtraInfo);
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
		MusicMgr->MusicPlay("SkillShot");
		MusicMgr->MusicVolume("SkillShot", 50);
	}
	if (InputMgr->IsPressed(KEY_K))
	{
		// change to PlayerFiringSpecialState
		entity->GetFSM()->ChangeState(PS_FiringSpecial::GetInstance());
		MusicMgr->MusicPlay("SkillUlti_1");
		MusicMgr->MusicVolume("SkillUlti_1", 50);
	}
	if (InputMgr->IsPressed(KEY_L))
	{
		// change to PlayerFiringUltimateState
		entity->GetFSM()->ChangeState(PS_FiringUltimate::GetInstance());
		MusicMgr->MusicPlay("SkillUlti_2");
		MusicMgr->MusicVolume("SkillUlti_2", 50);
	}

	entity->UpdateSpriteFrame(entity->GetAnimation(STANDING));
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
		entity->UpdateSpriteFrame(entity->GetAnimation(MOVING_FORWARD));
	}
	if (velocity.x < 0)
	{
		// MOVING BACKWARD	
		entity->UpdateSpriteFrame(entity->GetAnimation(MOVING_BACKWARD));
	}
	if (velocity.x == 0)
	{
		if (velocity.y > 0)
		{
			// MOVING UP
			entity->UpdateSpriteFrame(entity->GetAnimation(MOVING_UP));
		}

		if (velocity.y < 0)
		{
			// MOVING DOWN
			entity->UpdateSpriteFrame(entity->GetAnimation(MOVING_DOWN));
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
		entity->Fire();
		entity->IncreaseOverheat(5);
	}

	if (entity->IsOverheated() ||
		!InputMgr->IsPressed(KEY_J) && firingAnimation->GetTotalFrames() <= entity->GetFrameCount())
	{
		// change to PlayerStandingState
		entity->GetFSM()->ChangeState(PS_Standing::GetInstance());
	}

	entity->UpdateSpriteFrame(firingAnimation);
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
	m_fSpecialTime = 0.0f;
}

void PlayerFiringSpecialState::Execute(EntityPlayer* entity)
{
	// player cannot mow while firing special
	entity->GetBody()->SetLinearVelocity(b2Vec2(0, 0));

	Animation* firingSpecialAnimation = entity->GetAnimation(FIRING_SPECIAL);
	auto startFiringFrameIndex = firingSpecialAnimation->GetNStartFrame();
	auto currentFrameIndex = entity->GetFrameCount();

	if (currentFrameIndex >= startFiringFrameIndex)
	{
		m_fSpecialTime += Globals::deltaTime;
	}

	if (currentFrameIndex == startFiringFrameIndex && entity->IsFrameChanged())
	{
		entity->FireSpecial();
		// Decrease Ki here
	}

	if (m_fSpecialTime >= entity->GetSpecialDuration())
	{
		// change to PlayerStandingState
		entity->GetFSM()->ChangeState(PS_Standing::GetInstance());
	}

	entity->UpdateSpriteFrame(firingSpecialAnimation);
}

void PlayerFiringSpecialState::Exit(EntityPlayer* entity)
{
	entity->StopSpecial();
	entity->ResetCurrentAnimationInfo();
}


void PlayerFiringSpecialState::Render(EntityPlayer* entity)
{
}

bool PlayerFiringSpecialState::OnMessage(EntityPlayer*, const Telegram&)
{
	return false;
}

PlayerFiringSpecialState::PlayerFiringSpecialState(): m_fSpecialTime(0) {
}


/**
*	PlayerFiringUltimateState
*/


PlayerFiringUltimateState::~PlayerFiringUltimateState()
{
	m_fUltimateTime = 0.0f;
}

void PlayerFiringUltimateState::Enter(EntityPlayer* entity)
{
}

void PlayerFiringUltimateState::Execute(EntityPlayer* entity)
{
	// player cannot mow while firing ultimate
	entity->GetBody()->SetLinearVelocity(b2Vec2(0, 0));

	Animation* firingUltimateAnimation = entity->GetAnimation(FIRING_ULTIMATE);

	auto startFiringFrameIndex = firingUltimateAnimation->GetNStartFrame();
	auto currentFrameIndex = entity->GetFrameCount();

	if (currentFrameIndex >= startFiringFrameIndex)
	{
		m_fUltimateTime += Globals::deltaTime;
	}

	if (currentFrameIndex == startFiringFrameIndex && entity->IsFrameChanged())
	{
		entity->FireUltimate();
		// Decrease Ki here
	}

	if (m_fUltimateTime >= entity->GetUltimateDuration())
	{
		// change to PlayerStandingState
		entity->GetFSM()->ChangeState(PS_Standing::GetInstance());
	}

	entity->UpdateSpriteFrame(firingUltimateAnimation);
}

void PlayerFiringUltimateState::Exit(EntityPlayer* entity)
{
	entity->StopUltimate();
	entity->ResetCurrentAnimationInfo();
}


void PlayerFiringUltimateState::Render(EntityPlayer* entity)
{
}

bool PlayerFiringUltimateState::OnMessage(EntityPlayer*, const Telegram&)
{
	return false;
}

PlayerFiringUltimateState::PlayerFiringUltimateState(): m_fUltimateTime(0) {
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
		player->UpdateSpriteFrame(player->GetAnimation(DEAD));
		MusicMgr->MusicPlay("GokuDead");
		MusicMgr->MusicVolume("GokuDead", 50);
		MusicMgr->MusicStop("GamePlay");
		GameInstance->GetFSM()->ChangeState(GS_GameOver::GetInstance());
	}
	else
	{
		player->UpdateSpriteFrame(player->GetAnimation(FALLING));
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
