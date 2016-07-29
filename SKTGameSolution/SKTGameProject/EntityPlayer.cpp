#include "EntityPlayer.h"
#include "../GraphicsEngine/ResourceManager.h"
#include "../GraphicsEngine/AnimationManager.h"
#include "../GraphicsEngine/InputManager.h"
#include "GamePlayState.h"
#include "PlayerOwnedStates.h"


EntityPlayer::EntityPlayer(): m_fMaxKi(0), m_fCurrentKi(0), m_pStateMachine(new StateMachine<EntityPlayer>(this))
{
	m_pStateMachine->SetGlobalState(PlayerGlobalState::GetInstance());
	m_pStateMachine->SetCurrentState(PlayerStandingState::GetInstance());
}


EntityPlayer::~EntityPlayer()
{
	delete m_pStateMachine;
}

void EntityPlayer::Render()
{
	m_Sprite.Render();
}

void EntityPlayer::Update()
{
	EntityLiving::Update();

	

	m_pStateMachine->Update();
}

EntityType EntityPlayer::GetType()
{
	return ENTITY_PLAYER;
}

bool EntityPlayer::HandleMessage(const Telegram& telegram)
{
	return false;
}

StateMachine<EntityPlayer>* EntityPlayer::GetFSM() const
{
	return m_pStateMachine;
}

EntityLiving* EntityPlayer::Clone()
{
	return nullptr;
}
