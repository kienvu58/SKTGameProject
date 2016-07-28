#include "PlayerOwnedStates.h"

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

	Frame* frame = entity->GetAnimation(STANDING)
	                     ->GetNextFrame(entity->GetCurrentFrame(), entity->GetCurrentDelay());
	entity->SetFrameToSprite(frame);
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
	if (velocity.Length() == 0)
	{
		entity->GetFSM()->ChangeState(PlayerStandingState::GetInstance());
	}

	if (velocity.x > 0)
	{
		Frame* frame = entity->GetAnimation(MOVING_FORWARD)
		                     ->GetNextFrame(entity->GetCurrentFrame(), entity->GetCurrentDelay());
		entity->SetFrameToSprite(frame);
	}
	if (velocity.x < 0)
	{
		Frame* frame = entity->GetAnimation(MOVING_BACKWARD)
		                     ->GetNextFrame(entity->GetCurrentFrame(), entity->GetCurrentDelay());
		entity->SetFrameToSprite(frame);
	}
	if (velocity.x == 0)
	{
		if (velocity.y > 0)
		{
			Frame* frame = entity->GetAnimation(MOVING_FORWARD)
				->GetNextFrame(entity->GetCurrentFrame(), entity->GetCurrentDelay());
			entity->SetFrameToSprite(frame);
		}if (velocity.y < 0)
		{
			Frame* frame = entity->GetAnimation(MOVING_BACKWARD)
				->GetNextFrame(entity->GetCurrentFrame(), entity->GetCurrentDelay());
			entity->SetFrameToSprite(frame);
		}
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
